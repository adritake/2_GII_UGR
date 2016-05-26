
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>


void bloqueodesbloqueo (int descriptor, int orden) {

    struct flock cerrojo;


    cerrojo.l_type= orden;
    cerrojo.l_whence= SEEK_SET;
    cerrojo.l_start= 0;
    cerrojo.l_len = 0;

    //Establecemos un cerrojo con F_SETLKW
    if (fcntl(descriptor, F_SETLKW, &cerrojo) == -1){
        perror ("Error al bloquear para la impresion en el proxy");
        exit(1);
    }
}


int main(int argc, char *argv[]){

    char buffer[1024];
    char fifo[200];
    int tamanio, descriptor;
    FILE *tmp = tmpfile();

    // Se escriben en un archivo temporal bloques de 1024 bytes leidos desde la entrada estandar
    while((tamanio = read(STDIN_FILENO, buffer, 1024)) > 0){
        fwrite(buffer, sizeof(char), tamanio, tmp);
    }
    // Se abre el archivo de bloqueos.
    if ((descriptor = open("Archivo_B", O_RDWR)) == -1)
        printf("Error al abrir el archivo de bloques\n");
    // Se bloquea el cerrojo
    bloqueodesbloqueo(descriptor, F_WRLCK);

    // Se copia en la salida estandar lo que hay en el archivo temporal
    while(!feof(tmp)){

        fread(buffer, sizeof(char), 1024, tmp);
        write(STDOUT_FILENO, buffer, 1024);

    }

    // Se desbloquea el cerrojo.
    bloqueodesbloqueo(descriptor, F_UNLCK);
    // Se elimina su fifo
    sprintf(fifo,"fifo.%d", getpid());
    remove(fifo);
    exit(0);
}

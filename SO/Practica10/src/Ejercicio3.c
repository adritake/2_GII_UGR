#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
int main (int argc, char * argv[])
{
    //Se trata de lanzar dos veces el programa para ver que uno tiene bloqueado el archivo

    if(argc != 2){
        perror("Uso: ./Ejercicio3 archivo");
        exit(0);
    }

    int fd = open(argv[1], O_RDWR);

    struct flock cerrojo;

    cerrojo.l_type=F_WRLCK;
    cerrojo.l_whence=SEEK_SET;
    cerrojo.l_start=1;
    cerrojo.l_len=50;

    printf ("Intentando bloquear %s\n", argv[1]);
    if (fcntl (fd, F_SETLKW, &cerrojo) == EDEADLK){

        printf ("%s no se ha podido bloquear\n", argv[1]);

    }
    else{

        printf ("%s se ha podido bloquear\n", argv[1]);

        sleep(1);
        sleep(1);

        //Desbloqueo
        cerrojo.l_type=F_UNLCK;
        cerrojo.l_whence=SEEK_SET;
        cerrojo.l_start=1;
        cerrojo.l_len=50;

        fcntl (fd, F_SETLKW, &cerrojo);
    }


}


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>

const int longitud_nombre = 50;
const int MAX_CLIENTES = 20;

static void manejador(int sig){
    pid_t pid;
    char fifoproxy[longitud_nombre];
    pid = wait(NULL);

}

int main(int argc, char *argv[]){

    int fde, fds, fdc, tmp_cli,fifo;
    char nombrefifoc[longitud_nombre];
    char nombrefifos[longitud_nombre];
    char fifoproxy[longitud_nombre];
    int leidos, pid_proxy;
    pid_t pid;


    if(argc != 2) {
        printf("Uso: servidor <nombre_fifo>\n");
        exit(-1);
    }
    // Manejador de señal SIGCHLD.
    signal(SIGCHLD, manejador);

    // Agregacion de las letras al nombre de los fifos
    sprintf(nombrefifos,"%ss",argv[1]);
    sprintf(nombrefifoc,"%se",argv[1]);

    // Creacion de los fifos
    umask(0);
    mkfifo(nombrefifoc,0666);
    mkfifo(nombrefifos,0666);

    //Creacion del fifo del servidor y almacenamiento de su descriptor
    if((fds=open(nombrefifos,O_RDWR)) < 0){
        perror("\nError en la creación del fifo del servidor.");
        exit(-1);
    }

    //Creacion del fifo del cliente y almacenamiento de su descriptor
    if((fde=open(nombrefifoc,O_RDWR)) < 0){
        perror("\nError en la creación del fifo del cliente.");
        exit(-1);
    }

    // Creacion del archivo cuyas partes se bloquearan
    umask(0);
    if((fdc=open("Archivo_B", O_CREAT, 0666))<0){
        printf("\nError al crear el archivo de bloqueo.");
        exit(-1);
    }

    // Se crean proxys mientras se reciben datos del fifo del cliente
    while((leidos=read(fde, &tmp_cli, sizeof(int))) != 0){

        pid = fork();

        if (pid == 0){

            ///////  HIJO  //////

            // Pid de proceso proxy
            pid_proxy = getpid();

            // Se añade el pid al nombre del fifo
            sprintf(fifoproxy,"fifo.%d", pid_proxy);
            // Crear archivo fifo.
            umask(0);
            mkfifo(fifoproxy,0666);
            // Se escribe el pid en el fifo
            write(fds, &pid_proxy, sizeof(int));
            // Abrir fifo para lectura.
            fifo = open(fifoproxy,O_RDONLY);
            // Se redirige la entrada estandar al descriptor del fifo
            dup2(fifo, STDIN_FILENO);
            // Se ejecuta el proxy
            execlp("./proxy", "proxy", NULL);
            exit(0);
        }
    }
    return 0;
}

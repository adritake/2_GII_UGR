/*

    Nombre: Adrián de la Torre Rodríguez

*/


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>


int main( int argc, char *argv[]){


    if(argc != 2) {
    	perror("\nUso Padre <path>");
    	exit(-1);
    }

    int pid,n = 1;
    int fd[2];
    char buffer[10];

    pipe(fd);   //Creacion del fifo por el que se comunican los dos hijos

    //Creacion del primer hijo
    if( (pid=fork())<0) {
        perror("\nError en el primer fork");
        exit(-1);
    }

    if( pid == 0){
        //Este hijo se encarga de recibir numeros por entrada estandar

        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);

        while( n != 0){

            scanf("%d",&n);
            printf("%d",n); //Se escriben en el pipe porque he cerrado la salida estandar y redirigido al pipe

            if( n == 0)
                exit(0);
        }


    }
    else{

        //Creacion del segundo hijo por el padre
        if( (pid=fork())<0) {
            perror("\nError en el segundo fork");
            exit(-1);
        }

        if( pid == 0 ){

            //El segundo hijo ejecuta el programa LeerDir

            //Se redirige la entrada a la entrada del pipe
            close(fd[1]);
            dup2(fd[0],STDIN_FILENO);

            //Ejecucion del programa LeerDir
            if( (execl("/home/adritake/SO/Modulo2/Examen/LeerDir","LeerDir", argv[1], NULL)<0)) {
                perror("\nError en el execl");
            }

        }
        else{

            //El padre espera a sus hijos
            waitpid(-1);
            printf("El proceso padre ha finalizado.\n");
        }

    }






}

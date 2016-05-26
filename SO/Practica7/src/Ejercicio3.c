#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main( int argc, char *argv[] ){

    if(argc != 2){
        printf("Uso: ./Ejercicio3 <n_procesos>\n");
        exit(-1);
    }

    int nprocs = atoi(argv[1]);

    /*
        Jerarquía de procesos tipo 1
    */
    int i;
    pid_t childpid;


/*
    printf("*******Jerarquía de procesos tipo 1********\n" );
    for (i=1; i < nprocs; i++) {

        if ((childpid= fork()) == -1) {
            fprintf(stderr, "Could not create child %d: %d\n",i,strerror(errno));
            exit(-1);
        }



        if (childpid){
            printf("\nPID actual: %d   PID del padre: %d",getpid(),getppid() );
            fflush(stdout);
            break;
        }
    }
*/

    /*
        Jerarquía de procesos tipo 2
    */

    printf("*******Jerarquía de procesos tipo 2********\n" );
    for ( i=1; i < nprocs; i++) {
        if ((childpid= fork()) == -1) {
            fprintf(stderr, "Could not create child %d: %d\n",i,strerror(errno));
            exit(-1);
        }

        if (!childpid){
            printf("\nPID actual: %d   PID del padre: %d",getpid(),getppid() );
            //fflush(stdout);
            break;
        }
    }


    exit(0);
}

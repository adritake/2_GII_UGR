#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

void calculaPrimos (int minimo, int maximo ){

    int i, min;
    int  primo;         //Uso de primo como bool


    for( min = minimo; min <= maximo; min++ )

        primo = 1;

        for( i = 0; i <= sqrt(min) && primo; i++){

            if( min % i == 0)         //Si el argumento es divisible por i...
                primo = 0;

        }

        if( primo )
            printf("%d ", min);

}


int main( int argc, char *argv[]){

    if( argc != 3 || argv[1] > argv[2]){
        perror("\nUso: ./Ejercicio5 <min> <max>");
        exit(-1);
    }

    int min, max, mitad;
    pid_t PID;
    int fd1[2],fd2[2];

    //Inicialización de los argumentos
    min = atoi( argv[1] );
    max = atoi( argv[2] );
    mitad = (min + max) / 2;

    //Creación de los pipes

    pipe(fd1);
    pipe(fd2);

    if ( (PID = fork())<0) {    //Creación del primer hijo
        perror("\nError en el primer fork");
        exit(-1);
    }
////////////PADRE E HIJO 1///////////////////////////////
    if( PID == 0){
        /////////////////// HIJO 1  ////////////////////////////////
        close( fd1[0] );                      //Ajuste de los descriptores para el hijo 1
        close( STDOUT_FILENO );
        dup( fd1[1] );

        calculaPrimos( min, mitad);         //Calculo de primos
        printf("\nHijo uno finalizado.");
        exit(0);

    }
    else{
        ////////////////////////////// PADRE //////////////////////////////
        if ( (PID = fork())<0) {        //Creación del segundo hijo por el padre PID != 0
            perror("\nError en el segundo fork");
            exit(-1);
        }



        if( PID == 0){
            /////////////////// HIJO 2  ////////////////////////////
            close( fd2[0] );                          //Ajuste de los descriptores para el hijo 2
            close( STDOUT_FILENO );
            dup( fd2[1] );

            calculaPrimos(mitad, max);              //Calculo de primos
            printf("\nHijo dos finalizado.");
            exit(0);
        }
        else{
            //////////////////////// PADRE ///////////////////////////

            close(fd1[1]);                  //Ajuste de los descriptores para el padre
            close(STDIN_FILENO);
            dup(fd1[0]);

            execlp("echo","echo",NULL);     //Lectura del primer cauce


            close(fd2[1]);                  //Ajuste de los descriptores para el padre
            close(fd1[0]);
            dup(fd2[0]);

            execlp("echo","echo",NULL);     //Lectura del primer cauce

        }

    }
}

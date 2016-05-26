#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>




int main( int argc, char *argv[]){

    if( argc != 3 && argv[1] < argv[2]){
        perror("\nUso: ./Ejercicio5 <min> <max>");
        exit(-1);
    }

    int min, max, mitad,valor;
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
        perror("\nHijo 1 calculando primos...");
        close( fd1[0] );                      //Ajuste de los descriptores para el hijo 1
        close( STDOUT_FILENO );
        dup( fd1[1] );

        execlp("./Ejercicio5esclavo","Ejercicio5esclavo",mitad,max,NULL);

        exit(0);

    }

    ////////////////////////////// PADRE //////////////////////////////
    if ( (PID = fork())<0) {        //Creación del segundo hijo por el padre PID != 0
        perror("\nError en el segundo fork");
        exit(-1);
    }



    if( PID == 0){
        /////////////////// HIJO 2  ////////////////////////////
        perror("\nHijo 2 calculando primos...");
        close( fd2[0] );                          //Ajuste de los descriptores para el hijo 2
        close( STDOUT_FILENO );
        dup( fd2[1] );

        execlp("./Ejercicio5esclavo","Ejercicio5esclavo",mitad,max,NULL);

        exit(0);
    }

    //////////////////////// PADRE ///////////////////////////
    close(fd1[1]);                  //Ajuste de los descriptores para el padre


    while( read(fd1[0],&valor, sizeof(int)) > 0)
        printf("%d ", valor);


    close(fd1[0]);

    printf("\nPrueba 1");

    close(fd2[1]);                  //Ajuste de los descriptores para el padre
    while( read(fd2[0],&valor, sizeof(int)) > 0)
        printf("%d ", valor);
    close(fd2[0]);

    printf("\nPrueba 2");




}

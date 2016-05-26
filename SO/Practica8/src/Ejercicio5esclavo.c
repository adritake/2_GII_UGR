#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>

int esPrimo (int n){

    int i;
    int  primo;         //Uso de primo como bool



    primo = 1;

    for( i = 0; i <= sqrt(n) && primo; i++){

        if( n % i == 0)         //Si el argumento es divisible por i significa que no es primo
            primo = 0;

    }

    return primo;

}

int main( int argc, char *argv[]){


    if( argc != 3 && argv[1] < argv[2]){
        perror("\nUso: ./Ejercicio5esclavo <min> <max>");
        exit(-1);
    }

    int i, min, max;
    char buffer[33];

    min = atoi( argv[1] );
    max = atoi( argv[2] );

    for( i = min; i <= max; i++)

        if( esPrimo(i))
            write(STDOUT_FILENO, &i , sizeof(int));

    exit(0);
}

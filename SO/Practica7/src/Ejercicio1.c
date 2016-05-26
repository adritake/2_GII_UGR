
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] ){

    if(argc != 2){
        printf("Uso: ./Ejercicio1 <n_entero>\n");
        exit(-1);
    }

    int numero = atoi(argv[1]);

    //Guardo el PID actual, que va a ser el del padre
    pid_t pid_Padre = getpid();

    //Creo un proceso hijo
    fork();

    //Si el PID actual es el del padre hace esto
    if( getpid() == pid_Padre ){

        if( numero % 4 == 0)
            printf("El proceso padre dice que el numero es divisible por cuatro.\n");
        else
            printf("El proceso padre dice que el numero no es divisible por cuatro.\n");


    }

    //Si el PID actual es el del hijo hace esto
    else{

        if( numero % 2 == 0)
            printf("El proceso hijo dice que el numero es par.\n");
        else
            printf("El proceso hijo dice que el numero es impar.\n");


    }

    exit(0);


}

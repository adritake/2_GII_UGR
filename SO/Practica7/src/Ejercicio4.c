#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

    const int HIJOS = 5;
    int n_hijos = HIJOS;
    int i;
    pid_t pid_padre = getpid();
    pid_t pid_hijo;

    for( i = 0; i < HIJOS; i++ ){

        fork();
        //Si es el padre espera y almacena el pid del hijo que termina
        //Luego imprime y reduce el numero de hijos
        if( getpid() == pid_padre){

            pid_hijo = waitpid(-1);
            printf("\nAcaba de finalizar mi hijo con pid: %d", pid_hijo);
            printf("\nSolo me quedan %d hijos vivos",n_hijos);
            n_hijos--;

        }
        //Si no es el padre se imprime qué hijo es
        else{
            printf("\nSoy el hijo %d", getpid());

            exit(0);
        }



    }


    exit(0);






}

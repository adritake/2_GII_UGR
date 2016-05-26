
#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int contador[30] = {0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0};
static void sig_USR_hdlr( int i ){

    contador[i]++;
    printf("\n La señal %d , se ha realizado %d veces. " , i , contador[i]);

}

int main ( int argc , char *argv[]){

    struct sigaction sig_USR_nact;
    sig_USR_nact.sa_handler = sig_USR_hdlr;
    sigemptyset(&sig_USR_nact.sa_mask);

    sig_USR_nact.sa_flags = SA_RESTART;

    int i;
    for ( i = 1 ; i<=60 ; i++){
        if (sigaction(i, &sig_USR_nact, NULL) < 0){
            printf("error en el manejador");
        }
    }

    while(1);


}

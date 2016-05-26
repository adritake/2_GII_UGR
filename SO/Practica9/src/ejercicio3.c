
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main( int argc, char *argv[]){

    sigset_t mascara;

    sigemptyset( &mascara );

    sigfillset( &mascara );

    sigdelset( &mascara, SIGUSR1 );

    sigsuspend( &mascara );
    
}

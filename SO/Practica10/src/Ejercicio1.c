#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>


int main( int argc, char *argv[] ){



    if( argc != 4 ){

        perror("Uso: ./Ejercicio1 orden < ó > archivo" );
        exit(0);
    }

    int fd;

    if( strcmp(argv[2],">") ==0){

        fd = open( argv[3],  O_CREAT | O_WRONLY );
        close(STDOUT_FILENO);
        fcntl(fd, F_DUPFD,STDIN_FILENO);
        execlp( argv[1],"",NULL);

    }
    else if ( strcmp(argv[2],"<") ==0){

        fd = open( argv[3], O_RDONLY);
        close(STDIN_FILENO);
        fcntl(fd, F_DUPFD,STDIN_FILENO);
        execlp( argv[1],"",NULL);
    }



    close(fd);
    


}

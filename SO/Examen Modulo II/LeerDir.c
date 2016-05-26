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
    	perror("\nUso LeerDir <path>");
    	exit(-1);
    }

    //Creacion de variables
    int n = 1,i,fd;
    char *directorio = argv[1];
    char *nombre_archivo;
    char tipoArchivo[30];
    DIR *dir = opendir( directorio );          //Abrimos el directorio que le pasamos como argumento
    struct dirent *struct_dir;
    struct stat atributos;
    char buf[256];

    //Creamos el archivo donde se escribe el nombre de las entradas del directorio
    fd = open( "archivosEnlace.txt", O_CREAT | O_WRONLY , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP  );

    while( n != 0){

        printf( "\nIngrese un numero: \n");
        scanf("%d",&n);

        for( i = 0; i <= n && struct_dir != NULL; i++){

            //Vamos avanzando en las entradas hasta que llegamos a n o a NULL que es el final
            struct_dir = readdir( dir );
            //Se almacena en atributos el los atributos de la entrada actual
            stat( struct_dir->d_name ,&atributos);

        }

        nombre_archivo = struct_dir->d_name;        //Se guarda el nombre

        if( struct_dir != NULL ){

            //Comprobacion del tipo de archivo
            if(S_ISREG(atributos.st_mode)) strcpy(tipoArchivo,"Regular");
    		else if(S_ISDIR(atributos.st_mode)) strcpy(tipoArchivo,"Directorio");
    		else if(S_ISCHR(atributos.st_mode)) strcpy(tipoArchivo,"Especial de caracteres");
    		else if(S_ISBLK(atributos.st_mode)) strcpy(tipoArchivo,"Especial de bloques");
    		else if(S_ISFIFO(atributos.st_mode)) strcpy(tipoArchivo,"Tubería con nombre (FIFO)");
    		else if(S_ISLNK(atributos.st_mode)) strcpy(tipoArchivo,"Enlace relativo (soft)");
    		else if(S_ISSOCK(atributos.st_mode)) strcpy(tipoArchivo,"Socket");
    		else strcpy(tipoArchivo,"Tipo de archivo desconocido");

            //Se imprime por pantalla sus caracteristicas
            printf( "%s:   Numero de enlaces duros: %d     Tamaño: %d     Tipo: %s\n\n", nombre_archivo, (int)atributos.st_nlink, (int)atributos.st_size, tipoArchivo  );

            //Se guarada en el archivo sus caracteristicas
            sprintf( buf,"%s:   Numero de enlaces duros: %d     Tamaño: %d     Tipo: %s\n\n", nombre_archivo, (int)atributos.st_nlink, (int)atributos.st_size, tipoArchivo  );
            write( fd , buf, sizeof(buf) + 1);
        }
        else
            printf("\nNo existe esa entrada.");






    }

    exit(0);
}

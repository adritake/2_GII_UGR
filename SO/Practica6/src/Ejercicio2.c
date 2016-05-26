#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<dirent.h>

int main( int argc, char *argv[] ){

	if( argc != 3 ){
		printf("\nUso: Ejercicio2 <directorio> <nº octal de 4 digitos>");
		exit(-1);
	}

	char *directorio = argv[1];
	int permisos = atoi(argv[2]);
	int permisos_antiguos;
	int permisos_nuevos;
	struct stat carac;


	DIR *direc = opendir( directorio );
	struct dirent *di;

	while( ( di = readdir(direc)) != NULL ){

		//Alamaceno en carac las estadisticas del fichero actual
		stat( di->d_name, &carac);
		//Almaceno los pemisos antiguos
		permisos_antiguos = (int)carac.st_mode;
		//Cambio los permisos
		chmod( di->d_name, permisos);
		//Almaceno los pemisos nuevos
		stat( di->d_name, &carac);
		permisos_nuevos = (int)carac.st_mode;

		printf("%s :	%d	%d \n", di->d_name, permisos_antiguos, permisos_nuevos );
	}



	exit(0);
}

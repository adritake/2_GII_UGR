#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>


int main( int argc, char *argv[] ){

  int fd, fout, size, bloques, tam_cadena, aux, inicio, fin;
  char linea1[] = "El número de bloques es ";
  char linea_bloque[] = "\nBloque ";
  char buffer[81];
  char numero[50];

  if( argc == 1){

    if( (fd=open( "archivo.txt",O_CREAT|O_RDONLY,S_IRUSR|S_IWUSR) )<0) {
      printf("\nError %d en open del fichero de entrada",errno);
      perror("\nError en open del fichero de entrada");
      exit(-1);
    }

  }
  else{

    if( (fd=open( argv[1],O_CREAT|O_RDONLY,S_IRUSR|S_IWUSR))<0 ) {
      printf("\nError %d en open del fichero de entrada",errno);
      perror("\nError en open del fichero de entrada");
      exit(-1);
    }

  }

  //Creación del fichero salida.txt

  if( (fout=open( "salida.txt",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR))<0 ) {
    printf("\nError %d en open del fichero de salida",errno);
    perror("\nError en open del fichero de salida");
    exit(-1);
  }


  //Primero averiguo el tamaño del archivo
  //Esta es la unica manera que he encontrado de averiguarlo
  FILE *faux;
  faux=fopen(argv[1],"r");
  fseek(faux, 0L, SEEK_END);
  size= ftell(faux);
  fclose(faux);





  //Numero de bloques

  bloques = size / 80;              //Divido entre el tamaño de los bloques
  if( (bloques % 80) > 0 )          //Si la división no es exacta quiere decir que necesitamos un bloque mas para ese pico de bytes que sobran
    bloques++;

//ESCRITURA DE LA PRIMERA LINEA
  if( write( fout, linea1, 25) != 25) { //Escribe en el archivo "El número de bloques es "
    perror("\nError en primer write");
    exit(-1);
  }

  sprintf( numero, "%d", bloques);  //Transformación de entero a char

  aux=bloques;
  for(tam_cadena = 0; aux != 0 ;tam_cadena++) //Cálculo del tamaño de la la cadena
    aux /= 10;



  if( write( fout, numero, tam_cadena) != tam_cadena) {       //Escritura del numero de bloques
    perror("\nError en la escritura del numero de bloques");
    exit(-1);
  }


  if( write( fout, "\n", 1) != 1) {                         //Escritura del retorno de carro
    perror("\nError en la escritura del retorno de carro");
    exit(-1);
  }

//ESCRITURA DE LOS BLOQUES
  int i;
  for( i=1; i<= bloques; i++){

    if( write( fout, linea_bloque, 8) != 8) {                         //Escritura de la linea de bloque
        perror("\nError en la escritura de la linea de bloque");
        exit(-1);
    }

    sprintf( numero, "%d", i);  //Transformación de entero a char

    aux=i;
    for(tam_cadena = 0; aux != 0 ;tam_cadena++) //Cálculo del tamaño de la la cadena
      aux /= 10;

    if( write( fout, numero, tam_cadena) != tam_cadena ) {                         //Escritura del numero de bloque
        perror("\nError en la escritura del numero de bloque");
        exit(-1);
    }

    if( write( fout, "\n", 1) != 1) {                          //Escritura del retorno de carro
      perror("\nError en la escritura del retorno de carro");
      exit(-1);
    }



    if( read( fd, buffer, 80) != 80) {                        //Lectura del archivo de entrada
      perror("\nError en la lectura del buffer");
      exit(-1);
    }


    if( write( fout, buffer, 80) != 80) {                        //Escritura en el archivo de salida
      perror("\nError en la escritura del buffer");
      exit(-1);
    }

  }


}

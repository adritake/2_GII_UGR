#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char ** argv)
{

    if (argc<2){
		printf("Falta tamaño de matriz y vector\n");
		exit(-1);
	}


    unsigned int N = atoi(argv[1]);

    double *v1, *v2, **M;
    v1 = (double*) malloc(N*sizeof(double));// malloc necesita el tamaño en bytes
    v2 = (double*) malloc(N*sizeof(double)); //si no hay espacio suficiente malloc devuelve NULL
    M = (double**) malloc(N*sizeof(double *));
    int i,j,suma;


    for (i=0; i<N; i++){
		M[i] = (double*) malloc(N*sizeof(double));
		if ( M[i]==NULL ){
			printf("Error en la reserva de espacio para los vectores\n");
			exit(-2);
		}
	}



    for( i = 0; i < N; i++)
        for( j = 0; j < N; j++)

            if( j < i)  M[i][j] = 0;
            else        M[i][j] = j;

    for( i = 0; i < N; i++) v1[i] = i;


    for( i = 0; i < N; i++){
        suma = 0;
        for( j = i; j < N; j++){
            suma += M[i][j] * v1[j];
        }
        v2[i] = suma;
    }

    printf("\nVector solucion: \n");
    for( i = 0; i < N; i++) printf( "%f ",v2[i]);
    printf("\n");



}

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

    double **A, **B,**C;
    A = (double**) malloc(N*sizeof(double *));
    B = (double**) malloc(N*sizeof(double *));
    C = (double**) malloc(N*sizeof(double *));
    int i,j,k;
    double suma;

    for (i=0; i<N; i++){
        A[i] = (double*) malloc(N*sizeof(double));
		B[i] = (double*) malloc(N*sizeof(double));
        C[i] = (double*) malloc(N*sizeof(double));
		if ( B[i]==NULL || C[i]==NULL){
			printf("Error en la reserva de espacio para los vectores\n");
			exit(-2);
		}
	}


    for( i = 0; i < N; i++)
        for( j = 0; j < N; j++){
            B[i][j]=j+1;
            C[i][j]=j+1;
        }

    for( i = 0; i < N ; i++)
        for( j = 0; j < N; j++){
            A[i][j] = 0;
            for( k = 0; k < N; k++){
                A[i][j] = A[i][j] + B[i][k] * C[k][j];

            }

        }

    printf("\nMatriz B: \n");
    for( i = 0; i < N; i++){
        for( j = 0; j <N; j++)
            printf( "%f ",B[i][j]);
        printf("\n");
    }
    printf("\nMatriz C: \n");
    for( i = 0; i < N; i++){
        for( j = 0; j <N; j++)
            printf( "%f ",C[i][j]);
        printf("\n");
    }

    printf("\nMatriz solucion: \n");
    for( i = 0; i < N; i++){
        for( j = 0; j <N; j++)
            printf( "%f ",A[i][j]);
        printf("\n");
    }




}

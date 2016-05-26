#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>
#include <chrono>
#include <ctime>
#include <ratio>
#include <xmmintrin.h>

 double **A, **B,**C;





void Multiplica( double ** a, double ** b, double ** c, int tam){


   for( int i = 0; i < tam ; i++)
      for( int j = 0; j < tam; j++){
           a[i][j] = 0;
           for( int k = 0; k < tam; k++){
               a[i][j] = a[i][j] + b[i][k] * c[k][j];
               _mm_prefetch(b[i+32],_MM_HINT_T0);
               //_mm_prefetch(c[i+32],_MM_HINT_T0);

           }

      }

}



int main(int argc, char ** argv)
{


      using namespace std::chrono;

       if (argc<2){
   		printf("Falta tamaño de matriz y vector\n");
   		exit(-1);
   	}

      high_resolution_clock::time_point start, stop;
      duration<double> tiempo;


       unsigned int N = atoi(argv[1]);


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

       start = high_resolution_clock::now();
       Multiplica( A, B, C, N);
       stop = high_resolution_clock::now();

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

       tiempo =  duration_cast< duration<double> >(stop-start);

       printf("Tiempo= %f\n",tiempo);
    }

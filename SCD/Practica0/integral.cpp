#include <iostream>
#include <pthread.h>
#include "fun_tiempo.h"

using namespace std ;


const unsigned long n = 4;

const unsigned long m = 1000;

double resultado_parcial[n];

double f ( double x ){
	return 4.0/(1+x*x) ;
}

void * funcion_hebra( void * ih_void ){

	unsigned long ih = ( unsigned long) ih_void;
	double sumap = 0.0;

	for( unsigned long i = ih*(m/n); i < ih *(m/n) + (m/n); i++){
		sumap += f( (i+0.5)/m );
	}

	resultado_parcial[ih] = sumap/(m/ih);


}

double calcular_integral_concurrente(){

	pthread_t hebra[n];
	double resultado=0.0;

	for( unsigned long i = 0 ; i < n ; i++ ){
        void * arg_ptr = (void *) i ;
        pthread_create( &(hebra[i]), NULL, funcion_hebra, arg_ptr );
    }

    for(int i=0; i<n; i++)
        pthread_join(hebra[i],NULL);

    for( int i=0; i < n; i++)
        resultado+=resultado_parcial[n];

    return resultado;
    cout<<"Resultado:"<<resultado;
}

int main(){


    struct timespec inicio = ahora() ;



    cout<< " La integral es:"<< calcular_integral_concurrente;
    struct timespec fin = ahora() ;
    cout << "\ntiempo transcurrido == "<< duracion( &inicio, &fin )<< " seg." << endl ;






}




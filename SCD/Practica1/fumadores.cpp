#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>      // incluye "time(....)"
#include <unistd.h>    // incluye "usleep(...)"
#include <stdlib.h>    // incluye "rand(...)" y "srand"
#include <stdio.h>


using namespace std;

const int FUMADORES = 3;

//Creación de semáforos
sem_t puede_fabricar;
sem_t puede_fumar[FUMADORES];








/*
   Al fumador 0 le falta tabaco,
   al fumador 1 le falta papel y
   al fumador 2 le falta cerillas

*/


// ----------------------------------------------------------------------------
// función que simula la acción de fumar  como un retardo aleatorio de la hebra


void * fumar( void * ih_void) {


	//  inicializa la semilla aleatoria  (solo la primera vez)



  unsigned long caso = ( unsigned long) ih_void;


	while (true){

		if( caso == 0 ){

			cout<<"El fumador 1 esta esperando el tabaco.\n";
			sem_wait( &(puede_fumar[0]) );
			cout<<"El fumador 1 ha recibido el tabaco.\n";
		}
		else if( caso == 1 ){

			cout<<"El fumador 2 esta esperando el papel.\n";
			sem_wait( &(puede_fumar[1]) );
			cout<<"El fumador 2 ha recibido el papel.\n";
		}
		else if ( caso == 2){

			cout<<"El fumador 3 esta esperando las cerillas.\n";
			sem_wait( &(puede_fumar[2]) );
			cout<<"El fumador 3 ha recibido las cerillas.\n";
		}

		// calcular un numero aleatorio de milisegundos (entre 1/10 y 2 segundos)
		const unsigned miliseg = 100U + (rand() % 1900U) ;

		// retraso bloqueado durante 'miliseg' milisegundos
		cout<<"El fumador "<< caso+1<< " ha comenzado a fumar.\n";
		usleep( 1000U*miliseg );
		cout<<"El fumador "<< caso+1 << " ha terminado de fumar.\n";

		sem_post( &puede_fabricar );

	}
}


//Los ingredientes se corresponden con 0="tabaco", 1="papel", 2="cerillas"
bool primera_vez = true ;
void * estanquero(void *ih_void){

	if ( primera_vez ){
			primera_vez = false ;
   		srand( time(NULL) );
	}


	while(true){

		sem_wait( &puede_fabricar );
		int ing = rand() % 3 +1 ;


		if(ing==1){

			cout<<"El estanquero ha producido tabaco.\n";
			sem_post( &(puede_fumar[0]) );

		}
		else if (ing ==2){

			cout<<"El estanquero ha producido papel.\n";
			sem_post( &(puede_fumar[1]) );

		}
		else if (ing == 3){

			cout<<"El estanquero ha producido cerillas.\n";
			sem_post( &(puede_fumar[2]) );

		}

	}

}



int main(){

	pthread_t hebra[FUMADORES];
	pthread_t estan;

	sem_init ( &puede_fabricar, 0, 1);


	for( unsigned int i = 0 ; i < FUMADORES ; i++ ){

  	sem_init( &(puede_fumar[i]), 0, 0 );
  }



	void * arg_ptr;

	for( unsigned long i = 0 ; i < FUMADORES ; i++ ){
					arg_ptr = (void *) i ;
					pthread_create( &(hebra[i]), NULL, fumar, arg_ptr );
	}

	pthread_create( &estan, NULL, estanquero,NULL);


	pthread_join(estan,NULL);

	for(int i=0; i<FUMADORES; i++)
        pthread_join(hebra[i],NULL);





	return 0 ;
}

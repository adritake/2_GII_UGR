#include <iostream>
#include <cassert>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>

using namespace std ;

// ---------------------------------------------------------------------
// constantes
const unsigned
  num_items  = 40 ,
  tam_vector = 10 ;

// ---------------------------------------------------------------------

sem_t puede_leer;
sem_t puede_escribir;


int vector[tam_vector];

int pr=0;
void Prueba(){
	cout<<pr++<<endl;
}


unsigned producir_dato()
{
  static int contador = 0 ;
  cout << "producido: " << contador << endl << flush ;
  return contador++ ;
}
// ---------------------------------------------------------------------

void consumir_dato( int dato )
{
    cout << "dato recibido: " << dato << endl ;
}
// ---------------------------------------------------------------------

void * productor( void * ){

  
  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato = producir_dato() ;

    // falta: insertar "dato" en el vector
    // ................

    sem_wait(&puede_escribir);
    vector[i]=dato;

    sem_post(&puede_leer);


  }
  return NULL ;
}
// ---------------------------------------------------------------------

void * consumidor( void * ){

  

  for( unsigned i = 0 ; i < num_items ; i++ )
  {
    int dato ;

    // falta: leer "dato" desde el vector intermedio
    // .................

    sem_wait(&puede_leer);

    dato = vector[i];

    consumir_dato( dato ) ;

    sem_post(&puede_escribir);
  }
  return NULL ;
}
//----------------------------------------------------------------------

int main()
{

  // falta: crear y poner en marcha las hebras, esperar que terminen
  // ....

  sem_init(&puede_escribir,0,1);
  sem_init(&puede_leer,0,0);

/*
  for( unsigned long i = 0 ; i < n ; i++ ){
        void * arg_ptr = (void *) i ;
        pthread_create( &(hebra[i]), NULL, funcion_hebra, arg_ptr );
    }
    */

  pthread_t hebra_productora;
  pthread_t hebra_consumidora;
  pthread_create(&hebra_productora,NULL, productor,NULL);
  pthread_create(&hebra_consumidora,NULL, consumidor,NULL);

  pthread_join(hebra_consumidora,NULL);
  pthread_join(hebra_productora,NULL);



   return 0 ;
}

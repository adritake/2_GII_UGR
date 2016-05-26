#include <iostream>
#include <time.h>      // incluye "time"
#include <unistd.h>    // incluye "usleep"
#include <stdlib.h>    // incluye "rand" y "srand"
#include <mpi.h>

using namespace std;

void Filosofo( int id, int nprocesos);
void Tenedor ( int id, int nprocesos);
void Camarero();

// ---------------------------------------------------------------------


// ETIQUETA 0   ----->  Soltar tenedor
// ETIQUETA 1   ----->  Coger tenedor
// ETIQUETA 2   ----->  Sentarse
// ETIQUETA 3   ----->  Levantarse


// ---------------------------------------------------------------------


const int CAM = 10;     //Proceso camarero

int main( int argc, char** argv )
{
   int rank, size;

   srand(time(0));

   //Se incializa el comunicador con los argumentos del main
   MPI_Init( &argc, &argv );

   //Determina el identificador del proceso en un comunicador.
   MPI_Comm_rank( MPI_COMM_WORLD, &rank );

   //Determina el número de procesos de un comunicador.
   MPI_Comm_size( MPI_COMM_WORLD, &size );

   //Se comprueba el numero de procesos( En este caso once porque contamos el camarero)
   if( size != 11 )
   {
      if( rank == 0)
         cout<<"El numero de procesos debe ser 11" << endl << flush ;
      MPI_Finalize( );
      return 0;
   }

   //Hay que comprobar  si es el proceso camarero
   if( rank == CAM)
      Camarero();
   else if ((rank%2) == 0 )
      Filosofo(rank,size); // Los pares son Filosofos
   else
      Tenedor(rank,size);  // Los impares son Tenedores

   MPI_Finalize( );
   return 0;
}
// ---------------------------------------------------------------------

void Filosofo( int id, int nprocesos )
{
   int izq = (id+1) % (nprocesos-1);
   int der = ((id+nprocesos-1)-1) % (nprocesos-1);
   int buf = 1;
   MPI_Status status;

   while(1)
   {

      //Establecimiento de los tenedores que le corresponde al filosofo
      //filosofo solicita sentarse
      cout<<"Filosofo "<<id<< " solicita sentarse"<<endl<<flush;

      //Indica al camarero la peticion de sentares
      MPI_Ssend( &buf, 1, MPI_INT, CAM, 2, MPI_COMM_WORLD);

      //Espera respuesta del camarero
      MPI_Recv( &buf, 1, MPI_INT, CAM, 2, MPI_COMM_WORLD, &status);




      // Solicita tenedor izquierdo
      cout << "Filosofo "<<id<< " solicita tenedor izq ..." << izq << endl << flush;
      // ...
      MPI_Ssend( &buf, 1, MPI_INT, izq, 1, MPI_COMM_WORLD);

      // Solicita tenedor derecho
      cout <<"Filosofo "<<id<< " coge tenedor der ..." << der << endl << flush;
      // ...
      MPI_Ssend( &buf, 1, MPI_INT, der, 1,MPI_COMM_WORLD );

      cout<<"Filosofo "<<id<< " COMIENDO"<<endl<<flush;
      sleep((rand() % 3)+1);  //comiendo

      // Suelta el tenedor izquierdo
      cout <<"Filosofo "<<id<< " suelta tenedor izq ..." << izq << endl << flush;
      // ...
      MPI_Ssend( &buf,1,MPI_INT,izq,0,MPI_COMM_WORLD);


      // Suelta el tenedor derecho
      cout <<"Filosofo "<<id<< " suelta tenedor der ..." << der << endl << flush;
      // ...
      MPI_Ssend( &buf,1,MPI_INT,der,0,MPI_COMM_WORLD);

      //Se levanta
      cout<<"Filosofo "<<id<< " se levanta."<<endl<<flush;
      MPI_Ssend( &buf, 1, MPI_INT,  CAM, 3, MPI_COMM_WORLD);


      // Piensa (espera bloqueada aleatorio del proceso)
      cout << "Filosofo " << id << " PENSANDO" << endl << flush;
      // espera bloqueado durante un intervalo de tiempo aleatorio
      // (entre una décima de segundo y un segundo)
      usleep( 1000U * (100U+(rand()%900U)) );
 }
}
// ---------------------------------------------------------------------

void Tenedor(int id, int nprocesos)
{
  int buf;
  MPI_Status status;
  int Filo;

  while( true )
  {
    // Espera un peticion desde cualquier filosofo vecino ...
    // ...
    MPI_Recv( &buf, 1, MPI_INT, MPI_ANY_SOURCE, 1,MPI_COMM_WORLD,&status);
    // Recibe la peticion del filosofo ...
    // ...
    Filo = status.MPI_SOURCE;
    cout << "Ten. " << id << " recibe petic. de " << Filo << endl << flush;

    // Espera a que el filosofo suelte el tenedor...
    // ...
    MPI_Recv( &buf, 1, MPI_INT, Filo, 0,MPI_COMM_WORLD, &status);
    cout << "Ten. " << id << " recibe liberac. de " << Filo << endl << flush;
  }
}
// ---------------------------------------------------------------------

void Camarero(){

    int n_fil=0,buf;
    MPI_Status status;
    int Filo;

    while(1) {

        //Se pone la etiqueta del mensaje a 0
        status.MPI_TAG=0;

        //Se comprueba el numero de filosofos sentados
        if( n_fil < 4 )
            //Si es menor que cuatro se pueden sentar o levantar ( Etiqueta MPI_ANY_TAG)
            MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        else
            //Si es mayor que cuatro solo se pueden levantar ( Etiqueta 3)
            MPI_Probe(MPI_ANY_SOURCE,3, MPI_COMM_WORLD, &status);


        //Si la etiqueta es 2 quiere decir que es una peticion de sentarse
        if( status.MPI_TAG==2 ){

            //Se establece Filo al nº de proceso que hace la peticion
            Filo = status.MPI_SOURCE;

            //Se recive el mensaje de peticion de sentarse de un filosofo
            MPI_Recv( &buf, 1, MPI_INT, Filo, 2, MPI_COMM_WORLD,&status);

            //Se aumenta el nº de filosofos sentados
            n_fil++;

            //Se le indica que se puede sentar
            MPI_Ssend( &buf, 1, MPI_INT, Filo, 2, MPI_COMM_WORLD);
            cout<< "Se ha sentado el filosofo "<< Filo << " .Hay " << n_fil << " filosofos sentados." <<endl<<flush;

        }

        //Si la etiqueta es 3 es una petición de levantarse
        else if (status.MPI_TAG==3) {

            //Se establece Filo al nº de proceso que hace la peticion
            Filo = status.MPI_SOURCE;

            //Se recive el mensaje de peticion de levantarse de un filosofo
            MPI_Recv( &buf, 1, MPI_INT, Filo, 3, MPI_COMM_WORLD,&status);

            //Se reduce el número de filosofos sentados
            n_fil--;
            cout<< "Se ha levantado el filosofo "<< Filo << " .Hay " << n_fil << " filosofos sentados." <<endl<<flush;

        }

    }


}

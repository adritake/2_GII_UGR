#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <utility>


using namespace std;

typedef pair<int, int> coordenada;
const int MAX_MATRIZ = 500;



void leeLaberinto( string fichero,  char ** M){

  ifstream fi(fichero);
  char elemento;

  int i = 0, j = 0;

  elemento = fi.get();

  while( !fi.eof() ){


    if( elemento == '\n'){
      i++;
      j = 0;
    }

    if( elemento != '\n'){
        M[i][j] = elemento;
        j++;
    }

    elemento = fi.get();


  }

  fi.close();



}


//Función que dice si una solución es válida
// Básicamente comprueba si se ha llegado a la casilla final
bool AlcanzaSolucion(vector< coordenada> &V, int tam){

   bool factible = false;
   auto it = V.end();

   if( !V.empty() ){

      --it;

      if( (*it).first == tam-1 && (*it).second == tam-1)
         factible = true;

   }


   return factible;

}

//Función que dado un estado en el laberinto devuelve si hay que hacer BackTracking
bool Factible( coordenada c, char ** maze, int ** frec , int tam ){

   int i = c.first;
   int j = c.second;

   bool BT = false;
   bool arriba , abajo , izquierda , derecha ;

   if( i > 0)     arriba = maze[i-1][j] == '#'|| frec[i-1][j] == 1;
   if( i < tam-1) abajo = maze[i+1][j] == '#'|| frec[i+1][j] == 1;
   if( j > 0 )    izquierda = maze[i][j-1] == '#'|| frec[i][j-1] == 1;
   if( j < tam-1) derecha = maze[i][j+1] == '#'|| frec[i][j+1] == 1;

   if ( i == 0 ){

      if( j == 0)
         BT = derecha && abajo;
      else if ( j == tam -1)
         BT = izquierda && abajo;
      else
         BT = derecha && izquierda && abajo;

   }
   else if ( i == tam -1){

      if( j == 0)
         BT = derecha && arriba;
      else if ( j == tam -1)
         BT = izquierda && arriba;
      else
         BT = izquierda && derecha && arriba;
   }
   else if ( j == 0 ){

      BT = arriba && abajo && derecha;

   }
   else if ( j == tam -1 ){

      BT = arriba && abajo && izquierda;

   }

   else

      BT = izquierda && derecha && arriba && abajo;

   return BT;


}

//Función que devuelve la siguiente posición posible
coordenada SiguientePos( coordenada c, char ** maze, int ** frec, int tam ){

   int i = c.first;
   int j = c.second;

   coordenada sig;

   bool arriba = false, abajo = false , izquierda = false , derecha = false ;

   //Se comprueba en cada cardinalidad si hay pasillo y no se ha pasado por el con anterioridad
   if( i > 0)     arriba = maze[i-1][j] == 'x' && frec[i-1][j] == 0;
   if( i < tam-1) abajo = maze[i+1][j] == 'x' && frec[i+1][j] == 0;
   if( j > 0 )    izquierda = maze[i][j-1] == 'x' && frec[i][j-1] == 0;
   if( j < tam-1) derecha = maze[i][j+1] == 'x' && frec[i][j+1] == 0;

   // De mayor a menor prioridad


   if( derecha )                          //Hacia la derecha
      sig = make_pair( i, j+1);
   else if( abajo )                       //Hacia abajo
      sig = make_pair( i+1, j);
   else if( izquierda )                   //Hacia la izquierda
      sig = make_pair( i, j-1);
   else if( arriba )                       //Hacia arriba
      sig = make_pair( i-1, j);
   else{
      cout<<"ERROR: No debería estar aquí" <<endl;          //Si no hay siguiente posicion posible
      cout<< "Arriba    --> frec: "<< frec[i-1][j] << " elem: "<< maze[i-1][j]<<endl;
      cout<< "Abajo     --> frec: "<< frec[i+1][j] << " elem: "<< maze[i+1][j]<<endl;
      cout<< "Izquierda --> frec: "<< frec[i][j-1] << " elem: "<< maze[i][j-1]<<endl;
      cout<< "Derecha   --> frec: "<< frec[i][j+1] << " elem: "<< maze[i][j+1]<<endl;
      exit(-1);                                             //BackTracking() se encarga de dejar siempre en una posicion posible, así que si llegamos aquí algo ha fallado
   }

   return sig;

}

void BackTracking( vector<coordenada> &V, char ** maze, int ** frec , int tam){

   cout<<" ***** SE HACE BACKTRACKING*******"<<endl;

   //Nos posicionamos en el último elemento del vector
   auto it = V.end();
   --it;

   //Vamos podando posiciones hasta llegar a una en la que podemos ir por otro camino
   while( Factible(*it, maze,frec,tam) ){

      V.erase( it );
      it = V.end();
      --it;

   }




}


int main( int argc, char **argv){


  if(argc < 3){
     cout << "Uso: ./MazeBacktracking < n > <fichero>" << endl;
     exit(-1);
  }

  int tam = atoi( argv[1]);



  //Matrices necesarias para recorrer el laberinto
  char ** maze = new char * [MAX_MATRIZ];
  int ** frecuencias = new int * [MAX_MATRIZ];

  //Matriz para representar el recorrido
  char ** matriz_recorrido = new char * [MAX_MATRIZ];

  for( int i = 0; i < tam; i++){
     maze[i] = new char[tam];
     frecuencias[i] = new int[tam];
     matriz_recorrido[i] = new char[tam];
 }

  //Vector con las coordenadas que se recorren hasta la salida
  vector<coordenada> V_solucion;



  //Leemos el laberinto de un fichero
  leeLaberinto(argv[2],maze);

  /*
  // Para que las paredes del laberinto sean muros y se pueda llegar al final
  for( int i = 0; i < tam - 10 ; i ++){
     maze[i][tam-1] = 'u';
     maze[i][0] = 'u';
     maze[i][tam] = 'u';

  }
  maze[tam-1][tam-1] = 'o';
  */

  //Inicializamos la matriz de frecuencias
  for( int i = 0; i < tam ; i ++)
    for( int j = 0; j < tam ; j ++)
         frecuencias[i][j]=0;



  /*

     ***********ESQUEMA**************

    while( no se ha llegado la solucion){   //Consideramos llegar a la solucion como llegar al elemento [tam-1][tam-1]

       if( hay que hacer BackTracking ){

          BackTracking()
          pos_actual = Vector_solucion.end() --;

        }

        pos_actual = siguiente posicion posible
       frecuencia++

       Metemos pos_actual en la solucion

     }
  */


  coordenada pos_actual= make_pair(0,0);

  //Introduccion de la casilla 0,0 en la solucion
  V_solucion.push_back( pos_actual );
  frecuencias[pos_actual.first][pos_actual.second] = 1;

  while( !AlcanzaSolucion(V_solucion,tam) ){



    if ( Factible(pos_actual, maze, frecuencias, tam )){

         BackTracking( V_solucion,maze,frecuencias,tam);
         pos_actual = *(--(V_solucion.end()));


    }


   pos_actual = SiguientePos( pos_actual, maze, frecuencias,tam);
   frecuencias[pos_actual.first][pos_actual.second] = 1;

   V_solucion.push_back( pos_actual );

   cout<<"Posición actual: " << pos_actual.first << " " << pos_actual.second <<flush<<endl;

   /*
   cout<<"Pulsa una tecla para continuar..."<<endl;
   cin.get();
   */
  }



  //   Representación del recorrido    //
  for( int i = 0; i < tam ; i ++)
    for( int j = 0; j < tam ; j ++)
      matriz_recorrido[i][j] = maze[i][j];


   auto it  = V_solucion.begin();

   ofstream fout;
   fout.open("matriz_recorrido.txt");

   while( it != V_solucion.end() ){
      matriz_recorrido[(*it).first][(*it).second] = '*';
      ++it;
   }

   for( int i = 0; i < tam ; i ++){
      for( int j = 0; j < tam ; j ++)
         fout << matriz_recorrido[i][j];
      fout<<"\n";
   }

   fout.close();
}

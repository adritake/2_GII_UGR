#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include "player.h"
#include "environment.h"

using namespace std;

const double masinf=9999999999.0, menosinf=-9999999999.0;


// Constructor
Player::Player(int jug){
    jugador_=jug;
}

// Actualiza el estado del juego para el jugador
void Player::Perceive(const Environment & env){
    actual_=env;
}

double Puntuacion(int jugador, const Environment &estado){
    double suma=0;

    for (int i=0; i<7; i++)
      for (int j=0; j<7; j++){
         if (estado.See_Casilla(i,j)==jugador){
            if (j<3)
               suma += j;
            else
               suma += (6-j);
         }
      }

    return suma;
}


// Funcion de valoracion para testear Poda Alfabeta
double ValoracionTest(const Environment &estado, int jugador){
    int ganador = estado.RevisarTablero();

    if (ganador==jugador)
       return 99999999.0; // Gana el jugador que pide la valoracion
    else if (ganador!=0)
            return -99999999.0; // Pierde el jugador que pide la valoracion
    else if (estado.Get_Casillas_Libres()==0)
            return 0;  // Hay un empate global y se ha rellenado completamente el tablero
    else
          return Puntuacion(jugador,estado);
}

// ------------------- Los tres metodos anteriores no se pueden modificar


// Función que devuelve el valor segun la heurística para una casilla solo
double PuntuacionCasilla(  const Environment &estado, int jugador, int fila, int col ){

   //Puntuación de la casilla
   double punt = 0;

   //Casilla a puntuar
   int ficha_jug = estado.See_Casilla(fila,col);

   //Casillas que están al lado de la casilla a puntuar
   int casilla_actual;

   //Si es una ficha bomba del jugador 1, ponemos que la ficha pertenece al jugador 1
   if (ficha_jug == 4)        ficha_jug = 1;
   //Si es una ficha bomba del jugador 2, ponemos que la ficha pertenece al jugador 2
   else if( ficha_jug == 5)   ficha_jug == 2;
   //Si es una casilla vacía, la ponemos como si fuese una ficha puesta por el jugador actual
   else if( ficha_jug == 0 )  ficha_jug == jugador;


   //Para las 8 casillas adyacentes a la casilla actual...
   for( int i = fila -1; i <= fila +1; i++){
      for( int j = col -1; j <= col + 1; j++){

         //Si la casilla que estamos mirando no es la casilla a puntuar y la casilla que estamos mirando están dentro de los límites del tablero
         if( i != fila && j != col && i >= 0 && i < 7 && j >= 0 && j < 7){

            // Casilla adyacente a la que hay que puntuar
            casilla_actual = estado.See_Casilla(i,j);

            //Si la casilla a puntuar es la del jugador actual, miramos que no esté a lado de ninguna de su mismo color, y si es así, reducimos la puntuación
            if( (casilla_actual == ficha_jug || casilla_actual == ficha_jug + 3) && ficha_jug == jugador)
               punt -= 2;
            //En caso contrario( Está al lado de casillas de distinto color o es una casilla del adversario y está al lado de fichas del mismo color) aumentamos la puntuación.
            else
               punt ++;
         }


      }

   }


   //Se devuelve la puntuación
   return punt;



}


//Función heuriística. Devuelve la sumatoria de todas las puntuaciones de las casillas del tablero
double Heuristica( const Environment &estado, int jugador ){

   double puntuacion;

   for (int i=0; i<7; i++){

     for (int j=0; j<7; j++){

        puntuacion += PuntuacionCasilla( estado, jugador, i, j );

     }

  }


  return puntuacion;


}

// Funcion heuristica (ESTA ES LA QUE TENEIS QUE MODIFICAR)
double Valoracion(const Environment &estado, int jugador){

   int ganador = estado.RevisarTablero();

   if (ganador==jugador)
      return 99999999.0; // Gana el jugador que pide la valoracion

   else if (ganador!=0)
           return -99999999.0; // Pierde el jugador que pide la valoracion

   else if (estado.Get_Casillas_Libres()==0)
           return 0;  // Hay un empate global y se ha rellenado completamente el tablero
   else

      //Utilizo mi valoración heurísitca
      return Heuristica(estado,jugador);



}





// Esta funcion no se puede usar en la version entregable
// Aparece aqui solo para ILUSTRAR el comportamiento del juego
// ESTO NO IMPLEMENTA NI MINIMAX, NI PODA ALFABETA
void JuegoAleatorio(bool aplicables[], int opciones[], int &j){
    j=0;
    for (int i=0; i<8; i++){
        if (aplicables[i]){
           opciones[j]=i;
           j++;
        }
    }
}



double Player::PodaAlfaBeta( const Environment & T,int jugador, bool jugadorMaximizador, int prof, Environment::ActionType & accion, double alfa, double beta ){

   //Variable que indica si hay que podar
   bool poda = false;

   //Ultima acción realizada en un nodo
   int ulacc = -1;

   //Variable basura que pasamos a la función recursiva
   Environment::ActionType KK;

   //Valor heurístico del nodo
   double valor;

   //Primer nodo
   Environment hijo = T.GenerateNextMove( ulacc );

   //Valoración del tablero actual
   double valoracion_actual ;
   valoracion_actual = Valoracion( T, jugador);

   //Se hemos llegado la profundidad tope o un nodo terminal( ganador o vencedor )
   if( prof == 0 || valoracion_actual == 99999999.0 ||  valoracion_actual == -99999999.0){

      return valoracion_actual;

   }
   //Si es el jugador MAX
   else if ( jugadorMaximizador ){

         //Mientras haya acciones posibles en el nodo y no haya que podar
         while( ulacc < 8 && !poda ){

            //Seguimos recursivamente para cada accion posible en el nodo
            valor = PodaAlfaBeta( hijo, jugador,false , prof - 1, KK, alfa, beta);

            //Si el valor es mayor que alfa, actualizamos alfa y guardamos la accion
            if( valor > alfa ){

               alfa = valor;
               accion = static_cast< Environment::ActionType > ( ulacc );

            }
            //Si beta es menor que alfa se poda
            else if( beta <= alfa ){

               poda = true;


            }

            //Creamos el siguiente nodo
            hijo = T.GenerateNextMove( ulacc );
         }


         //Se devuelve alfa
         return alfa;

   }
   //En el caso del jugador min es igual solo que actualizamos beta cuando hay un valor menor que beta
   else{

      while( ulacc < 8 && !poda ){

         valor = PodaAlfaBeta( hijo, jugador, true , prof - 1, KK, alfa, beta);

         if( valor < beta ){

            beta = valor;
            accion =  static_cast< Environment::ActionType > ( ulacc );

         }
         else if( beta <= alfa ){

            poda = true;


         }

         hijo = T.GenerateNextMove( ulacc );
      }



      return beta;

   }



}



// Invoca el siguiente movimiento del jugador
Environment::ActionType Player::Think(){
    const int PROFUNDIDAD_MINIMAX = 6;  // Umbral maximo de profundidad para el metodo MiniMax
    const int PROFUNDIDAD_ALFABETA = 8; // Umbral maximo de profundidad para la poda Alfa_Beta

    Environment::ActionType accion; // acci�n que se va a devolver
    bool aplicables[8]; // Vector bool usado para obtener las acciones que son aplicables en el estado actual. La interpretacion es
                        // aplicables[0]==true si PUT1 es aplicable
                        // aplicables[1]==true si PUT2 es aplicable
                        // aplicables[2]==true si PUT3 es aplicable
                        // aplicables[3]==true si PUT4 es aplicable
                        // aplicables[4]==true si PUT5 es aplicable
                        // aplicables[5]==true si PUT6 es aplicable
                        // aplicables[6]==true si PUT7 es aplicable
                        // aplicables[7]==true si BOOM es aplicable



    double valor; // Almacena el valor con el que se etiqueta el estado tras el proceso de busqueda.
    double alpha, beta; // Cotas de la poda AlfaBeta

    int n_act; //Acciones posibles en el estado actual


    n_act = actual_.possible_actions(aplicables); // Obtengo las acciones aplicables al estado actual en "aplicables"
    int opciones[10];

    // Muestra por la consola las acciones aplicable para el jugador activo
    /*
    //actual_.PintaTablero();
    cout << " Acciones aplicables ";
    (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
    for (int t=0; t<8; t++)
      if (aplicables[t])
         cout << " " << actual_.ActionStr( static_cast< Environment::ActionType > (t)  );
    cout << endl;
    */


    //--------------------- COMENTAR Desde aqui
    /*
    cout << "\n\t";
    int n_opciones=0;
    JuegoAleatorio(aplicables, opciones, n_opciones);

    if (n_act==0){
      (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
      cout << " No puede realizar ninguna accion!!!\n";
      //accion = Environment::actIDLE;
    }
    else if (n_act==1){
           (jugador_==1) ? cout << "Verde: " : cout << "Azul: ";
            cout << " Solo se puede realizar la accion "
                 << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[0])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[0]);

         }
         else { // Hay que elegir entre varias posibles acciones
            int aleatorio = rand()%n_opciones;
            cout << " -> " << actual_.ActionStr( static_cast< Environment::ActionType > (opciones[aleatorio])  ) << endl;
            accion = static_cast< Environment::ActionType > (opciones[aleatorio]);
         }
   */

    //--------------------- COMENTAR Hasta aqui


    //--------------------- AQUI EMPIEZA LA PARTE A REALIZAR POR EL ALUMNO ------------------------------------------------


    // Opcion: Poda AlfaBeta
    // NOTA: La parametrizacion es solo orientativa
    alpha = menosinf;
    beta = masinf;
    valor = PodaAlfaBeta(actual_, jugador_,true, PROFUNDIDAD_ALFABETA , accion, alpha, beta);
    cout << "Valor MiniMax: " << valor << "  Accion: " << actual_.ActionStr(accion) << endl;
    //cout<<"Casting: "<<actual_.ActionStr( static_cast< Environment::ActionType > (0))<<endl;

    return accion;
}

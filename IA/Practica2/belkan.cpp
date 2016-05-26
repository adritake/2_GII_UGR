#include "belkan.h"
#include "conexion.h"
#include "environment.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <utility>
#include <cstring>


#include <stdlib.h>

using namespace std;



// -----------------------------------------------------------
void PasarVectoraMapaCaracteres(int fila, int columna, char m[200][200], char *v, int brujula){
  m[fila][columna]=v[0];

    switch(brujula){
        case 0: // Orientacion Norte

		m[fila-1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila-2][columna+i-1]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila-3][columna+j-2]=v[5+j];
		}
	        break;
	case 1: // Orientacion Este
		m[fila][columna+1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+i-1][columna+2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+j-2][columna+3]=v[5+j];
		}
	        break;
        case 2: // Orientacion Sur
		m[fila+1][columna]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+2][columna+1-i]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+3][columna+2-j]=v[5+j];
		}
		                break;
        case 3: // Orientacion Oeste
		m[fila][columna-1]=v[1];
		for (int i=0; i<3; i++){
		  m[fila+1-i][columna-2]=v[2+i];
		}
		for (int j=0; j<5; j++){
		  m[fila+2-j][columna-3]=v[5+j];
		}

                break;
    }

}


// -----------------------------------------------------------
void Agent::Perceive(Environment &env)
{
	env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, false);

}


bool Agent::Perceive_Remote(conexion_client &Cliente, Environment &env)
{
	bool actualizado=false;


	actualizado = env.Perceive_Remote(Cliente);
	if (actualizado)
		env.SenSorStatus(VISTA_, SURFACE_, MENSAJE_, REINICIADO_, EN_USO_, MOCHILLA_, PUNTUACION_, FIN_JUEGO_, SALUD_, true);

    return actualizado;
}


// -----------------------------------------------------------
string ActionStr(Agent::ActionType accion)
{
	switch (accion)
	{
	case Agent::actFORWARD: return "FORWARD";
	case Agent::actTURN_L: return "TURN LEFT";
	case Agent::actTURN_R: return "TURN RIGHT";
	case Agent::actIDLE: return "IDLE";
	case Agent::actPICKUP: return "PICK UP";
	case Agent::actPUTDOWN: return "PUT DOWN";
	case Agent::actPUSH: return "PUSH";
	case Agent::actPOP: return "POP";
	case Agent::actGIVE: return "GIVE";
	case Agent::actTHROW: return "THROW";
	default: return "????";
	}
}

// -----------------------------------------------------------
void Agent::ActualizarInformacion(Environment *env){
	// Actualizar mi informacion interna
	if (REINICIADO_){
		// Lo que tengas que hacer si eres reposicionado en el juego

        //Se reinician las matrices
        for( int i = 0; i < 200; i++)
            for( int j = 0; j < 200; j++){
                mapa_entorno_[i][j] = '?';
                mapa_potencial_[i][j] = 1;
            }

        //Si cambia el estado de orientado a false
        orientado = false;

        //Ya no tiene piedra
        tiene_piedra = false;

        //Se limpian las casillas de orientación
        PK1.first = 0;
        PK1.second = 0;
        PK1_ent.first = 0;
        PK1_ent.second = 0;

        PK2.first = 0;
        PK2.second = 0;
        PK2_ent.first = 0;
        PK2_ent.second = 0;

        x_ = 99;
        y_ = 99;

        REINICIADO_ = false;

	}

	switch(last_accion_){
	  case 0: //avanzar
	  switch(orientacion_){
	    case 0: // norte
		    y_--;
		    break;
	    case 1: // este
		    x_++;
		    break;
	    case 2: // sur
		    y_++;
		    break;
	    case 3: // este
		    x_--;
		    break;
	  }
	  break;
	  case 1: // girar izq
		  orientacion_=(orientacion_+3)%4;
		  break;
	  case 2: // girar dch
		  orientacion_=(orientacion_+1)%4;
		  break;
	}

	// Comprobacion para no salirme del rango del mapa
	bool algo_va_mal=false;
	if (y_<0){
		y_=0;
		algo_va_mal=true;
	}
	else if (y_>199){
		y_=199;
		algo_va_mal=true;
	}
	if (x_<0){
		x_=0;
		algo_va_mal=true;
	}
	else if (x_>199){
		x_=199;
		algo_va_mal=true;
	}

	if (algo_va_mal){
		cout << "CUIDADO: NO ESTAS CONTROLANDO BIEN LA UBICACION DE TU AGENTE\n";
	}


	PasarVectoraMapaCaracteres(y_,x_,mapa_entorno_,VISTA_,orientacion_);
	PasarVectoraMapaCaracteres(y_,x_,mapa_objetos_,SURFACE_,orientacion_);

	env->ActualizarMatrizUsuario(mapa_entorno_);

}

//Devuelve la fila y columna que dal el mensaje de un PK
void Agent::CapturaFilaColumnaPK (string mensaje, int &fila, int &columna){
	if (mensaje.substr(0,8)=="PK fila:"){
		int pos = mensaje.find('c');
		string valor = mensaje.substr(9,pos-8);
		fila = atoi(valor.c_str());

		int pos2 = mensaje.find('.');
		pos = pos+8;
		valor = mensaje.substr(pos,pos2-1);
		columna = atoi(valor.c_str());
	}
}

// -----------------------------------------------------------

Agent::ActionType Agent::Think()
{

    // Accion por defecto: avanza
    Agent::ActionType accion = actFORWARD;


    //Elige su próxima accion basándose en el potencial que le rodea( Se explica en Potencial)
    accion = Potencial();


    //Si delante tiene algo que no se puede cruzar y el potencial a elegido avanzar entonces se escoge una direccion nueva
    if( VISTA_[1] == 'B' || VISTA_[1] == 'A' || VISTA_[1] == 'P' || VISTA_[1] == 'M' || VISTA_[1] == 'D' || (SURFACE_[1] >='a' && SURFACE_[1]<='z') ){
            //GiraPotencial() es como Potencial() pero elige solo entre si es mejor girar a la izquierda o a la derecha
            if(accion == actFORWARD) accion = GiraPotencial();
    }

    if( SURFACE_[0] == '1' && !tiene_piedra ){
         accion= actPICKUP;
         tiene_piedra = true;
     }

    if( (SURFACE_[1] == 'q' || SURFACE_[3] == 'q' || SURFACE_[7] == 'q') && tiene_piedra ){
         accion= actTHROW;
         tiene_piedra=false;
     }

    //Por donde pasamos disminuimos el potencial
    mapa_potencial_[y_][x_]-=1000;

    //Si estamos sobre un PK y no estamos orientados lo guardamos
    if( VISTA_[0] == 'K' && !orientado)
        RellenaPK(y_ , x_);

    //Siempre que estemos orientados actualizamos el mapa solucion
    if( orientado )
        RellenaMapaSolucion();

    cout<<"X: "<<x_ << "   Y: "<< y_ <<endl;
    cout<< "Paso actual: "<<n_pasos<<endl;
    cout<<"Accion a realizar: ";
    if( accion == actFORWARD) cout<< " actFORWARD" <<endl;
    else if( accion == actTURN_R) cout<< " actTURN_R" <<endl;
    else if( accion == actTURN_L) cout<< " actTURN_L" <<endl;
    else if( accion == actPICKUP) cout<< " actPICKUP"<<endl;
    else if( accion == actTHROW) cout<< "actTHROW"<<endl;

    //Actualizamos la variable de pasos actual
    n_pasos++;

    //Cuando la partida esté proxima a acabarse rellenamos los huecos del mapa solución que el agente no ha podido alcanzar
    if( n_pasos > 19990)    RellenaHuecos();

    last_accion_ = accion;
	return accion;

}

//Método que almacena las cordenadas del mapa entorno de un PK y las que dice el propio PK
void Agent::RellenaPK(int i, int j){

    //Si no se ha rellenado el primer PK
    if( PK1.first == 0){

        //Almaceno las coordenadas que dice
        CapturaFilaColumnaPK( MENSAJE_, PK1.first, PK1.second);

        //Almaceno las coordenadas donde está
        PK1_ent.first = i;
        PK1_ent.second = j;
        cout<<"Se ha rellenado el primer PK, fila: "<< PK1.first << " columna: "<< PK1.second<<endl;

    }
    //Si se ha rellenado el primer PK pero el segundo no
    else if( PK2.first == 0 ){

        CapturaFilaColumnaPK( MENSAJE_, PK2.first, PK2.second);
        PK2_ent.first = i;
        PK2_ent.second = j;

        //Si el nuevo PK es distinto al primero
        if( (PK1.first != PK2.first || PK1.second != PK2.second) && (PK2.first != 0 && PK2.second != 0) ){

            cout<<"Se ha rellenado el segundo PK, fila: "<< PK2.first << " columna: "<< PK2.second<<endl;
            //Se gira el mapa entorno si es necesario
            Orientacion();
            orientado = true;

        }
        //Se reinicia el segundo PK
        else{

            PK2.first = 0;
            PK2.second = 0;
            PK2_ent.first = 0;
            PK2_ent.second = 0;
            cout<<"Es el mismo PK"<<endl;

        }

    }



}


// Método que gira el mapa entorno y el mapa potencial a su izquierda
void Agent::RotaMapaIzquierda(){

    // Matrices auxiliares
    char copia_rotada[200][200];
    int copia_rotada_pot[200][200];

    //Se copian los mapas rotados en las matrices auxiliares
    for( int i = 0; i < 200 ; i++)
        for( int j = 0; j < 200 ; j++){
            copia_rotada[200-j-1][i] = mapa_entorno_[i][j];
            copia_rotada_pot[200-j-1][i] = mapa_potencial_[i][j];
        }

    //Se vuelven a copiar rotados en los mapas originales
    for( int i = 0; i < 200 ; i++)
        for( int j = 0; j < 200 ; j++){
            mapa_entorno_[i][j] = copia_rotada[i][j];
            mapa_potencial_[i][j] = copia_rotada_pot[i][j];
        }

    //Se gira la orientacion del agente a la izquierda
    orientacion_ --;
    if(orientacion_ == -1) orientacion_ = 3;

    //Se actualizan sus coordenadas con el mismo procedimiento que al rotar la matriz
    int x_aux = x_;
    x_ = y_;
    y_ = 200 - x_aux - 1;


    //Se actualizan las coordenadas de entorno de los PK
    int coor_aux = PK1_ent.second;
    PK1_ent.second = PK1_ent.first;
    PK1_ent.first = 200 - coor_aux - 1;


    coor_aux = PK2_ent.second;
    PK2_ent.second = PK2_ent.first;
    PK2_ent.first = 200 - coor_aux - 1;


}


//Metodo que gira el mapa entorno y el mapa potencial a la derecha; procede igual que RotaMapaDerecha() pero con las coordenadas contrarias
void Agent::RotaMapaDerecha(){

    char copia_rotada[200][200];
    int copia_rotada_pot[200][200];

    for( int i = 0; i < 200 ; i++)
        for( int j = 0; j < 200 ; j++){
            copia_rotada[i][j] = mapa_entorno_[200 - j -1][i];
            copia_rotada_pot[i][j] = mapa_potencial_[200 - j -1][i];
        }


    for( int i = 0; i < 200 ; i++)
        for( int j = 0; j < 200 ; j++){
            mapa_entorno_[i][j] = copia_rotada[i][j];
            mapa_potencial_[i][j] = copia_rotada_pot[i][j];
        }

    orientacion_ = (orientacion_ + 1 ) % 4;

    int y_aux = y_;
    y_ = x_;
    x_ = 200 - y_aux - 1;



    int coor_aux = PK1_ent.first;
    PK1_ent.first = PK1_ent.second;
    PK1_ent.second = 200 - coor_aux - 1;

    coor_aux = PK2_ent.first;
    PK2_ent.first = PK2_ent.second;
    PK2_ent.second = 200 - coor_aux - 1;


}



//Método que, dados dos PK, decide si rotar el mapa a la izquierda, a la derecha o 180º
void Agent::Orientacion(){

    //Desplazamiento con respecto a la columna y fila que está un PK y la columna y fila que indica ese PK
    int desfase_1_i = 0, desfase_1_j = 0, desfase_2_i = 0, desfase_2_j = 0;

    desfase_1_i = PK1.first - PK1_ent.first;
    desfase_1_j = PK1.second - PK1_ent.second;

    desfase_2_i = PK2.first - PK2_ent.first;
    desfase_2_j = PK2.second - PK2_ent.second;

    //Posición de un PK con respecto al otro
    pair<int , int > mas_izquierda, mas_derecha, mas_arriba, mas_abajo,
                     mas_izquierda_ent, mas_derecha_ent, mas_arriba_ent, mas_abajo_ent;

    bool orientancion_completa = false;


    //Comprobaciones para saber la posición de un PK con respecto a otro

    //Izquierda o dercha
    if( PK1_ent.second > PK2_ent.second ){

        mas_derecha = PK1;
        mas_izquierda = PK2;
        mas_derecha_ent = PK1_ent;
        mas_izquierda_ent = PK2_ent;

    }
    else if( PK1_ent.second < PK2_ent.second ){
        mas_derecha = PK2;
        mas_izquierda = PK1;
        mas_derecha_ent = PK2_ent;
        mas_izquierda_ent = PK1_ent;
    }
    else{       //Si están en la misma columna, es el de arriba el que está mas a la izquierda

        if( PK1_ent.first > PK2_ent.first ){
            mas_derecha = PK1;
            mas_izquierda = PK2;
            mas_derecha_ent = PK1_ent;
            mas_izquierda_ent = PK2_ent;
        }
        else{
            mas_derecha = PK2;
            mas_izquierda = PK1;
            mas_derecha_ent = PK2_ent;
            mas_izquierda_ent = PK1_ent;
        }

    }


    //Arriba o abajo
    if( PK1_ent.first > PK2_ent.first ){
        mas_abajo = PK1;
        mas_arriba = PK2;
        mas_abajo_ent = PK1_ent;
        mas_arriba_ent = PK2_ent;
    }
    else if( PK1_ent.first < PK2_ent.first ){
        mas_abajo = PK2;
        mas_arriba = PK1;
        mas_abajo_ent = PK2_ent;
        mas_arriba_ent = PK1_ent;
    }
    else{     //Si están en la misma fila, es el de la izquierda el que esta mas arriba

        if( PK1_ent.second > PK2_ent.second ){
            mas_abajo = PK1;
            mas_arriba = PK2;
            mas_abajo_ent = PK1_ent;
            mas_arriba_ent = PK2_ent;
        }
        else{
            mas_abajo = PK2;
            mas_arriba = PK1;
            mas_abajo_ent = PK2_ent;
            mas_arriba_ent = PK1_ent;
        }


    }




    //Si el desfase de las cordenadas para ambos PK es el mismo quiere decir que ya está orientada
    if( desfase_1_i == desfase_2_i && desfase_1_j == desfase_2_j ){
        orientancion_completa = true;
        cout<<"Está orientado."<<endl;
    }

    //Si está doblemente rotada la matriz
    else if( (mas_arriba_ent.first - mas_abajo_ent.first) == -1 *(mas_arriba.first - mas_abajo.first) &&
             (mas_arriba_ent.second - mas_abajo_ent.second) == -1 *(mas_arriba.second - mas_abajo.second)){

        //Doble rotación
        cout<<"Doble Rotacion"<<endl;
        RotaMapaIzquierda();
        RotaMapaIzquierda();
        orientancion_completa = true;
    }



    //Si aún está sin orientar( En este punto descartamos que haya que rotarla 180º)
    if( !orientancion_completa) {

        if( (mas_izquierda.first >= mas_derecha.first) && (mas_arriba.second <= mas_abajo.second) ){


            //Giro izquierda
            cout<<"Giro a la izquierda"<<endl;
            RotaMapaIzquierda();
        }

        else{
            //Giro derecha
            cout<<"Giro a la derecha"<<endl;
            RotaMapaDerecha();
        }

    }


    orientado = true;       //Actualizamos la variable global


}

//Metodo que actualiza el mapa solución según el mapa entorno
void Agent::RellenaMapaSolucion(){

    for( int i = 0; i < 100 ; i++ )
        for( int j = 0; j < 100; j++){

            //Si la casilla está sin rellenar la rellenamos
            if( mapa_solucion_[i][j] == '?')
                mapa_solucion_[i][j] = mapa_entorno_[i + PK1_ent.first - PK1.first][j + PK1_ent.second - PK1.second];
            }

    //Bucle que rellena los bordes de la matriz solucion con precipicios
    for( int i = 0; i < 3 ; i++)
        for( int j = 0; j< 100; j++){

            mapa_solucion_[i][j] = 'P';
            mapa_solucion_[j][i] = 'P';
            mapa_solucion_ [99-i][j] = 'P';
            mapa_solucion_[j][99-i] = 'P';
        }

}

// Método que segun el potencial que rodea al agente decide su próximo movimiento.
// Calcula las casillas por donde ha pasado, las casillas por las que no puede pasar y elige el movimiento que le lleve al mayor potencial
Agent::ActionType Agent::Potencial(){

    //Variables que indican el radio de medición de potencial
    int i_inicio = y_ - 7, j_inicio = x_ - 7,
        i_final = y_ + 7,  j_final = x_ + 7;

    //Variables que almacenan el potencial en cada dirección del agente
    int potencial_sur = 0, potencial_este = 0, potencial_norte = 0, potencial_oeste = 0;

    //Variable de la nueva orientacion que debe tomar el agente
    int orientacion;

    //Accion que tomara el agente
    Agent::ActionType accion = actIDLE;


    //En el radio de medicion de potencial...
    for( int i = i_inicio; i < i_final; i++){
        for( int j = j_inicio; j < j_final; j++ ){

            //Si la casilla está al norte del agente..
            if( i < y_){

                //Si no ha visto esa casilla se aumenta el potencial
                if ( mapa_entorno_[i][j] == '?' )
                    potencial_norte +=10;

                //Si esa casilla es intransitable se disminuye el potencial
                else if( mapa_entorno_[i][j] == 'B' || mapa_entorno_[i][j] == 'A' || mapa_entorno_[i][j] == 'P' || mapa_entorno_[i][j] == 'M' || mapa_entorno_[i][j] == 'D')
                    potencial_norte -= 10;

                //Si la casilla es un PK y no está orientado se aumenta el potencial
                else if( mapa_entorno_[i][j] == 'K' && !orientado)
                    potencial_norte += 10000;

                potencial_norte += mapa_potencial_[i][j];
            }

            //Si la casilla está al sur del agente
            else if ( i > y_){

                if ( mapa_entorno_[i][j] == '?' )
                    potencial_sur +=10;
                else if( mapa_entorno_[i][j] == 'B' || mapa_entorno_[i][j] == 'A' || mapa_entorno_[i][j] == 'P' || mapa_entorno_[i][j] == 'M' || mapa_entorno_[i][j] == 'D')
                    potencial_sur -= 10;
                else if( mapa_entorno_[i][j] == 'K' && !orientado)
                    potencial_sur += 10000;

                potencial_sur += mapa_potencial_[i][j];
            }


            //Si la casilla está al oeste del agente
            if( j < x_) {

                if ( mapa_entorno_[i][j] == '?' )
                    potencial_oeste +=10;
                else if( mapa_entorno_[i][j] == 'B' || mapa_entorno_[i][j] == 'A' || mapa_entorno_[i][j] == 'P' || mapa_entorno_[i][j] == 'M' || mapa_entorno_[i][j] == 'D')
                    potencial_oeste -= 10;
                else if( mapa_entorno_[i][j] == 'K' && !orientado)
                    potencial_oeste += 10000;

                potencial_oeste += mapa_potencial_[i][j];
            }

            //Si la casilla está al este del agente
            else if ( j > x_) {

                if ( mapa_entorno_[i][j] == '?' )
                    potencial_este +=10;
                else if( mapa_entorno_[i][j] == 'B' || mapa_entorno_[i][j] == 'A' || mapa_entorno_[i][j] == 'P' || mapa_entorno_[i][j] == 'M' || mapa_entorno_[i][j] == 'D')
                    potencial_este -= 10;
                else if( mapa_entorno_[i][j] == 'K' && !orientado)
                    potencial_este += 10000;

                potencial_este += mapa_potencial_[i][j];
            }



        }

    }


    //Estas comprobaciones son si el agente está justo al lado de una casilla intransitable, en cuyo caso
    //el potencial de la dirección en donde está esa casilla será muy bajo para que no se decida ir por ahí


    if( mapa_entorno_[y_][x_-1] == 'B' || mapa_entorno_[y_][x_-1] == 'A' || mapa_entorno_[y_][x_-1] == 'P' || mapa_entorno_[y_][x_-1] == 'M' || mapa_entorno_[y_][x_-1] == 'D' || mapa_objetos_[y_][x_-1] >= 'a')
        potencial_oeste = -999999999;

    if( mapa_entorno_[y_][x_+1] == 'B' || mapa_entorno_[y_][x_+1] == 'A' || mapa_entorno_[y_][x_+1] == 'P' || mapa_entorno_[y_][x_+1] == 'M' || mapa_entorno_[y_][x_+1] == 'D' || mapa_objetos_[y_][x_+1] >= 'a')
        potencial_este = -999999999;

    if( mapa_entorno_[y_-1][x_] == 'B' || mapa_entorno_[y_-1][x_] == 'A' || mapa_entorno_[y_-1][x_] == 'P' || mapa_entorno_[y_-1][x_] == 'M' || mapa_entorno_[y_-1][x_] == 'D' || mapa_objetos_[y_ -1][x_] >= 'a')
        potencial_norte = -999999999;

    if( mapa_entorno_[y_+1][x_] == 'B' || mapa_entorno_[y_+1][x_] == 'A' || mapa_entorno_[y_+1][x_] == 'P' || mapa_entorno_[y_+1][x_] == 'M' || mapa_entorno_[y_+1][x_] == 'D' || mapa_objetos_[y_+1][x_] >= 'a')
        potencial_sur = -999999999;



    //Cálculo del mayor potencial
    if( potencial_norte >= potencial_sur && potencial_norte >= potencial_este && potencial_norte >= potencial_oeste)
        orientacion = 0;
    else if( potencial_sur >= potencial_este && potencial_sur >= potencial_oeste && potencial_sur >= potencial_norte)
        orientacion = 2;
    else if( potencial_este >= potencial_sur && potencial_este >= potencial_oeste && potencial_este >= potencial_norte)
        orientacion = 1;
    else
        orientacion = 3;


    //Cálculo de la accion a realizar según la orientacion actual y la nueva

    //Si es la misma orientacion se avanza
    if( orientacion == orientacion_)
        accion = actFORWARD;

    //Si la nueva orientación es a la derecha
    else if ( orientacion == ((orientacion_ + 1) % 4) )
        accion = actTURN_R;

    //Si la nueva orientación es hacia atrás entonces se usa el método giraPotencial()
    else if ( orientacion == ((orientacion_ + 2) % 4) )
        accion = GiraPotencial();

    //Si la nueva orientación es a la izquierda
    else
        accion = actTURN_L;


    //Información de la ejecución de esta función. No es relevante, solo sirve para ver si va bien.

    cout<<"*********************************POTENCIAL V4***********************************"<<endl;
    cout<<"Norte: "<< potencial_norte << " Sur: "<< potencial_sur << " Este: "<<potencial_este << " Oeste: " <<potencial_oeste <<endl;
    cout<<"Orientacion: "<< orientacion << " Accion: ";
    if( accion == actFORWARD) cout<< " actFORWARD" <<endl;
    else if( accion == actTURN_R) cout<< " actTURN_R" <<endl;
    else if( accion == actTURN_L) cout<< " actTURN_L" <<endl;

    cout<< "*******************************************************************************"<<endl;

    return accion;


}


//Método que decide entre girar a la izquierda o a la derecha segun el potencial a ambos lados del agente
Agent::ActionType Agent::GiraPotencial(){

    //Accion a realizar
    Agent::ActionType accion;

    //Variables que almacenan el potencial en cada dirección del agente
    int pot_nor = 0, pot_sur = 0, pot_est = 0, pot_oes = 0;

    //Esta vez en lugar de medir en un radio, se mide en las lineas de casillas que atraviesan al agente
    for( int i = 0; i < 11; i++){

        if( mapa_entorno_[y_][x_-i] == '?')
            pot_oes++;

        if( mapa_entorno_[y_][x_+i] == '?')
            pot_est++;

        if( mapa_entorno_[y_-i][x_] == '?')
            pot_nor++;

        if( mapa_entorno_[y_+i][x_] == '?')
            pot_sur++;

    }


    //Al igual que en Potencial(), si el agente está al lado de una casilla intransitable ese potencial será mínimo
    if( mapa_entorno_[y_][x_-1] == 'B' || mapa_entorno_[y_][x_-1] == 'A' || mapa_entorno_[y_][x_-1] == 'P' || mapa_entorno_[y_][x_-1] == 'M' || mapa_entorno_[y_][x_-1] == 'D' || mapa_objetos_[y_][x_-1] >= 'a')
        pot_oes = 0;

    if( mapa_entorno_[y_][x_+1] == 'B' || mapa_entorno_[y_][x_+1] == 'A' || mapa_entorno_[y_][x_+1] == 'P' || mapa_entorno_[y_][x_+1] == 'M' || mapa_entorno_[y_][x_+1] == 'D' || mapa_objetos_[y_][x_+1] >= 'a')
        pot_est = 0;

    if( mapa_entorno_[y_-1][x_] == 'B' || mapa_entorno_[y_-1][x_] == 'A' || mapa_entorno_[y_-1][x_] == 'P' || mapa_entorno_[y_-1][x_] == 'M' || mapa_entorno_[y_-1][x_] == 'D' || mapa_objetos_[y_-1][x_] >= 'a')
        pot_nor = 0;

    if( mapa_entorno_[y_+1][x_] == 'B' || mapa_entorno_[y_+1][x_] == 'A' || mapa_entorno_[y_+1][x_] == 'P' || mapa_entorno_[y_+1][x_] == 'M' || mapa_entorno_[y_+1][x_] == 'D' || mapa_objetos_[y_+1][x_] >= 'a')
        pot_sur = 0;





    //Según la orientación que tenga comprobamos distintos potenciales y elegimos hacia donde gira
    switch(orientacion_){

        case 0: // Orientacion Norte

            if( pot_oes >= pot_est ){
                accion = actTURN_L;
                cout<<"Giro izquierda"<<endl;
            }
            else{
                accion = actTURN_R;
                cout<<"Giro derecha"<<endl;
            }
	    break;

	    case 1: // Orientacion Este

            if( pot_nor >= pot_sur ){
                accion = actTURN_L;
                cout<<"Giro izquierda"<<endl;
            }
            else{
                accion = actTURN_R;
                cout<<"Giro derecha"<<endl;
            }

        break;

        case 2: // Orientacion Oeste

            if( pot_est >= pot_oes ){
                accion = actTURN_L;
                cout<<"Giro izquierda"<<endl;
            }
            else{
                accion = actTURN_R;
                cout<<"Giro derecha"<<endl;
            }
        break;

        case 3: // Orientacion Oeste

            if( pot_sur >= pot_nor ){
                accion = actTURN_L;
                cout<<"Giro izquierda"<<endl;
            }
            else{
                accion = actTURN_R;
                cout<<"Giro derecha"<<endl;
            }

        break;

    }

    return accion;

}

//Método que rellena los huecos del mapa solución cuando se va a acabar la partida
void Agent::RellenaHuecos(){

    for( int i = 0; i < 100 ; i++)
        for( int j = 0; j < 100; j++)
            if( mapa_solucion_[i][j] == '?'){

                //La casilla en blanco será igual a la que está justo encima
                mapa_solucion_[i][j] = mapa_solucion_[i-1][j];
                mapa_entorno_[i + PK1_ent.first - PK1.first][j + PK1_ent.second - PK1.second] = mapa_solucion_[i][j];
            }

}

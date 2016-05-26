
#ifndef AGENT__
#define AGENT__

#include <string>
#include <iostream>
#include <cstdlib>
#include "conexion.h"
#include <utility>

using namespace std;

// -----------------------------------------------------------
//				class Agent
// -----------------------------------------------------------
class Environment;
class Agent
{
public:
	Agent(){
		x_= 99;
		y_= 99;
		orientacion_=3;
		role_="PlYR";
		last_accion_=3;
		REINICIADO_=false;
		size_=200;
		for (int i=0;i<200;i++)
		    for(int j=0;j<200;j++){
		      mapa_entorno_[i][j]='?';
		      mapa_objetos_[i][j]='?';
			  	mapa_potencial_[i][j]=1;
		    }

		for (int i=0;i<100;i++)
		    for(int j=0;j<100;j++)
		      mapa_solucion_[i][j]='?';



	/********************************************/


		PK1.first = 0;
		PK1.second = 0;
		PK2.first = 0;
		PK2.second = 0;

		PK1_ent.first = 0;
		PK1_ent.second = 0;
		PK2_ent.first = 0;
		PK2_ent.second = 0;

		orientado = false;

		n_pasos = 0;

		tiene_piedra = false;


	/********************************************/

	}

	enum ActionType
	{
	    actFORWARD, // avanzar
	    actTURN_L,  // Girar Izquierda
	    actTURN_R,  // Girar Derecha
	    actIDLE,    // No hacer nada
	    actPICKUP,  // Recoger un objeto
	    actPUTDOWN, // Soltar un objeto
	    actPUSH,    // Meter en la mochila
	    actPOP,     // Sacar de la mochila
	    actGIVE,	// Dar un objeto a un personaje
	    actTHROW	// Lanzar un objeto

	};

	void Perceive(Environment &env);
	bool Perceive_Remote(conexion_client &Cliente, Environment &env);
	void ActualizarInformacion(Environment *env);
	ActionType Think();
	void FixLastAction(Agent::ActionType x){last_accion_=x;};

	char mapa_entorno_[200][200]; // mapa que muestra el tipo de terreno
	char mapa_objetos_[200][200]; // mapa que muestra los objetos que estan encima del terreno
	char mapa_solucion_[100][100]; // Mapa que almacena la solucion que el alumno propone
	// Funciones de acceso a los datos
	void GetCoord(int &fila, int &columna, int &brujula){fila=y_;columna=x_;brujula=orientacion_;};


	/********************************************/

	ActionType GiraPotencial();

	void RotaMapaDerecha();
	void RotaMapaIzquierda();
	ActionType Potencial();
	void CapturaFilaColumnaPK (string mensaje, int &fila, int &columna);
	void RellenaPK(int i, int j);
	void Orientacion();
	void RellenaMapaSolucion();
	void RellenaHuecos();

	/********************************************/

private:
	//Variables de interaccion con el entorno grafico
	int size_;

	//SENSORES
	char VISTA_[10];
	char SURFACE_[10];
	bool REINICIADO_;
	string MENSAJE_;
	char EN_USO_;
	char MOCHILLA_[5];
	char PUNTUACION_[9];
	bool FIN_JUEGO_;
	char SALUD_;

	//Variables de estado
	int x_,y_, orientacion_;
	int last_accion_;
	string role_;

	/********************************************/

	bool primera_vez;
	int x_antes_de_avanzar;
	int y_antes_de_avanzar;
	int mapa_potencial_[200][200];
	pair< int , int> PK1, PK2,   PK1_ent, PK2_ent;
	bool orientado;
	int n_pasos;
	bool tiene_piedra;



	/********************************************/

};

string ActionStr(Agent::ActionType);

#endif

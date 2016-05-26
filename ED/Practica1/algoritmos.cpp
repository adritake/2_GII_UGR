#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <vector> 
#include <string>
#include <time.h>
#include <algorithm>
#include <map>

using namespace std;


//ALGORITMO DE ORDENACION BURBUJA

void burbuja(vector<string> & T, int inicial, int final) {
	int i, j;
	string aux;
	for (i = inicial; i < final - 1; i++)
		for (j = final - 1; j > i; j--)
			if (T[j] < T[j-1]) {
  				aux = T[j];
				T[j]= T[j-1];
				T[j-1] = aux;
			}

}


//Función que se usa en el algoritmo de ordenación por serlección
void intercambiar(  string &a, string &b){

	string aux = a;
	a = b;
	b = aux;

}


//ALGORITMO DE ORDENACION POR SELECCION
void seleccion( vector<string> & T, int inicial, int final ){

	int minimo=0;	

	for ( int i = inicial; i < final; i++){

		T[minimo] = T[i];

		for( int j = i+1; j < final; j++)
			
			if( T[j] < T[minimo])
				
				minimo = j;
		
		intercambiar( T[i] , T[minimo] );
	}
}



//ALGORITMO DE ORDENACION POR SELECCION
void insercion ( vector<string> & T, int inicial, int final ){

	string aux;	
	int i,j;
	for (  i = inicial; i < final; i++){
		
		aux = T[i];		
			
		for(  j = i-1; j >= 0 && aux < T[j]; j--)
		
			T[j+1] = T[j];
		
		T[j+1] = aux;
	}
}

//Función que lee el fichero que le pasamos y lo copia a un vector V
void lee_fichero( const char * nf, vector<string> & V) {
	
	ifstream fe;
 	string s;
	fe.open(nf, ifstream::in);
	
	while ( !fe.eof() ){ 
		fe >> s;
     		if (!fe.eof())
       			V.push_back(s);
  	}
 	
	fe.close();
}



int main(){
	
	vector<string> Dicc;
	
	clock_t start,end;
	double dif;

	int fin=35000;
 
 	lee_fichero("lema.txt", Dicc);
	
 	
 	
	
	for( int i=10; i < fin; i+=1000){
	
		start = clock();

		//seleccion(Dicc,0,i);			//Descomentar el algoritmo que se desea usar
		//burbuja(Dicc,0,i);
		insercion(Dicc,0,i);
		
		end = clock();
		dif = end-start;
		cout<< i << " " << dif/CLOCKS_PER_SEC <<endl;
	}
	
	

	


}












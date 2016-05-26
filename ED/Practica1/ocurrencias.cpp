#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdlib.h>
#include <vector> 
#include <string>
#include <time.h>
#include <algorithm>


#define POS_NULA -1 


///////// Código modificado para que la salida sea el tamaño y el tiempo que tarda //////////



using namespace std;



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




int contar_hasta( vector<string> & V, int ini, int fin, string & s) {
 	
	int cuantos = 0;
	
	for (int i=ini; i< fin ; i++)
		if (V[i]==s) {
			cuantos ++;
    		}
  	
	return cuantos;  
}



int main() {

	vector<string> Dicc;
	vector<string> Q;
	int pos;
	clock_t start,end;
 

	int contador =0;
 
	lee_fichero("lema.txt", Dicc); 
 
 
	lee_fichero("quijote.txt", Q);
 
 
	for (int fin = 10; fin < 100000 ; fin+= 1000){
 		
		string b="hidalgo";
 
 		start = clock();
 		
		for (int iteraciones = 0; iteraciones < 1000; iteraciones++)  
      			pos = contar_hasta(Q, 0,fin, b); 
 		
		end= clock(); 
 		
		double dif = end-start;
 
 		cout<< fin << " " << dif/CLOCKS_PER_SEC <<endl;		// Parte modificada para adecuar la salida.

 }
 

 




}
 

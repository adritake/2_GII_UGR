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
void intercambiar(  int &a, int &b){

	int aux = a;
	a = b;
	b = aux;

}

void seleccion( vector<string> & T, int inicial, int final ){

	for ( int i = inicial; i < final; i++){

		minimo = T[i];

		for( int j = i+1; j < final; j++)
			
			if( T[j] < T[minimo])
				
				minimo = j;
		
		intercambiar( T[i] , T[minimo] );
	}
}




void insercion ( vector<string> & T, int inicial, int final ){

	for ( int i = inicial; i < final; i++){

		for( int j = i-1; j >= 0 && T[j] > minimo; j--)
		
			T[j+1] = T[j];
		
		T[j+1] = minimo;
	}
}
 


int main(){

	int vector[]={'a','t','v','j','t','l','s','r'};

	insercion( vector,0,8);

	for(int i=0; i < 8; i++)
		cout<<vector[i]<<" ";
}












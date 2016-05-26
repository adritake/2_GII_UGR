#include <iostream>
#include <fstream>
#include <unistd.h>
#include <functional>
#include "avl.h"

#include <time.h>
#include <stdlib.h>


using namespace std;

template <class T>
class comparar{

public:

    bool operator()( const T & x,  const T & y){ return x < y; }


};

int n = 0;
void prueba(){

    cout<< "Prueba: " <<n++<<endl;



}
int main(){

    AVL< int, comparar<int> > mi_avl;
    AVL< int, comparar<int> >::iterator it;
    cout<<"PRUEBA DEL INSERT"<<endl;

    pair< AVL< int, comparar<int> >::iterator, bool > ib;

    srand ( time(NULL) );

    int b;


    for( int i = 0; i < 1000; i++){

        b = rand() % 1000;

        cout<<"*********************INSERCION DEL " << b << "*****************************"<<endl;
        ib = mi_avl.insert(b);
        if( ib.second )
            cout<<" Se ha insertado el "<< (*(ib.first))<<endl;
        else
            cout<<" No se ha insertado." << endl;

    }

    cout<<"Tamaño del arbol: " << mi_avl.size()<<endl;

    cout<<"COMPROBACIÓN DE LOS ELEMENTOS"<<endl;

    it = mi_avl.begin();
    bool orden = true;
    int anterior = *it;
    ++it;

    while( it != mi_avl.end() ){
        cout<< *it <<" ";

        if( anterior >= *it)    orden = false;

        anterior = *it;
        ++it;

    }
    cout<<endl;

    if( orden )     cout<< "ESTAN ORDENADOS"<<endl;
    else            cout<< "NO ESTAN ORDENADOS"<<endl;


    cout<<"\n\nPRUEBA DEL FIND Y DEL ERASE"<<endl;

    cout<<"*********************INSERCION DEL 500*****************************"<<endl;
    ib =mi_avl.insert(500);

    if( ib.second )
        cout<<" Se ha insertado el "<< (*(ib.first))<<endl;
    else
        cout<<" No se ha insertado." << endl;

    it = mi_avl.find(500) ;

    cout<<"Antes del borrado:"<<endl;

    cout<<"Tamaño del arbol: " << mi_avl.size()<<endl;
    if( it != mi_avl.end() )    cout<<" Se ha encontrado el "<< *it <<endl;
    else                        cout<<" No se ha encontrado el elemento "<<endl;

    mi_avl.erase(500);
    cout<<"Después del borrado:"<<endl;

    cout<<"Tamaño del arbol: " << mi_avl.size()<<endl;
    it = mi_avl.find(500) ;
    if( it != mi_avl.end() )    cout<<" Se ha encontrado el "<< *it <<endl;
    else                        cout<<" No se ha encontrado el elemento "<<endl;
}


#include <iostream>
#include <fstream>
#include <unistd.h>
#include "crimen.h"
#include "fecha.h"
#include "css.h"


using namespace std;

list<string> to_list( const string & s){

    list<string> l;
    string term;
    unsigned int  indice_s, indice_term, tamanio_s = s.size();

    for( indice_s = 0; indice_s < tamanio_s;    ){


        term.clear();
        indice_term = 0;

        while( s[indice_s] != ' ' && s[indice_s] != '\n' && indice_s < tamanio_s){

            term.push_back( s[indice_s] );
            indice_s++;
            indice_term++;


        }

        indice_s++;
        l.push_back(term);


    }

    return l;

}

int main(){


    cout<<"\n         BIENVENIDO A LA BASE DE DATOS DE LOS CRIMENES DE CHICAGO"<<endl;

    CSS css("crimenes.csv");

    int opcion,k;
    float x1,y1,x2,y2;
    string term_s;
    list<string> term_l;
    list<ID> inarea;
    list<ID>::iterator it_l;
    vector<pair<ID,float> > resultados;
    vector<pair<ID,float> >::iterator it_v;

    do{
        cout<<"\nElija una opción: "<<endl;
        cout<<"\n 1 - Buscar terminos en la base de datos."<<endl;
        cout<<"\n 2 - Buscar crimenes en una área específica."<<endl;

        cin>>opcion;
    }while( opcion < 1 || opcion > 3);

    switch( opcion ){

        case 1:

            cout<<"\n Buscar terminos en la base de datos."<<endl;
            cout<<"\nPor favor introduce los terminos a buscar."<<endl;
            cin.ignore();
            getline(cin, term_s);

            cout<<"\nPor favor introduce el número de resultados a mostrar."<<endl;
            cin>>k;

            term_l = to_list( term_s );




            resultados = css.Query( term_l, k);
            it_v = resultados.begin();

            cout<<"\nEstos son los resultados: "<<endl;

            while( it_v != resultados.end() ){

                cout<<"Peso: " << (*it_v).second <<" ID: "<< (*it_v).first <<"   Descripicion: "<< (*(css.find_ID( (*it_v).first))).second.getDescription()      <<endl;
                ++it_v;
            }

            break;

        case 2:
            cout<<"\n Buscar crimenes en una área específica."<<endl;
            cout<<"\nIntroduce x1"<<endl;
            cin>> x1;
            cout<<"\nIntroduce x2"<<endl;
            cin>> x2;
            cout<<"\nIntroduce y1"<<endl;
            cin>> y1;
            cout<<"\nIntroduce y2"<<endl;
            cin>> y2;

            inarea = css.inArea( x1, x2, y1, y2);
            it_l = inarea.begin();

            while( it_l != inarea.end() ){

                cout<< "ID: "<< *it_l << " Latitud: "<< (*(css.find_ID( *it_l))).second.getLatitude() << " Longitud: "<< (*(css.find_ID( *it_l))).second.getLongitude() << endl;
                ++it_l;
            }


            break;


    }



}

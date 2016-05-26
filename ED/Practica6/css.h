

#ifndef __CRIMESEARCH_H
#define __CRIMESEARCH_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <queue>
#include "crimen.h"
#include <assert.h>


using namespace std;

//! Clase conjunto
/*!
    * \b Constructores
    * CSS::CSS(), CSS::CSS( string nombreDB )

    * \b Metodos de inserción y borrado
    * load( string nombreDB), insert( const crimen & x), erase( const ID & x )

    * \b Modificadores y consultores
    * setArrest(const ID & x, bool value), size()

    * \b Herramientas de búsqueda
    * inArea(Longitud x1, Longitud x2, Latitud y1, Latitud y2 ), Query(list<string> & q, int k)
    * fin_ID(const ID & x)

    * \b Descripción

    * Contiene almacenados los crimenes de un fichero según diferentes criterios para su acceso eficiente


*/
typedef float Longitud;
typedef float Latitud;
typedef unsigned int ID;
typedef string Termino;
typedef string IUCR;



class CSS{

private:

    //Datos miembro

    /**@brief Mapa de ID y su correspondiente crimen
    */
    map<ID,crimen> baseDatos;

    /**@brief Mapa de fechas e iteradores que apuntan al crimen en baseDatos que tiene esa fecha
    */
    multimap < fecha, map<ID,crimen>::iterator >  DateAccess;

    /**@brief Mapa de IUCR y conjuntos de ID que tienen el mismo IUCR
    */
    map<IUCR,set<ID> > IUCRAccess;

    /**@brief Mapa de términos y conjuntos de ID que tienen ese término en su descripcion
    */
    unordered_map<Termino, set<ID> > index;

    /**@brief Mapa que las claves son la longitud y la descripcion un multimapa de latitudes e ID que se dan en esa latitud
    */
    map<Longitud,multimap<Latitud, ID> > posicionGeo;

    /**@brief Método para calcular el pesos de tres o mas resultados
    */
    void unionPeso( map<ID,float> & m, set<ID> & t_i);

    /**@brief Functor para ordenar los resultados en el Query()
    */
    class Comparacion{
    public:
        bool operator() (const pair<ID,float>& p1, const pair<ID,float>& p2);

    };

public:

    //Constructor por defecto
    CSS();

    //Constructor a partir de un archivo
    CSS( string nombreDB) ;

    //Tamaño del contenedor baseDatos
    int size();

    //Carga en los contenedores el fichero
    void load(string nombreDB);

    //Inserta un crimen
    void insert( const crimen & x);

    //Elimina un crimen
    void erase( const ID & x );

    //Estable el arresto de un crimen( ID ) a el valor( value ) que le pasamos
    void setArrest(const ID & x, bool value);

    //Lista de crimenes en una región geográfica
    list<ID> inArea(Longitud x1, Longitud x2, Latitud y1, Latitud y2 );

    //Devuelve los k mejores resultados
    vector<pair<ID,float> > Query(list<string> & q, int k);







    class iterator {

        private:
            // Clase amiga para poder acceder al contenedor.
            friend class CSS;

            // Iterador sobre el contenedor del conjunto.
            map<ID,crimen>::iterator iter;

            // Constructores para begin() y end().
            iterator( const map<ID,crimen>::iterator & it );

        public:

            // Constructor por defecto
            iterator();

            // Constructor de copia
            iterator( const CSS::iterator & it );

            // Operadores
            pair< const ID, crimen > & operator*();
            CSS::iterator & operator++();
            CSS::iterator operator++(int);
            CSS::iterator & operator--();
            CSS::iterator operator--(int);
            CSS::iterator & operator=( const CSS::iterator & new_it );
            bool operator==( const CSS::iterator & new_it ) const;
            bool operator!=( const CSS::iterator & new_it ) const;

    };

    class IUCR_iterator {

        private:
            // Clase amiga para poder acceder al contenedor.
            friend class CSS;

            // Iterador sobre el contenedor del conjunto.
            map<IUCR,set<ID> >::iterator iter;

            // Iterador sobre los elementos de un set
            set<ID>::iterator it_s;

            // Constructores para begin() y end().
            IUCR_iterator( const map<IUCR,set<ID> >::iterator & it, CSS & bd_new );

            //Puntero a la clase CSS para poder aceder a sus miembros
            CSS *bd;

        public:

            // Constructor por defecto
            IUCR_iterator();

            // Constructor de copia
            IUCR_iterator( const CSS::IUCR_iterator & it, CSS & bd_new );

            // Operadores
            pair< const ID, crimen > & operator*();
            CSS::IUCR_iterator & operator++();
            CSS::IUCR_iterator operator++(int);
            CSS::IUCR_iterator & operator--();
            CSS::IUCR_iterator operator--(int);
            CSS::IUCR_iterator & operator=( const CSS::IUCR_iterator & new_it );
            bool operator==( const CSS::IUCR_iterator & new_it ) const;
            bool operator!=( const CSS::IUCR_iterator & new_it ) const;

    };

    class Date_iterator {

        private:
            // Clase amiga para poder acceder al contenedor.
            friend class CSS;

            // Iterador sobre el contenedor del conjunto.
            multimap < fecha, map<ID,crimen>::iterator >::iterator iter;

            // Constructores para begin() y end().
            Date_iterator( const multimap < fecha, map<ID,crimen>::iterator >::iterator & it);


        public:

            // Constructor por defecto
            Date_iterator();

            // Constructor de copia
            Date_iterator( const CSS::Date_iterator & it );

            // Operadores
            pair< const ID, crimen > & operator*();
            CSS::Date_iterator & operator++();
            CSS::Date_iterator operator++(int);
            CSS::Date_iterator & operator--();
            CSS::Date_iterator operator--(int);
            CSS::Date_iterator & operator=( const CSS::Date_iterator & new_it );
            bool operator==( const CSS::Date_iterator & new_it ) const;
            bool operator!=( const CSS::Date_iterator & new_it ) const;

    };



    //Inicios y finales para los iteradores
    iterator begin();
    iterator end();
    IUCR_iterator ibegin();
    IUCR_iterator iend();
    IUCR_iterator lower_bound(const IUCR &iucr);
    IUCR_iterator upper_bound(const IUCR &iucr);
    Date_iterator dbegin();
    Date_iterator dend();
    Date_iterator lower_bound(const fecha &fe);
    Date_iterator upper_bound(const fecha &fe);

    //Devuelve un iterador que apunta al crimen con esa ID
    iterator find_ID(const ID & x);

};

#include "css.hxx"

#endif

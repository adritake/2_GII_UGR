
/**@brief Constructor por defecto
*/
CSS::CSS(){}

//-----------------------------------------------------------------------------

/**
    @brief Constructor que carga un fichero.
    @param nombreDB nombre del fichero.

*/
CSS::CSS( string nombreDB ){

    load( nombreDB );


}
//-----------------------------------------------------------------------------

/**@brief
    Tamaño del mapa baseDatos.

    @return Devuelve un unsigned int que es el tamaño del mapa baseDatos
*/
int CSS::size(){

    return baseDatos.size();

}
//-----------------------------------------------------------------------------

/**
   @brief Carga un fichero en los contenedores.
   @param nombreDB nombre del fichero.
*/
void CSS::load(string nombreDB){

    ifstream fe;
    string cadena;

    cout << "\nAbriendo "<< nombreDB << endl;
    fe.open(nombreDB.c_str(), ifstream::in);

    int linea = 1;

    if( fe.fail() ){

        cerr << "Error al abrir el fichero " << nombreDB << endl;

    }
    else{

        getline(fe,cadena,'\n'); //leo la cabecera del fichero

        cout<<"\nCargando crimenes....."<<endl;
        while ( !fe.eof() ){

            getline(fe,cadena,'\n');

            if (!fe.eof()) {

         	    // Convertir cadena a crimen
                crimen aux = cadena;
                // Insertar cadena en el map

                CSS::insert( aux );
            }

     			++linea;

        }

        cout<<"Hecho."<<endl;


    }

    fe.close();


}
//-----------------------------------------------------------------------------

/**
   @brief Inserta un tipo de dato crimen en los contenedores.
   @param x crimen a insertar.
*/
void CSS::insert( const crimen & x){

    //Almacenamiento de los datos del crimen
    //(para no hacer una llamada a los metodos cada vez que los necesite)
    fecha fech = x.getDate();
    string desc = x.getDescription();
    ID id = x.getID();
    IUCR iucr = x.getIUCR();
    Longitud lon = x.getLongitude();
    Latitud lat = x.getLatitude();

    //Inserción el el map de ID
    pair< ID, crimen > to_insert;

    to_insert.first = id;
    to_insert.second = x;

    baseDatos.insert( to_insert );


    //Insercion en el multimap de fechas
    pair< fecha, map<ID,crimen>::iterator  > to_insert_date;

    to_insert_date.first = fech;
    to_insert_date.second = baseDatos.find( id );

    DateAccess.insert( to_insert_date );


    //Insecion en el map de IUCR
    IUCRAccess[ iucr ].insert( id );


    //Insercion en el unordered map de terminos
    //String auxiliar que tomara el valor de cada termino de la descripcion
    string term;
    unsigned int indice_term  , indice_desc  ;

    //Se recorre cada carácter de la descripción
    for( indice_desc = 0; indice_desc < desc.size();    ){

        term.clear();
        indice_term = 0;

        //Si el carácter es igual a espacio o se llega al final de la descripión se considera que es el fin del término
        while( desc[indice_desc] != ' ' && indice_desc < desc.size()){

            term.push_back( desc[indice_desc] );
            indice_desc++;
            indice_term++;

        }

        //Se avanza indice_desc porque estamos en un espacio
        indice_desc++;
        index[term].insert(id);

    }

    //Insecion en el mapa de posiciones geograficas
    pair< Latitud, ID > to_insert_pos;
    to_insert_pos.first = lat;
    to_insert_pos.second = id;

    posicionGeo[ lon ].insert(to_insert_pos);




}
//-----------------------------------------------------------------------------

/**
   @brief Borra el crimen que tiene esa ID de los contenedores.
   @param x crimen a borrar.
*/
void CSS::erase( const ID & x ){

    //Iterador de baseDatos de ese crimen(Sirve para los demas borrados)
    map<ID,crimen>::iterator it = baseDatos.find( x );



    //BORRADO DEL MULTIMAP DE FECHAS
    //Se busca otro iterador en DateAccess cuya clave sea la fecha de ese id
    multimap < fecha, map<ID,crimen>::iterator >::iterator it2 = DateAccess.find( it->second.getDate() );
    //Como puede haber varias fechas iguales se avanza hasta que sean el mismo iterador
    while( it2 != DateAccess.end() && it2->second != it )
        it2++;
    //Si se ha encontrado se elimina
    if( it2 != DateAccess.end())
        DateAccess.erase( it2 );


    //BORRADO DEL MAPA DE IUCR
    string iucr;
    //Si lo encuentra elimina en la clave iucr el elemento x de el conjunto correspondiente
    if( it != baseDatos.end() ){
        iucr = it->second.getIUCR();
        IUCRAccess[iucr].erase( x );
    }


    //BORRADO DEL UNORDERED MAP DE TERMINOS
    string term;
    string desc = it->second.getDescription();
    unsigned int indice_term  , indice_desc  ;

    //Mismo procedimiento de transformacion de la descripcion en terminos
    //Esta vez en vez de insertar se elimina
    for( indice_desc = 0; indice_desc < desc.size();    ){

        term.clear();
        indice_term = 0;

        while( desc[indice_desc] != ' ' && indice_desc < desc.size()){

            term.push_back( desc[indice_desc] );
            indice_desc++;
            indice_term++;

        }
        indice_desc++;
        index[term].erase( it->second.getID() );

    }

    //BORRADO DEL MAPA DE POSICIONES

    posicionGeo[ it->second.getLongitude() ].erase( it->second.getLatitude());


    //BORRADO DEL MAP DE ID
    //Se borra el ultimo porque los otros borrados se basan en baseDatos
    baseDatos.erase( x );

}
// -------------------------------------------------------------------------------------------

	///////////////////////////
	//
	//        iterator
	//
	///////////////////////////

/**
    @brief Constructor por defecto.
*/
CSS::iterator::iterator(){}
// -------------------------------------------------------------------------------------------


/**
    @brief constructor de copia a partir de un CSS::iterator.
*/
CSS::iterator::iterator( const CSS::iterator &it){

    iter = it.iter;

}
// -------------------------------------------------------------------------------------------

/**
    @brief constructor de copia a partir de un map<ID,crimen>::iterator.
*/
CSS::iterator::iterator( const map<ID,crimen>::iterator & it){

    iter = it;

}
// -------------------------------------------------------------------------------------------

/**
    @biref Operador de pre-incremento.

    @return Una referencia a sí mismo incrementado.
*/
CSS::iterator & CSS::iterator::operator++( ){

    ++iter;

    return *this;

}
// -------------------------------------------------------------------------------------------


/**
    @brief Operador de post-incremento.

    @return Una copia de sí mismo antes de ser incrementado.
*/
CSS::iterator CSS::iterator::operator++(int){

    CSS::iterator ant = *this;

    ++(*this);

    return ant;


}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador de pre-decremento.

    @return Una referencia a sí mismo decrementado.
*/
CSS::iterator & CSS::iterator::operator--( ){

    --iter;

    return *this;

}
// -------------------------------------------------------------------------------------------


/**
    @brief Operador de post-decremento.

    @return Una copia de sí mismo antes de ser decrementado.
*/
CSS::iterator CSS::iterator::operator--(int){

    CSS::iterator ant = *this;

    --(*this);

    return ant;


}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador de asignación.

    @return Una referencia a sí mismo para poder encadenar asignaciones.

*/
CSS::iterator & CSS::iterator::operator=( const CSS::iterator & new_it ){

    if( this != &new_it)
        iter = new_it.iter;

    return *this;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador de comparación de igualdad.

    @return true si son iguales, false si no.
*/
bool CSS::iterator::operator==(const CSS::iterator & new_it )const{

    return iter == new_it.iter;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador de comparación de desigualdad.

    @return true si son distintos, false si no.
*/
bool CSS::iterator::operator!=(const CSS::iterator & new_it )const{

    return iter != new_it.iter;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador para acceder a donde apunta el iterador.

    @return un par de ID y el crimen con esa ID.
*/
pair< const ID, crimen > & CSS::iterator::operator*(){

    return *iter;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Inicio del mapa baseDatos.

    @return CSS::iterator que apunta al inicio del mapa baseDatos.
*/
CSS::iterator CSS::begin(){

    CSS::iterator it ( baseDatos.begin() );
    return it;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Fin del mapa baseDatos.

    @return CSS::iterator que apunta al final del mapa baseDatos.
*/
CSS::iterator CSS::end(){

    CSS::iterator it ( baseDatos.end() );
    return it;

}

// -------------------------------------------------------------------------------------------

	///////////////////////////
	//
	//        IUCR_iterator
	//
	///////////////////////////

/**
    @brief Constructor por defecto.
*/
CSS::IUCR_iterator::IUCR_iterator(){}
// -------------------------------------------------------------------------------------------


/**
    @brief constructor de copia a partir de un CSS::IUCR_iterator y un puntero a un objeto de la clase CSS.
*/
CSS::IUCR_iterator::IUCR_iterator( const CSS::IUCR_iterator &it, CSS & bd_new){

    iter = it.iter;
    it_s = it.it_s;
    bd = &bd_new;

}

// -------------------------------------------------------------------------------------------


/**
    @brief constructor de copia a partir de un map<IUCR,set<ID> >::iterator y un puntero a un objeto de la clase CSS.
*/
CSS::IUCR_iterator::IUCR_iterator( const map<IUCR,set<ID> >::iterator & it, CSS & bd_new){

    iter = it;
    it_s = it->second.begin();
    bd = &bd_new;

}
// -------------------------------------------------------------------------------------------

/**
    @biref Operador de pre-incremento.

    @return Una referencia a sí mismo incrementado.
*/

CSS::IUCR_iterator & CSS::IUCR_iterator::operator++( ){

    ++it_s;

    //Si se llega a el final del conjunto se avanza iter y se pone it_s al inicio del conjunto que apunta iter
    if( it_s == iter->second.end() ){
        ++iter;
        it_s = iter->second.begin();
    }


    return *this;

}
// -------------------------------------------------------------------------------------------

/**
    @biref Operador de post-incremento.

    @return Una copia de sí mismo antes de ser incrementado.
*/
CSS::IUCR_iterator CSS::IUCR_iterator::operator++(int){

    CSS::IUCR_iterator ant = *this;

    ++(*this);

    return ant;


}
// -------------------------------------------------------------------------------------------


/**
    @brief Operador de pre-decremento.

    @return Una referencia a sí mismo decrementado.
*/
CSS::IUCR_iterator & CSS::IUCR_iterator::operator--( ){

    --it_s;

    //Si es igual al final, quiere decir que ha dado la vuelta al set
    //Se decrementa iter y se pone it_s apuntando al final del conjunto que apunta iter
    if( it_s == iter->second.end() ){
        --iter;
        it_s = iter->second.end();
        --it_s;
    }

    return *this;

}
// -------------------------------------------------------------------------------------------


/**
    @brief Operador de post-decremento.

    @return Una copia de sí mismo antes de ser decrementado.
*/
CSS::IUCR_iterator CSS::IUCR_iterator::operator--(int){

    CSS::IUCR_iterator ant = *this;

    --(*this);

    return ant;


}

// -------------------------------------------------------------------------------------------

/**
    @brief Operador de asignación.

    @return Una referencia a sí mismo para poder encadenar asignaciones.

*/
CSS::IUCR_iterator & CSS::IUCR_iterator::operator=( const CSS::IUCR_iterator & new_it ){

    if( this != &new_it   &&   it_s != new_it.it_s ){
        iter = new_it.iter;
        it_s = new_it.it_s;
        bd = new_it.bd;
    }

    return *this;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador de comparación de igualdad.

    @return true si son iguales, false si no.
*/

bool CSS::IUCR_iterator::operator==(const CSS::IUCR_iterator & new_it )const{

    return iter == new_it.iter && it_s == new_it.it_s;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador de comparación de desigualdad.

    @return true si son distintos, false si no.
*/bool CSS::IUCR_iterator::operator!=(const CSS::IUCR_iterator & new_it )const{

    return iter != new_it.iter && it_s != new_it.it_s;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador para acceder a donde apunta el iterador.

    @return un par de ID y el crimen con esa ID.
*/
pair< const ID, crimen > & CSS::IUCR_iterator::operator*(){

    //Se busca en bd el iterador cuya ID es la que apunta it_s
    CSS::iterator it = bd->find_ID(*it_s);

    return *it;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Inicio del mapa IUCRAccess.

    @return CSS::IUCR_iterator que apunta al inicio del mapa IUCRAccess.
*/

CSS::IUCR_iterator CSS::ibegin(){

    CSS::IUCR_iterator it( IUCRAccess.begin() , *this);

    return it;


}
// -------------------------------------------------------------------------------------------

/**
    @brief Final del mapa IUCRAccess.

    @return CSS::IUCR_iterator que apunta al final del mapa IUCRAccess.
*/
CSS::IUCR_iterator CSS::iend(){

    CSS::IUCR_iterator it( IUCRAccess.end() , *this);

    return it;


}
// -------------------------------------------------------------------------------------------

/**
    @brief Lower bound del mapa IUCRAccess.

    @param IUCR del cual se quiere buscar el lower bound.

    @return CSS::IUCR_iterator que apunta al lower bound del IUCR que se le ha pasado.
*/
CSS::IUCR_iterator CSS::lower_bound(const IUCR &iucr){

    CSS::IUCR_iterator it( IUCRAccess.lower_bound( iucr ), *this);
    return it;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Upper bound del mapa IUCRAccess.

    @param IUCR del cual se quiere buscar el upper bound.

    @return CSS::IUCR_iterator que apunta al upper bound del IUCR que se le ha pasado.
*/
CSS::IUCR_iterator CSS::upper_bound(const IUCR &iucr){

    CSS::IUCR_iterator it( IUCRAccess.upper_bound( iucr ), *this);
    return it;

}


// -------------------------------------------------------------------------------------------

	///////////////////////////
	//
	//        Date_iterator
	//
	///////////////////////////

/**
    @brief Constructor por defecto.
*/
CSS::Date_iterator::Date_iterator(){}
// -------------------------------------------------------------------------------------------


/**
    @brief constructor de copia a partir de un CSS::Date_iterator.
*/
CSS::Date_iterator::Date_iterator( const CSS::Date_iterator &it){

    iter = it.iter;


}
// -------------------------------------------------------------------------------------------

/**
    @brief constructor de copia a partir de un multimap < fecha, map<ID,crimen>::iterator >::iterator.
*/
CSS::Date_iterator::Date_iterator( const multimap < fecha, map<ID,crimen>::iterator >::iterator & it){

    iter = it;

}
// -------------------------------------------------------------------------------------------

/**
    @biref Operador de pre-incremento.

    @return Una referencia a sí mismo incrementado.
*/

CSS::Date_iterator & CSS::Date_iterator::operator++( ){

    ++iter;

    return *this;

}
// -------------------------------------------------------------------------------------------


/**
    @brief Operador de post-incremento.

    @return Una copia de sí mismo antes de ser incrementado.
*/
CSS::Date_iterator CSS::Date_iterator::operator++(int){

    CSS::Date_iterator ant = *this;

    ++(*this);

    return ant;


}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador de pre-decremento.

    @return Una referencia a sí mismo decrementado.
*/
CSS::Date_iterator & CSS::Date_iterator::operator--( ){

    --iter;

    return *this;

}
// -------------------------------------------------------------------------------------------


/**
    @brief Operador de post-decremento.

    @return Una copia de sí mismo antes de ser decrementado.
*/
CSS::Date_iterator CSS::Date_iterator::operator--(int){

    CSS::Date_iterator ant = *this;

    --(*this);

    return ant;


}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador de asignación.

    @return Una referencia a sí mismo para poder encadenar asignaciones.

*/
CSS::Date_iterator & CSS::Date_iterator::operator=( const CSS::Date_iterator & new_it ){

    if( this != &new_it ){
        iter = new_it.iter;
    }

    return *this;

}


// -------------------------------------------------------------------------------------------

/**
    @brief Operador de comparación de igualdad.

    @return true si son iguales, false si no.
*/
bool CSS::Date_iterator::operator==(const CSS::Date_iterator & new_it )const{

    return iter == new_it.iter;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador de comparación de desigualdad.

    @return true si son distintos, false si no.
*/
bool CSS::Date_iterator::operator!=(const CSS::Date_iterator & new_it )const{

    return iter != new_it.iter;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Operador para acceder a donde apunta el iterador.

    @return un par de ID y el crimen con esa ID.
*/
pair< const ID, crimen > & CSS::Date_iterator::operator*(){

    return *(iter->second);

}

// -------------------------------------------------------------------------------------------

/**
    @brief Inicio del multimap DateAccess.

    @return CSS::Date_iterator que apunta al inicio del multimap DateAccess.
*/
CSS::Date_iterator CSS::dbegin(){

    CSS::Date_iterator it( DateAccess.begin());

    return it;


}
// -------------------------------------------------------------------------------------------

/**
    @brief Final del multimap DateAccess.

    @return CSS::Date_iterator que apunta al final del multimap DateAccess.
*/
CSS::Date_iterator CSS::dend(){

    CSS::Date_iterator it( DateAccess.end() );

    return it;


}
// -------------------------------------------------------------------------------------------

/**
    @brief Lower bound del multimap DateAccess.

    @param fecha de la cual se quiere buscar el lower bound.

    @return CSS::Date_iterator que apunta al lower bound de la fecha que se le ha pasado.
*/
CSS::Date_iterator CSS::lower_bound(const fecha &fe){

    CSS::Date_iterator it( DateAccess.lower_bound( fe ));
    return it;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Upper bound del multimap DateAccess.

    @param fecha de la cual se quiere buscar el upper bound.

    @return CSS::Date_iterator que apunta al upeer bound de la fecha que se le ha pasado.
*/
CSS::Date_iterator CSS::upper_bound(const fecha &fe){

    CSS::Date_iterator it( DateAccess.upper_bound( fe ));
    return it;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Método para buscar un crimen a partir de su ID en el mapa baseDatos.

    @param ID del crimen a buscar.

    @return CSS::iterator que apunta al crimen de basDatos con esa ID.
*/

CSS::iterator CSS::find_ID(const ID & x){

    CSS::iterator it( baseDatos.find( x ) );

    return it;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Cambia el arresto de un crimen.

    @param bool que es el valor del arresto que se desea poner.

*/
void CSS::setArrest(const ID & x, bool value){

    //Se busca en baseDatos
    CSS::iterator it( baseDatos.find( x ) );

    //Si se encuentra se establece el valor de arresto al nuevo valor
    if( it != CSS::end() )
        (*it).second.setArrest( value );

}
// -------------------------------------------------------------------------------------------

/**
    @brief Busca crimenes dentro de unas coordenadas

    @param Latitudes y longitudes en donde se quieren buscar los crimenes.( x1 < x2 && y1 < y2)

    @return Una lista de ID de crimenes que se encuentran dentro de ese area

*/
list<ID> CSS::inArea(Longitud x1, Longitud x2, Latitud y1, Latitud y2 ){

    list<ID> zona;

    CSS::iterator it;

    //Se recorren todos los elementos de baseDatos
    for( it = CSS::begin(); it != CSS::end() ; ++it){

        //Si las coordenadas se encuentran dentro de las coordenadas pasadas como argumentos
        //Se introduce la ID en la lista
        if( (*it).second.getLongitude() > x1 && (*it).second.getLongitude() < x2
           && (*it).second.getLatitude() > y1 && (*it).second.getLatitude() < y2){


           zona.push_back( (*it).first );
       }



    }

    return zona;

}
// -------------------------------------------------------------------------------------------

/**
    @brief Actualiza el peso(Número de veces que aparece un elemento) de un map<ID,float> a partir de un nuevo set<ID>.

    @param El map<ID,float> a actualizar y un set<ID> de donde se sacan los datos para actualizar el map.

    @return El map<ID,float> actualizado.

*/
void CSS::unionPeso( map<ID,float> & m, set<ID> & t_i){

    set<ID>::iterator it = t_i.begin();

    //Se recorren todos los elementos del set<ID>
    while( it != t_i.end() ){

        //Si el peso de esa ID es mayor que uno quiere decir que ya estaba y se aumenta
        if ( m[*it] >= 1 )
            m[*it] = m[*it] + 1;
        //Si es menor que uno quiere decir que no estaba, se crea y se pone su peso a 1
        else
            m[*it] = 1;

        ++it;


    }


}
// -------------------------------------------------------------------------------------------

/**
    @brief Functor que ordena la priority queue del método Query/().

    @param Dos pair<ID,float> que se van a comparar.

    @return true si el peso del crimen uno es mayor o igual que el peso del crimen dos. False en caso contrario.

*/
bool CSS::Comparacion::operator()(const pair<ID,float>& p1, const pair<ID,float>& p2){

    return p1.second >= p2.second;


}

// -------------------------------------------------------------------------------------------

/**
    @brief Busca los k elementos con mejores coincidencias en su descrpcion con una lista de terminos.

    @param Una list<string> con los parametros a buscar, un entero que indica cuantos elementos queremos mostrar

    @return Un vector<pair<ID,float> > donde se almacenan las ID y su peso

*/
vector<pair<ID,float> > CSS::Query( list<string> & q, int k ){

    //Contenedores y iteradores necesarios para la búsqueda
    vector<pair<ID,float> > resultados;
    map<ID,float> unionpeso;
    map<ID,float>::iterator it_m;
    list<string>::iterator it_l = q.begin();
    //priority_queue que se le pasa como functor la clase Comparacion
    priority_queue< pair<ID,float> , vector< pair<ID,float> >, Comparacion > pq;
    pair<ID,float> to_insert;

    //Union de conjuntos mientras se recorre cada elemento de la lista
    while ( it_l != q.end() ){

        if( index.find( *it_l ) != index.end() )

            unionPeso( unionpeso, index.find( *it_l )->second );

        ++it_l;


    }

    it_m = unionpeso.begin();

    //Este if es para el caso de que se introduzca un solo termino y no exista en ninguna descripción
    if( it_m != unionpeso.end()){


        //Se meten los primeros k elementos en el priority queue
        for( int i=0; i < k; i++){

            to_insert.first = it_m->first;
            to_insert.second = it_m->second;

            pq.push( to_insert );

            ++it_m;


        }

        //Para el restor de elementos se comprueba si tienen mayor peso y si procede, se mete
        while( it_m != unionpeso.end() ){

            to_insert.first = it_m->first;
            to_insert.second = it_m->second;

            if( to_insert.second >= pq.top().second ){
                pq.push( to_insert );
                pq.pop();

            }

            ++it_m;

        }


        //Ahora pasamos los k elementos de la priority queue al vector
        while( !pq.empty() ){
            resultados.insert( resultados.begin(), pq.top() );
            pq.pop();
        }
    }


    return resultados;


}

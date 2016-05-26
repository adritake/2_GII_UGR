

// **********************************************************************************//
template< typename T, class comparar>
AVL<T,comparar>::AVL():tama(0){}

// **********************************************************************************//

template< typename T, class comparar>
AVL<T,comparar>::AVL( const AVL<T, comparar> & a ){

    //Uso del operador de asignación del bintree
    el_avl = a.el_avl;
    tama = a.tama;


}

// **********************************************************************************//

template< typename T, class comparar>
AVL<T,comparar>::AVL( const T & t){

    //Creo el pair a insertar con la etiqueta y la altura 1
    pair < T, typename AVL< T, comparar >::altura > p_aux( t,1);

    //Creo un arbol auxiliar con ese par
    bintree < pair < T, typename AVL< T, comparar >::altura > > b_aux(p_aux);

    //Se lo asigno a el_avl
    el_avl = b_aux;

    tama = 1;


}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL<T,comparar>::altura AVL<T,comparar>::h(  typename bintree < pair<T, typename AVL<T,comparar>::altura> >::node & n ){

    //Si es un nodo nulo devuelve 0 para que cuadren las cuentas de balanceo
    if( n.null() )
        return 0;

    //Si no es nulo devuelve el elemento segundo del pair que es la altura
    else
        return (*n).second;
}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL<T,comparar>::altura AVL<T,comparar>::h( const typename bintree < pair<T, typename AVL<T,comparar>::altura> >::const_node & n){

    //Si es un nodo nulo devuelve 0 para que cuadren las cuentas de balanceo
    if( n.null() )
        return 0;
    //Si no es nulo devuelve el elemento segundo del pair que es la altura
    else
        return (*n).second;


}

// **********************************************************************************//


template< typename T, class comparar>
int AVL<T,comparar>::balanceo( const typename bintree < pair < T, typename AVL<T,comparar>::altura > >::node & n ){


    int b = 0;

    if( !n.null() )
        b = h( n.left() ) - h( n.right() );


    //Si n es nulo devuelvo 0, sino devuelvo la diferencia de la altura de sus hijos
    return b;

}

// **********************************************************************************//


template< typename T, class comparar>
void AVL<T,comparar>::balancear( typename bintree < pair < T, typename AVL<T,comparar>::altura > >::node & n ){



    if( balanceo( n ) > 1 ) {    //Quiere decir que la rama izquierda tiene mas altura que la derecha


            //Comprobación de si es una rotación simple o doble

            /*
                                A
                               /
                              /
                             /
                            B
                           / \
                          /   \
                         /     \
                        C       D

                *   n == A
                *   En este punto h(C) != h(D) porque balanceo(n) > 1
                *   si h(C) < h(D) se hace una rotacion simple a la derecha sobre A
                *   si h(C) > h(D) se hace una rotacion doble a la derecha sobre A

            */
            if( !AVL<T,comparar>::cmp( h( n.left().left() ) ,h( n.left().right() ) ) )

                rsd(n);

            else

                rdd(n);

    }
    else if ( balanceo( n ) < -1 ){


            //Igual que el caso anterior pero al contrario
            if( !AVL<T,comparar>::cmp ( h( n.right().right() ), h( n.right().left() ) ) )

                rsi(n);

            else

                rdi(n);

    }



}

// **********************************************************************************//



template< typename T, class comparar>
void AVL<T,comparar>::rsd( typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node & n ){





    //raiz -> nodo que pasara a estar arriba e insertado en padre
    typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node raiz,  padre;

    //Arboles auxiliares para hacer los prune y las inserciones
    bintree < pair < T, typename AVL<T,comparar >::altura > > aux1, aux2, auxp;

    //Condiciones del nodo
    // tiene_padre -> si tiene padre
    // izq -> si es un hijo izquierda del padre
    bool izq = true, tiene_padre = true;


    //Almaceno el padre de n en padre
    padre = n.parent();

    //Si no tiene padre pongo tiene_padre a false ( necesario para elegir qué hacer más adelante)
    if( padre.null())

        tiene_padre = false;

    //Si es un hijo derecha podo el padre por la derecha, pongo izq a false y almaceno la rama derecha del padre en auxp
    else if( padre.left() != n ){
        izq = false;
        el_avl.prune_right( padre, auxp);
    }
    else
        //Si es un hijo izquierda podo el padre por la izquierda, dejo izq igual y almaceno la rama izquierda del padre en auxp
        el_avl.prune_left( padre, auxp);


    //Como es una rsd, la raiz será el hijo izquierda del nodo a rotar
    raiz = n.left();

    //Podo la rama izquierda del nodo y la almaceno en aux1
    el_avl.prune_left( n, aux1);

    //Podo la rama derehca de la raiz( n.left() )  y la almaceno en aux2
    el_avl.prune_right( raiz, aux2);

    //Insertamos aux2 a la izquierda de n
    el_avl.insert_left( n, aux2);


    //Si tiene padre insertamos a la derecha de la raiz auxp
    if( tiene_padre )
        el_avl.insert_right( raiz, auxp);

    //Si no tiene padre quiere decir que es el nodo raiz el el_avl e inserto a la derecha de raiz el el_avl
    else
        el_avl.insert_right( raiz, el_avl);


    if( tiene_padre)
        //Inserción a la izquierda o derecha del padre
        if( izq )
            el_avl.insert_left(padre,aux1);
        else
            el_avl.insert_right(padre,aux1);
    else{

        //Si no tiene padre, el el_avl le corresponde a aux1
        el_avl = aux1;
        //Establezco raiz a la raiz del el_avl
        raiz = el_avl.root();
    }


    //Decremento en dos unidades la altura del hijo derecha de la raiz.
    (*(raiz.right())).second -= 2;

    //Establezco n como la raiz para que despues se pueda seguir subiendo por el arbol con normalidad
    n = raiz;


}

// **********************************************************************************//


template< typename T, class comparar>
void AVL<T,comparar>::rsi( typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node  & n ){


    //Exactamente igual que en la rsd
    typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node raiz,  padre;
    bintree < pair < T, typename AVL<T,comparar >::altura > > aux1, aux2, auxp;

    bool izq = true, tiene_padre = true;


    padre = n.parent();

    if( padre.null())

        tiene_padre = false;

    else if( padre.left() != n ){
        izq = false;
        el_avl.prune_right( padre, auxp);
    }
    else
        el_avl.prune_left( padre, auxp);


    //Exactamente igual que la rsd solo que se cambian los left por right ya que es un proceso simétrico
    raiz = n.right();


    el_avl.prune_right( n, aux1);

    el_avl.prune_left( raiz, aux2);

    el_avl.insert_right( n, aux2);

    if( tiene_padre )
        el_avl.insert_left( raiz, auxp);
    else
        el_avl.insert_left( raiz, el_avl);


    if( tiene_padre)
        if( izq )
            el_avl.insert_left(padre,aux1);
        else
            el_avl.insert_right(padre,aux1);
    else{
        el_avl = aux1;
        raiz = el_avl.root();
    }


    (*(raiz.left())).second -= 2;

    n=raiz;


}



// **********************************************************************************//



template< typename T, class comparar>
void AVL<T,comparar>::rdi( typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node & n ){

    typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node aux = n.right();


    // RSD del hijo derecha de n
    rsd( aux );

    //Ajuste necesario de las alturas ya que rsd no tiene en cuenta que despues se hace un rsi
    (*(aux.right())).second++;
    (*(aux)).second++;

    // RSI de n
    rsi( n );


}

// **********************************************************************************//


template< typename T, class comparar>
void AVL<T,comparar>::rdd( typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node & n ){

    typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node aux = n.left();

    // RSI del hijo izquierda de n
    rsi( aux );

    //Ajuste necesario de las alturas ya que rsi no tiene en cuenta que despues se hace un rsd
    (*(aux.left())).second++;
    (*(aux)).second++;

    // RSD de n
    rsd( n );


}

// **********************************************************************************//


template< typename T, class comparar>
void AVL<T,comparar>::clear(){

    el_avl.clear();

}

// **********************************************************************************//


template< typename T, class comparar>
typename bintree < pair < T, typename AVL<T,comparar>::altura > >::size_type AVL<T,comparar>::size(){

    return tama;

}

// **********************************************************************************//


template< typename T, class comparar>
bool AVL<T,comparar>::empty(){

    return el_avl.empty();

}

// **********************************************************************************//


template< typename T, class comparar>
AVL<T, comparar> & AVL<T,comparar>::operator=(const AVL<T, comparar> & a){

    el_avl = a.el_avl;
    tama = a.tama;

}

// **********************************************************************************//



template< typename T, class comparar>
void AVL<T, comparar>::swap( AVL<T, comparar> & a){

    AVL<T, comparar> aux;
    int tama_aux;
    //El propio operador de asignación se encarga de liberar lo que habia antes en el arbol
    aux.el_avl = el_avl;
    tama_aux = tama;

    el_avl = a.el_avl;
    tama = a.tama;

    a.el_avl = aux.el_avl;
    a.tama = tama_aux;



}

// **********************************************************************************//


template< typename T, class comparar>
pair< typename AVL<T,comparar>::iterator, bool> AVL<T,comparar>::insert( const T & x){


    //pair que devolveremos
    pair< typename AVL<T,comparar>::iterator, bool> ret;

    //Nodo iterador que usaremos para movernos por el árbol
    typename bintree < pair<T, typename AVL<T,comparar>::altura> >::node n = el_avl.root();

    //Iterador que devolveremos en el pair
    typename AVL<T,comparar>::iterator it;

    //pair para insertar
    pair<T, typename AVL<T,comparar>::altura> p;
    //El primer elemento es igual a la etiqueta pasada como argumento
    p.first = x;
    //Cualquier nodo que se inserte siempre sera un nodo hoja con altura 1
    //Puede ser que despues se balancee pero ya se encargar el propio método de cambiar su altura
    p.second = 1;


    //Condicion de parada del bucle e información de si se ha insertado
    bool para = false, insertado = false;

    //Si n == root() == null quiere decir que el árbol no tiene elementos
    if( n.null() ){

        //Creamos un árbol auziliar a partir de el pair p
        bintree < pair<T, typename AVL<T,comparar>::altura> > bt(p);
        //Asignación a el_avl
        el_avl = bt;
        //Se pone insertado a true
        insertado = true;
        //Establezco el iterador n a la raiz para ser devuelto despues
        n = el_avl.root();

    }
    else{       //Si el árbol tiene elementos

        //Mientras una sentencia del bucle no indique que pare
        while( ! para ){

            //Si el elemento a buscar es mas pequeño que el nodo actual
            if( AVL<T,comparar>::cmp( x, (*n).first ) ){

                //Si el nodo de la izquierda es nulo quiere decir que no existe el elemento y se debe insertar ahí
                if( n.left().null() ){

                    el_avl.insert_left(n,p);
                    para = true;
                    insertado = true;
                }
                //Si la etiqueta del nodo de la izquierda es igual a la que queremos insertar quiere decir que ese elemento ya existe y no podemos insertarlo
                else if ( (*(n.left())).first == x ){
                    para = true;
                    insertado = false;
                }

                //Se avanza a n.left() ya sea para seguir avanzando por el arbol o para dejar el nodo iterador en el elemento que queremos devolver
                n = n.left();


            }

            //Como cmp es una comprobacion estricta hay que comprobar si es igual ( Sirve para comrpobar si si quiere insertar un elemento igual a la raiz)
            else if ( (*n).first != x ){

                //Igual que en el caso anterior pero simetricamente
                if( n.right().null() ){

                    el_avl.insert_right(n,p);
                    para = true;
                    insertado = true;

                }
                else if ( (*(n.right())).first == x){
                    para = true;
                    insertado = false;
                }

                n = n.right();

            }

            //Si queremos insertar un nodo igual a la raiz no lo insertamos. n ya esta en la raiz del arbol.
            else{
                para = true;
                insertado = false;

            }
        }

    }


    //Actualización de las alturas
    if( insertado ){

        //Mientras no lleguemos a la raiz
        while( n != el_avl.root() ){

            //Si el nodo tiene padre && la altura del padre es igual a la nuestra quiere decir que debemos aumentar la altura del padre
            if( !n.parent().null()    &&    (  (*(n.parent())).second == (*n).second )  )
                (*(n.parent())).second++;


            //Avanzamos al padre
            n = n.parent();


            //Se balancea si se debe el nodo n
            balancear(n);





        }

        tama++;
    }


    //Devolvemos el pair usando find(x) ya que devuelve un iterador al elemento o el end del AVL si no lo encuentra
    return pair< typename AVL<T,comparar>::iterator, bool>( find(x), insertado );

}


// **********************************************************************************//


template< typename T, class comparar>
int AVL<T, comparar>::erase( const T & x){


    //Parada del bucle e información de si se ha encontrado el elemento a borrar
    bool encontrado = false, para = false;

    //Nodo iterador
    typename bintree < pair<T, typename AVL<T,comparar>::altura> >::node n = el_avl.root();



    //Busqueda del elemento a borrar

    //Mientras una sentencia del bucle no indique que pare
    while( !para ){

        if( (*n).first == x ) {
            encontrado = true;
            para = true;

        }
        else if ( AVL<T,comparar>::cmp(x, (*n).first ) ){

                if( n.left().null() ){
                    para = true;
                    encontrado = false;
                }
                else
                    n = n.left();

        }
        else{

            if( n.right().null() ){
                para = true;
                encontrado = false;
            }
            else
                n = n.right();

        }


    }


    //Si se ha encontrado...
    if( encontrado ){

        // Si es un nodo hoja...
        if( n.right().null() && n.left().null() ){


            erase_hoja( n );


        }

        else{

            erase_nodo_interno(n);


        }

        tama--;
        return 1;

    }
    else
        //Si no se ha encontrado devolvemos 0 ( elementos borrados == 0)
        return 0;



}


// **********************************************************************************//


template< typename T, class comparar>
void AVL<T, comparar>::erase_hoja( typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node & n){

    //Arbol auxiliara para el prune
    bintree < pair<T, typename AVL<T,comparar>::altura> > padre_bin;

    //Nodo padre del nodo hoja a eliminar
    typename bintree < pair<T, typename AVL<T,comparar>::altura> >::node padre_node;

     //Si es el nodo raiz solo limpiamos el arbol
    if( n == el_avl.root() )
        el_avl.clear();
    else {

        //Establecemos el padre de la hoja a borrar
        padre_node = n.parent();


        //Si el hijo izquierda es menor o igual
        if(  padre_node.left() == n   ||    AVL<T,comparar>::cmp( (*n).first, (*padre_node).first)   )
            //Podamos el padre por la izquierda
            el_avl.prune_left( padre_node, padre_bin);
        else
            //Si es mayor o igual lo podamos por la derehca
            el_avl.prune_right( padre_node, padre_bin);


        //Una vez podado ponemos el nodo iterador al padre del elemento borrado
        n = padre_node;

        //Mientras no lleguemos a la raiz...
        while( n != el_avl.root() ){

            //Si no tiene hijos ponemos la altura a uno
            if( n.right().null() && n.left().null() )
                (*n).second = 1;

            //balancear ya se encarga de poner las alturas bien
            balancear(n);

            //Avanzo al padre
            n = n.parent();



        }

    }
}

// **********************************************************************************//



template< typename T, class comparar>
void AVL<T, comparar>::erase_nodo_interno( typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node & n ){

    //Nodo iterador
    typename bintree < pair < T, typename AVL<T,comparar >::altura > >::node n_it;


    //Para buscar el elemento anterior mas grande, si se puede avanzamos a la izquierda
    if( n.left().null() )
        n_it = n.right();
    else
        n_it = n.left();


    //Busqueda del anterior más grande
    while( ! n_it.right().null() ){

        n_it = n_it.right();

    }

    //Pongo la etiqueta del elemento a borrar igual al elemento anterior mas grande
    (*n).first = (*n_it).first;

    //Borramos el elemento anterior mas grande que es una hoja y a pasado a estar en el lugar del elemento a borrar
    erase_hoja( n_it );

}



// **********************************************************************************//



template< typename T, class comparar>
typename AVL<T, comparar>::iterator AVL<T, comparar>::find( const T & t){

    //Nodo iterador
    typename bintree < pair<T, typename AVL<T,comparar>::altura> >::node n = el_avl.root();

    //Iterador sobre el bintree que usaremos para crear el AVL::iterator
    typename bintree < pair<T, typename AVL<T,comparar>::altura> >::inorder_iterator it;

    //Iterador para devolver
    AVL<T, comparar>::iterator found;

    //Condicion de parada del bucle y información de si se ha encontrado
    bool para = false, encontrado = false;


    while( !para ){

        //Si la etiqueta es igual al valor buscado se para
        if( (*n).first == t ){

            para = true;
            encontrado = true;
        }
        else{

            //Si el valor actual es menor al buscado avanzamos a la izquierda
            if( AVL<T,comparar>::cmp(t, (*n).first) )

                //Si no se puede avanzar mas a la izquierda no se ha encontrado
                if( n.left().null() ){
                    para = true;
                    encontrado = false;
                }
                else
                    n = n.left();


            //Si no avanzamos a la derecha
            else
                if( n.right().null() ){
                    para = true;
                    encontrado = false;
                }
                else
                    n = n.right();

        }


    }



    //Una vez se ha parado el bucle quiere decir que o se ha encontrado o se ha llegado al nodo nulo( no se ha encontrado)

    //Si no se ha encontrado, pongo el iterador al end del bintree
    if ( !encontrado )

        it = el_avl.end_inorder();

    //Si se ha econtrado pongo el iterador apuntando al nodo usando un constructor de copia
    else

        it = typename bintree < pair<T, typename AVL<T,comparar>::altura> >::inorder_iterator(n);


    //Finalmente convierto el iterador del bintree a un iterador del AVL
    found = AVL<T, comparar>::iterator(it);

    return found;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL<T, comparar>::iterator AVL<T, comparar>::lower_bound( const T & t){

    //Iterador que devolveremos
    typename AVL<T, comparar>::iterator it( el_avl.begin() );


    //Buscamos el último elemento que es menor que t
    while( comparar( t, it->first ))
        it++;

    //Retrocedemos porque en este punto estamos un elemento despues al buscado
    it--;

    return it;

}


// **********************************************************************************//

template< typename T, class comparar>
typename AVL<T, comparar>::iterator AVL<T, comparar>::upper_bound( const T & t){

    typename AVL<T, comparar>::iterator it( el_avl.begin() );


    //Buscamos el último elemento que es menor que t
    while( comparar( t, it->first ))
        it++;

    //No hace falta retroceder porque queremos estar en el elemento mayor siguiente a t

    return it;

}

// **********************************************************************************//


///////////////////////////
//
//       iterator
//
///////////////////////////


// **********************************************************************************//

template< typename T, class comparar>
AVL< T, comparar>::iterator::iterator(){}

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::iterator::iterator(const AVL< T, comparar>::iterator & i){

    it = i.it;

}

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::iterator::iterator(const typename bintree< pair<T, typename AVL<T,comparar>::altura> >::inorder_iterator & i){

    it = i;

}

// **********************************************************************************//


template< typename T, class comparar>
bool AVL< T, comparar>::iterator::operator!=(const AVL< T, comparar>::iterator & i) const{

    return it != i.it;

}

// **********************************************************************************//


template< typename T, class comparar>
bool AVL< T, comparar>::iterator::operator==(const AVL< T, comparar>::iterator & i) const{

    return it == i.it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::iterator & AVL< T, comparar>::iterator::operator=(const AVL< T, comparar>::iterator & i){

    if( this != &i)
		it = i.it ;

	return *this ;

}

// **********************************************************************************//


template< typename T, class comparar>
T & AVL< T, comparar>::iterator::operator*(){

    return (*it).first;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::iterator & AVL< T, comparar>::iterator::operator++(){

    ++it;

    return *this;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::iterator & AVL< T, comparar>::iterator::operator--(){

    --it;

    return *this;

}

// **********************************************************************************//


///////////////////////////
//
//       const_iterator
//
///////////////////////////

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::const_iterator::const_iterator(){}

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::const_iterator::const_iterator(const AVL< T, comparar>::const_iterator & i){

    it = i.it;

}

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::const_iterator::const_iterator(const typename bintree< pair<T, typename AVL<T,comparar>::altura> >::const_inorder_iterator & i){

    it = i;

}

// **********************************************************************************//


template< typename T, class comparar>
bool AVL< T, comparar>::const_iterator::operator!=(const AVL< T, comparar>::const_iterator & i) const{

    return it != i.it;

}

// **********************************************************************************//


template< typename T, class comparar>
bool AVL< T, comparar>::const_iterator::operator==(const AVL< T, comparar>::const_iterator & i) const{

    return it == i.it;

}

// **********************************************************************************//



template< typename T, class comparar>
typename AVL< T, comparar>::const_iterator & AVL< T, comparar>::const_iterator::operator=(const AVL< T, comparar>::const_iterator & i){

    if( this != &i)
		it = i.it ;

	return *this ;

}

// **********************************************************************************//


template< typename T, class comparar>
const T & AVL< T, comparar>::const_iterator::operator*() const{

    return *it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::const_iterator & AVL< T, comparar>::const_iterator::operator++(){

    ++it;

    return *this;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::const_iterator & AVL< T, comparar>::const_iterator::operator--(){

    --it;

    return *this;

}

// **********************************************************************************//


///////////////////////////
//
//     reverse_iterator
//
///////////////////////////

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::reverse_iterator::reverse_iterator(){}

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::reverse_iterator::reverse_iterator(const AVL< T, comparar>::reverse_iterator & i){

    it = i.it;

}

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::reverse_iterator::reverse_iterator(const typename bintree< pair<T, typename AVL<T,comparar>::altura> >::inorder_iterator & i){

    it = i;

}

// **********************************************************************************//


template< typename T, class comparar>
bool AVL< T, comparar>::reverse_iterator::operator!=(const AVL< T, comparar>::reverse_iterator & i) const{

    return it != i.it;

}

// **********************************************************************************//


template< typename T, class comparar>
bool AVL< T, comparar>::reverse_iterator::operator==(const AVL< T, comparar>::reverse_iterator & i) const{

    return it == i.it;

}

// **********************************************************************************//



template< typename T, class comparar>
typename AVL< T, comparar>::reverse_iterator & AVL< T, comparar>::reverse_iterator::operator=(const AVL< T, comparar>::reverse_iterator & i){

    if( this != &i)
		it = i.it ;

	return *this ;

}

// **********************************************************************************//

template< typename T, class comparar>
T & AVL< T, comparar>::reverse_iterator::operator*(){

    return *it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::reverse_iterator & AVL< T, comparar>::reverse_iterator::operator++(){

    --it;

    return *this;

}

// **********************************************************************************//


///////////////////////////
//
//       const_reverse_iterator
//
///////////////////////////

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::const_reverse_iterator::const_reverse_iterator(){}


// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::const_reverse_iterator::const_reverse_iterator(const AVL< T, comparar>::const_reverse_iterator & i){

    it = i.it;

}

// **********************************************************************************//


template< typename T, class comparar>
AVL< T, comparar>::const_reverse_iterator::const_reverse_iterator(const typename bintree< pair<T, typename AVL<T,comparar>::altura> >::const_inorder_iterator & i){

    it = i;

}

// **********************************************************************************//


template< typename T, class comparar>
bool AVL< T, comparar>::const_reverse_iterator::operator!=(const AVL< T, comparar>::const_reverse_iterator & i) const{

    return it != i.it;

}

// **********************************************************************************//


template< typename T, class comparar>
bool AVL< T, comparar>::const_reverse_iterator::operator==(const AVL< T, comparar>::const_reverse_iterator & i) const{

    return it == i.it;

}

// **********************************************************************************//



template< typename T, class comparar>
typename AVL< T, comparar>::const_reverse_iterator & AVL< T, comparar>::const_reverse_iterator::operator=(const AVL< T, comparar>::const_reverse_iterator & i){

    if( this != &i)
		it = i.it ;

	return *this ;

}

// **********************************************************************************//

template< typename T, class comparar>
const T & AVL< T, comparar>::const_reverse_iterator::operator*() const{

    return *it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::const_reverse_iterator & AVL< T, comparar>::const_reverse_iterator::operator++(){

    --it;

    return *this;

}

// **********************************************************************************//


///////////////////////////////////////////////
//
//       BEGIN Y END PARA LOS ITERADORES
//
///////////////////////////////////////////////

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::iterator AVL< T, comparar>::begin(){

    AVL< T, comparar>::iterator it(el_avl.begin_inorder());
    return  it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::iterator AVL< T, comparar>::end(){

    AVL< T, comparar>::iterator it(el_avl.end_inorder());
    return it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::const_iterator AVL< T, comparar>::cbegin(){

    AVL< T, comparar>::const_iterator it(el_avl.begin_inorder());
    return  it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::const_iterator AVL< T, comparar>::cend(){

    AVL< T, comparar>::const_iterator it(el_avl.end_inorder());
    return it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::reverse_iterator AVL< T, comparar>::rbegin(){

    AVL< T, comparar>::reverse_iterator it(el_avl.begin_inorder());
    return  it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::reverse_iterator AVL< T, comparar>::rend(){

    AVL< T, comparar>::reverse_iterator it(el_avl.end_inorder());
    return it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::const_reverse_iterator AVL< T, comparar>::crbegin(){

    AVL< T, comparar>::const_reverse_iterator it(el_avl.begin_inorder());
    return  it;

}

// **********************************************************************************//


template< typename T, class comparar>
typename AVL< T, comparar>::const_reverse_iterator AVL< T, comparar>::crend(){

    AVL< T, comparar>::const_reverse_iterator it(el_avl.end_inorder());
    return it;

}

// **********************************************************************************//

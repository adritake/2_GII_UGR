
#ifndef __AVL_H__
#define __AVL_H__

/**
   TDA bintree AVL.

   Representa un árbol binario con nodos etiquetados con datos del tipo T.

   T debe tener definidas las operaciones:

   - T & operator=(const T & e);
   - bool operator!=(const T & e);
   - bool opertaor==(const T & e);


   Invariante de la representación:

   Para cada nodo, la diferencia de altura de sus dos hijos tiene que estar comprendida en [-1, 1]

*/





#include "bintree.h"
#include <utility>
#include <functional>


using namespace std;


template < typename T, class comparar = less<T> >
class AVL {
public:

    typedef int altura;

    //Constructores

    /**
       @brief Constructor primitivo por defecto.

       Crea un árbol nulo.
    */
    AVL();

    /**
       @brief Constructor primitivo.

       @param a árbol que se copia

        Crea un árbol duplicado exacto de a.
    */
    AVL( const AVL<T, comparar> & a );


    /**
       @brief Constructor primitivo.

       @param t Etiqueta para la raíz.

       Crea un árbol con un único nodo etiquetado con t.
    */
    AVL( const T & t);



    /**
       @brief Operador de asignación.

       @param a: árbol que se asigna.

       Destruye el contenido previo del receptor y le asigna un
       duplicado de a.
    */
    AVL<T, comparar> & operator=(const AVL<T, comparar> & a);


    /**
       Clase iterator bidireccional para recorrer el árbol, los elementos se recorren en segun
       el criterio comparar pasado en la plantilla
    */
    class iterator {
    public:
        iterator();
        iterator(const iterator & i);
        iterator(const typename bintree< pair<T, typename AVL<T,comparar>::altura> >::inorder_iterator & i);
        bool operator!=(const iterator & i) const;
        bool operator==(const iterator & i) const;
        iterator & operator=(const iterator & i);
        T & operator*();
        iterator & operator++();
        iterator & operator--();
    private:
        typename bintree< pair< T, altura > > ::inorder_iterator it;
        friend class AVL< T, comparar>;
    };

    /**
       Clase const_iterator bidireccional constante para recorrer el árbol, los elementos se recorren en segun
       el criterio comparar pasado en la plantilla
    */
    class const_iterator {
    public:
        const_iterator();
        const_iterator(const const_iterator & i);
        const_iterator(const typename bintree< pair<T, typename AVL<T,comparar>::altura> >::const_inorder_iterator & i);
        bool operator!=(const const_iterator & i) const;
        bool operator==(const const_iterator & i) const;
        const_iterator & operator=(const const_iterator & i);
        const T & operator*() const;
        const_iterator & operator++();
        const_iterator & operator--();
    private:
        typename bintree< pair< T, altura > > ::const_inorder_iterator it;
        friend class AVL< T, comparar>;
    };



    /**
       Clase reverse_iterator para recorrer el árbol en orde contrario, los elementos se recorren en segun
       el criterio comparar pasado en la plantilla
    */
    class reverse_iterator {
    public:
        reverse_iterator();
        reverse_iterator(const reverse_iterator & i);
        reverse_iterator(const typename bintree< pair<T, typename AVL<T,comparar>::altura> >::inorder_iterator & i);
        bool operator!=(const reverse_iterator & i) const;
        bool operator==(const reverse_iterator & i) const;
        reverse_iterator & operator=(const reverse_iterator & i);
        T & operator*();
        reverse_iterator & operator++();
    private:
        typename bintree< pair< T, altura > > ::inorder_iterator it;
        friend class AVL< T, comparar>;
    };



    /**
       Clase reverse_iterator constante para recorrer el árbol en orde contrario, los elementos se recorren en segun
       el criterio comparar pasado en la plantilla
    */
    class const_reverse_iterator {
    public:
        const_reverse_iterator();
        const_reverse_iterator(const const_reverse_iterator & i);
        const_reverse_iterator(const typename bintree< pair<T, typename AVL<T,comparar>::altura> >::const_inorder_iterator & i);
        bool operator!=(const const_reverse_iterator & i) const;
        bool operator==(const const_reverse_iterator & i) const;
        const_reverse_iterator & operator=(const const_reverse_iterator & i);
        const T & operator*() const;
        const_reverse_iterator & operator++();
        const_reverse_iterator & operator--();
    private:
        typename bintree< pair< T, altura > > ::const_inorder_iterator it;
        friend class AVL< T, comparar>;
    };

    //Begin y end para los iteradores
    const_reverse_iterator crbegin();
    const_reverse_iterator crend();
    reverse_iterator rbegin();
    reverse_iterator rend();
    const_iterator cbegin();
    const_iterator cend();
    iterator begin();
    iterator end();


    //Modificadores

    /**
       @brief Intercambiar árboles

       @param a: árbol que se intercambia.

       Intercambia el contenido del arbol actual
       por el de a.
    */
    void swap(  AVL< T,comparar > & a);

    /**
       @brief Insertar elemento

       @param x: etiqueta del elemento a insertar.

       @return  pair< iterator, bool> si se ha podido insertar
                devuelve un iterador al elemento insertado y true.
                En caso contrario devuelve un iterador al elemento
                que ya estaba y false.


       Inserta el elemento en el árbol y si procede,
       realiza un balanceo para que quede equilibrado.
    */
    pair< iterator, bool> insert( const T & x);


    /**
       @brief Eliminar un elemento.

       @param x: etiqueta del elemento a eliminar.

       @return  int,  devuelve el número de elementos
                borrados. En el caso de este árbol,
                devuelve 1 si se ha borrado o 0 si
                no se ha borrado.


       Inserta el elemento en el árbol y si procede,
       realiza un balanceo para que quede equilibrado.
    */
    int erase( const T & x);

    /**
       @brief Borrar árbol

       Elimina todo el contenido del árbol y se queda
       en estado nulo.
    */
    void clear();

    //Consultores


    /**
       @brief Tamaño del árbol

       @return  size_type

       Devuelve el tamaño del árbol.
    */
    typename bintree< pair<T,altura> >::size_type size();

    /**
       @brief Árbol vacío

       @return  bool: true si esta vacío, false en caso contrario

       Comprueba si el árbol esta vacío
    */
    bool empty();

    /**
       @brief Busca un elemento en el árbol

       @param t: etiqueta del elemento a encontrar.

       @return  AVL<T, comparar>:: iterator : Si se encuentra
                devuelve un iterador apuntando al elemento
                econtrado, o apuntando a AVL<T, comparar>::end()
                en caso contrario.

       Recorre el árbol hasta encontrar el elemento. Operacion O( log(n) )
    */
    iterator find( const T & t);

    /**
       @brief Lower bound de un elemento

       @param t: etiqueta del elemento a encontrar su lower bound.

       @return  AVL<T, comparar>:: iterator : Un iterador apuntando
                al lower bound del elemento.

       Busca el primer elemento que no se considera que va antes que t
    */
    iterator lower_bound( const T & t);

    /**
       @brief Upper bound de un elemento

       @param t: etiqueta del elemento a encontrar su upper bound.

       @return  AVL<T, comparar>:: iterator : Un iterador apuntando
                al upper bound del elemento

       Busca el primer elemento que se considera que va después que t
    */
    iterator upper_bound( const T & t);

public:


    // Metodos privados


    //Consultores de nodos


    /**
       @brief Altura de un nodo

       @param n: bintree < pair<T,altura> >::node nodo del que se desea
                 averiguar su altura

       @return  AVL<T, comparar>::altura : entero que indica su altura.

       Si es un nodo hoja su altura es 1, en caso contrario su altura es
       mayor que 1. Si es un nodo nulo su altura es 0.
    */
    altura h(  typename bintree < pair<T,altura> >::node & n);

    /**
       @brief Altura de un nodo

       @param n: bintree < pair<T,altura> >::const_node nodo constante
              del que se desea averiguar su altura.

       @return  AVL<T, comparar>::altura : entero que indica su altura

       Si es un nodo hoja su altura es 1, en caso contrario su altura es
       mayor que 1. Si es un nodo nulo su altura es 0.
    */
    altura h( const typename bintree < pair<T,altura> >::const_node & n);


    /**
       @brief Balanceo de un nodo

       @param n: bintree < pair<T,altura> >::node nodo
              del que se desea averiguar su balanceo.

       @return  int: Diferencia de la altura de sus hijos.

       Calcula la diferencia de la altura de su hijo izquierda menos la
       de su hijo derecha. Casos posibles:

        *            0: Su dos hijos están a la misma altura.
        *            1: Su hijo izquierda es una unidad más alto que el derecha.
        *           -1: Su hijo izquierda es una unidad más bajo que el derecha.
        *            2: Su hijo izquierda es una mas de una unidad más alto que el derecha ( Necesita balanceo ).
        *           -2: Su hijo izquierda es una mas de una unidad más bajo que el derecha ( Necesita balanceo ).
    */
    int balanceo(  const typename bintree < pair<T,altura> >::node & n );

    /**
       @brief Balancear nodo

       @param n: nodo a balancear


       Comprueba si el nodo necesita balanceo y si procede, realiza las rotaciones
       necesarias en el árbol para balancearlo.
    */
    void balancear( typename bintree < pair<T,altura> >::node & n );

    /**
       @brief Elimina un nodo hoja

       @param n: nodo hoja a eliminar


       Método usado por erase(), se encarga de eliminar un nodo en
       el caso de que éste sea una nodo hoja.
    */
    void erase_hoja( typename bintree < pair<T,altura> >::node & n );

    /**
       @brief Elimina un nodo hoja

       @param n: nodo interior a eliminar


       Método usado por erase(), se encarga de eliminar un nodo en
       el caso de que éste sea una nodo interno.
    */
    void erase_nodo_interno( typename bintree < pair<T,altura> >::node & n );

    /**
       @brief Rotación simple a la izquierda

       @param n: nodo a rotar.


       Método usado por balanceo( node n ), se encarga de hacer una rotación
       simple a la izquierda sobre ese nodo
    */
    void rsi( typename bintree < pair<T,altura> >::node & n );

    /**
       @brief Rotación simple a la derecha

       @param n: nodo a rotar.


       Método usado por balanceo( node n ), se encarga de hacer una rotación
       simple a la derecha sobre ese nodo
    */
    void rsd( typename bintree < pair<T,altura> >::node & n );

    /**
       @brief Rotación doble a la izquierda

       @param n: nodo a rotar.


       Método usado por balanceo( node n ), se encarga de hacer una rotación
       simple a la derecha sobre el hijo izquierda de ese nodo y luego una
       rotación simple a la izquierda sobre n.
    */
    void rdi( typename bintree < pair<T,altura> >::node & n );

    /**
       @brief Rotación doble a la derecha

       @param n: nodo a rotar.


       Método usado por balanceo( node n ), se encarga de hacer una rotación
       simple a la izquierda sobre el hijo derehca de ese nodo y luego una
       rotación simple a la derecha sobre n.
    */
    void rdd( typename bintree < pair<T,altura> >::node & n );

    // Representacion
    bintree <pair<T,altura> > el_avl;
    unsigned int tama;
    comparar cmp;


};
#include "avl.hxx"


#endif

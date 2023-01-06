#include <stdlib.h>
#include "A1_20946887-5_c4_lara_ignacio.h"

// Función que retorna el puntero a una lista
lista *crearLista() {
    lista *nuevaLista = (lista*)malloc(sizeof(lista));
    nuevaLista->inicio = NULL;
    return nuevaLista;
}

// Función que agrega un número al final de una lista
void agregarLista(lista *Lista, int numero) {
    nodoLista *nuevoNodo = (nodoLista*)malloc(sizeof(nodoLista));
    nuevoNodo->numero = numero;
    nuevoNodo->siguiente = NULL;

    nodoLista *puntero = Lista->inicio;
    if (puntero == NULL) {
        Lista->inicio = nuevoNodo;
    }
    else {
        while (puntero->siguiente != NULL) {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nuevoNodo;
    }

    
}

// Función que elimina el elemento posición de la lista
void eliminarLista(lista *Lista, int posicion) {
    int i = 1;
    
    if (posicion == 0) {

        Lista->inicio = Lista->inicio->siguiente;
        
    }
    else {
        nodoLista *puntero = Lista->inicio;
        while (i++ < posicion) {
            puntero->siguiente;
        }
        if (puntero->siguiente->siguiente == NULL) {
            puntero->siguiente == NULL;
        }
        else {
            puntero->siguiente = puntero->siguiente->siguiente;
        }
    }
}

// Función que retorna un puntero a árbol
bArbol* crearArbol() {
    bArbol *nuevoArbol = (bArbol*)malloc(sizeof(bArbol));
    nuevoArbol->inicio = NULL;
    nuevoArbol->nivel = NULL;
    return nuevoArbol;
}

// Función para la creación de los nodos del árbol binario
nodo *crearNodo() {
    nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo));
    nuevoNodo->contenido = NULL;
    nuevoNodo->derecha = NULL;
    nuevoNodo->izquierda = NULL;
    return nuevoNodo;
}

// Función para recorrer el árbol hasta obtener un objetivo
nodo *recorrerArbol(nodo *inicio, int objetivo) {
    if (inicio == NULL) {
        return NULL;
    }
    if (inicio->contenido == objetivo) {
        return inicio;
    }
    nodo *encontrado = recorrerArbol(inicio->izquierda, objetivo);
    if (encontrado != NULL) {
        return encontrado;
    }
    return recorrerArbol(inicio->derecha, objetivo);
}

// Función para buscar el nivel total del árbol
// Cada vez que baja a un nivel nuevo, aumenta el nivel del árbol
void buscarNivelArbol(nodo *inicio, bArbol *tree, int nivel) {
    if (nivel > tree->nivel) {

        tree->nivel += 1;
    }
    if (inicio->izquierda != NULL) {
        buscarNivelArbol(inicio->izquierda, tree, nivel + 1);
    }
    if (inicio->derecha != NULL) {
        buscarNivelArbol(inicio->derecha, tree, nivel + 1);
    }
}

// Función para agregar un nodo a un arbol
void agregarNodo(bArbol *tree, int dato, lista *Lista) {

    // Si la conexión del nodo no existe, la guarda para después
    if (dato > tree->ultimo) {
        agregarLista(Lista, dato);
        
    }
    else {
        // Busca al nodo padre y agrega el nodo, por defecto, a su hijo izquierdo, posteriormente, si se busca de nuevo,
        // se agrega al derecho
        nodo *nuevoNodo = crearNodo();
        tree->ultimo = tree->ultimo + tree->incremento;
        nuevoNodo->contenido = tree->ultimo;
        nodo *padre = recorrerArbol(tree->inicio, dato);

        if (padre->izquierda == NULL) {
            padre->izquierda = nuevoNodo;
            
        }   
        else {
            padre->derecha = nuevoNodo;
        }
        
    }
}

// Búsqueda de la cantidad de nodos por nivel
void buscarPorNivel(nodo *inicio, int nivel, int *punteroCantidad) {
    if (nivel == 0) {
        *punteroCantidad += 1;
    }
    else {
        if (inicio->izquierda != NULL) {
            buscarPorNivel(inicio->izquierda, nivel - 1, punteroCantidad);
        }  
        if (inicio->derecha != NULL) {
            buscarPorNivel(inicio->derecha, nivel - 1, punteroCantidad);
        }
    }
}

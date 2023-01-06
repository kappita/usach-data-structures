// Struct nodo del árbol
typedef struct sNodo {
    int contenido;
    struct sNodo *izquierda;
    struct sNodo *derecha;
} nodo;

// Struct del arbol
typedef struct sArbol {
    nodo *inicio;
    int incremento;
    int ultimo;
    int nivel;
} bArbol;

// Struct nodo de la lista enlazada
typedef struct sNodoLista {
    int numero;
    struct sNodoLista *siguiente;
} nodoLista;

// Struct lista
typedef struct sLista {
    nodoLista *inicio;
} lista;
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct Nodo
typedef struct sNodo {
    float numero;
    struct sNodo *siguiente;
} nodo;

// Struct lista
typedef struct sLista {
    nodo *inicio;
} lista;

// Struct vértice del grafo
typedef struct sVertice {
    int numero;
    lista *hacia;
    lista *peso;
} vertice;

// Crea una lista
lista *crearLista() {
    lista *nuevaLista = (lista*)malloc(sizeof(lista));
    nuevaLista->inicio = NULL;
    return nuevaLista;
}

// Función que agrega un nodo al final de la lista entregada
void agregarFinalLista(lista* listaNumeros, nodo* nuevoNodo) {
    nodo *puntero = listaNumeros->inicio;
    if (puntero == NULL) {
        listaNumeros->inicio = nuevoNodo;
    }
    else {
        while (puntero->siguiente != NULL) {
            puntero = puntero->siguiente;
        }
        puntero->siguiente = nuevoNodo;
    }
}

// Función que retorna el puntero a un nodo inicializado con un número
nodo *crearNodo(float numero) {
    nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo));
    nuevoNodo->numero = numero;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

// aplica dijkstra para encontrar el menor camino de inicio a destino
float dijkstra(int inicio, int destino, int totalNodos, vertice *grafo) {
    int nodosDisp[totalNodos], i, totalDisp = totalNodos, cercano;
    float recorridoActual, pesoNodos[totalNodos], pesoCercano;
    nodo *adyacentes, *pesoAdyacentes;
    for (i = 0; i < totalNodos; i++) {
        nodosDisp[i] = i;
        pesoNodos[i] = -1.0f;
    }

    int nodoActual = inicio;
    while (totalDisp != 0) {
        totalDisp -= 1;
        nodosDisp[nodoActual] = NULL;
        adyacentes = grafo[nodoActual].hacia->inicio;
        pesoAdyacentes = grafo[nodoActual].peso->inicio;
        cercano = NULL;
        recorridoActual = 0;
        while (adyacentes != NULL) {
            if (nodosDisp[(int)adyacentes->numero] != NULL) {
                if (pesoNodos[(int)adyacentes->numero] > recorridoActual + pesoAdyacentes->numero || pesoNodos[(int)adyacentes->numero] == -1.0f) {
                    pesoNodos[(int)adyacentes->numero] = recorridoActual + pesoAdyacentes->numero;
                }
                
                if (cercano == NULL) {
                    cercano = (int)adyacentes->numero;
                    pesoCercano = pesoAdyacentes->numero;
                }
                else if (pesoAdyacentes->numero > pesoCercano) {
                    cercano = (int)adyacentes->numero;
                    pesoCercano = pesoAdyacentes->numero;
                }
            }
            adyacentes = adyacentes->siguiente;
            pesoAdyacentes = pesoAdyacentes->siguiente;
            
        }

        nodoActual = cercano;
        recorridoActual += pesoCercano;

    }
    return pesoNodos[destino];
}

// Bloque principal

int main(int argc, char *argv[]) {
    int nodos, aristas, i, desde, hacia;
    float peso;
    FILE *fp = fopen(argv[1], "r");
    // Identifica las dos primeras líneas del archivo para obtener número de nodos y aristas
    fscanf(fp, "%d %d", &nodos, &aristas);

    // Inicializa un arreglo de vértices 
    vertice grafo[nodos];
    for (i = 0; i < nodos; i++) {
        grafo[i].numero = i;
        grafo[i].hacia = crearLista();
        grafo[i].peso = crearLista();
    }

    // Agrega todas las aristas en ambos nodos
    for (i = 0; i < aristas; i++) {
        fscanf(fp, "%d %d %f", &desde, &hacia, &peso);
        agregarFinalLista(grafo[desde].hacia, crearNodo((float)hacia));
        agregarFinalLista(grafo[desde].peso, crearNodo(peso));
        agregarFinalLista(grafo[hacia].hacia, crearNodo((float)desde));
        agregarFinalLista(grafo[hacia].peso, crearNodo(peso));
    }

    printf("%d", atoi(argv[2]));
    for (i = 0; i < nodos; i++) {
        if (i != atoi(argv[2])) {
            printf("%d,%d: %f\n", atoi(argv[2]), i, dijkstra(atoi(argv[2]), i, nodos, grafo));
        }
    }

    
}
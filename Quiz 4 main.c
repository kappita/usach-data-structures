#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "A1_20946887-5_c4_lara_ignacio.c"

// Bloque principal del código
int main(int argc, char* argv[]) {
    // Declaración de variables
    if (argc == 1) {
        printf("Ingrese un archivo de arbol");
        return 0;
    }
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Ingrese un archivo valido");
        return 0;
    }
    int cNodos, numeroNodo, i;
    lista *nodosRestantes = crearLista();
    bArbol *arbol = crearArbol();

    // Se comienza a leer los primeros tres o cuatro nodos, con el objetivo de obtener el incremento del árbol
    // Inicialmente, no tienen valor/contenido hasta que se encuentre el incremento
    fscanf(fp, "%d", &cNodos);
    fscanf(fp, "%d", &numeroNodo);
    arbol->inicio = crearNodo();

    fscanf(fp, "%d", &numeroNodo);
    arbol->inicio->contenido = numeroNodo;
    arbol->ultimo = numeroNodo;
    arbol->inicio->izquierda = crearNodo();
    
    fscanf(fp, "%d", &numeroNodo);
    cNodos -= 3;

    // En caso de que inicialmente hayan dos nodos asociados al nodo raíz, se inicializan sin valor
    if (numeroNodo == arbol->ultimo) {
        arbol->inicio->derecha = crearNodo();
        fscanf(fp, "%d", &numeroNodo);
        cNodos -= 1;
        // Obtiene el valor de incremento y le entrega valor a los nodos creados anteriormente
        arbol->incremento = numeroNodo - arbol->ultimo;
        arbol->ultimo = arbol->ultimo + arbol->incremento;
        arbol->inicio->izquierda->contenido = arbol->ultimo;
        arbol->ultimo = arbol->ultimo + arbol->incremento;
        arbol->inicio->derecha->contenido = arbol->ultimo;
        
        arbol->ultimo = arbol->ultimo + arbol->incremento;
        arbol->inicio->izquierda->izquierda = crearNodo();
        arbol->inicio->izquierda->izquierda->contenido = arbol->ultimo;
    }

    else {
        // Obtiene el valor de incremento y le entrega valor a los nodos creados anteriormente, en el caso
        // de que no hayan dos nodos asociados a la raíz
        arbol->incremento = numeroNodo - arbol->ultimo;
        arbol->ultimo = arbol->ultimo + arbol->incremento;
        arbol->inicio->izquierda->contenido = arbol->ultimo;

        arbol->ultimo = arbol->ultimo + arbol->incremento;
        arbol->inicio->izquierda->izquierda = crearNodo();
        arbol->nivel += 1;
        arbol->inicio->izquierda->izquierda->contenido = arbol->ultimo;

    }

    // Con el incremento obtenido, puede añadir al árbol todos los nodos restantes del archivo
    for (i = 0; i < cNodos; i++) {
        fscanf(fp, "%d", &numeroNodo);
        agregarNodo(arbol, numeroNodo, nodosRestantes);
    }

    // Agrega los nodos que no tenían padre inicialmente
    // y que fueron guardados en la lista enlazada de nodosRestantes
    nodoLista *faltante;
    int j;
    while (nodosRestantes->inicio != NULL) {
        faltante = nodosRestantes->inicio;
        j = 0;
        while (faltante != NULL) {
            if (faltante->numero <= arbol->ultimo) {
                agregarNodo(arbol, faltante->numero, nodosRestantes);
                eliminarLista(nodosRestantes, j);
            }
            faltante = faltante->siguiente;
            j += 1;
        }
    }

    // Obtiene el nivel del árbol
    buscarNivelArbol(arbol->inicio, arbol, 0);

    // Inicializa el proceso de entregar las ocupaciones por nivel
    // Declaración de variables
    int k;
    int totalNivel, totalMaximoArbol = 0, totalArbol = 0;
    float porcentaje;
    int *punteroTotal = &totalNivel;

    // Recorre todos los niveles encontrados, contando los nodos existentes, además de guardar los encontrados y el total
    // En dos variables, para posteriormente mostrar la ocupación total

    for (k = 0; k <= arbol->nivel; k++) {
        totalNivel = 0;
        buscarPorNivel(arbol->inicio, k, punteroTotal);
        totalArbol += totalNivel;
        totalMaximoArbol += ldexp(1, k);
        porcentaje = (float)totalNivel / (float)(ldexp(1, k)) * 100;
        printf("Ocupacion nivel %d: %.0f%%\n", k, porcentaje);
    }
    printf("Ocupacion arbol total: %.0f%%\n", (float)totalArbol/(float)totalMaximoArbol * 100);
    
    return 1;
}
    
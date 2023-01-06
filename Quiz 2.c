#include <stdio.h>
#include <stdlib.h>

// Struct Nodo
typedef struct sNodo {
    int numero;
    struct sNodo *siguiente;
} nodo;

// Struct lista
typedef struct sLista {
    nodo *inicio;
} lista;

// Función para iniciar una lista vacía
lista *crearLista() {
    lista *nuevaLista = (lista*)malloc(sizeof(lista));
    nuevaLista->inicio = NULL;
    return nuevaLista;
}

// Función que retorna el puntero a un nodo inicializado con un número
nodo *crearNodo(int numero) {
    nodo *nuevoNodo = (nodo*)malloc(sizeof(nodo));
    nuevoNodo->numero = numero;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
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

// Función para invertir los elementos entre dos posiciones de una lista
void invertirElementos(lista* listaNumeros, int primerElemento, int segundoElemento) {
    nodo *puntero = listaNumeros->inicio;
    nodo *primerPuntero;
    int aux;

    // Comprueba que los elementos estén ordenados para 
    // no alterar la búsqueda de punteros
    if (primerElemento > segundoElemento) {
        aux = primerElemento;
        primerElemento = segundoElemento;
        segundoElemento = aux;
    }

    // Búsqueda de punteros por posición
    // (aprovecha la búsqueda realizada por el primer elemento
    // para no recorrer dos veces la lista)
    int i = 0;
    while (i < primerElemento) {
        puntero = puntero->siguiente;
        i += 1;
    }
    primerPuntero = puntero;
    aux = puntero->numero;
    while (i < segundoElemento) {
        puntero = puntero->siguiente;
        i += 1;
    }

    primerPuntero->numero = puntero->numero;
    puntero->numero = aux;
}

// Escribe un archivo a partir de una lista
void escribirArchivoLista(FILE *archivo, lista *listaNumeros) {
    char numero[14];
    nodo *puntero = listaNumeros->inicio;
    while (puntero != NULL) {
        sprintf(numero, "%d", puntero->numero);
        fputs(numero, archivo);
        fputc(' ', archivo);
        puntero = puntero->siguiente;
    }
}

// Bloque principal
int main(int argc, char *argv[]) {
    // Se asegura de que estén los datos necesarios
    if (argc != 2) {
        printf("Recuerda ingresar el nombre del archivo con la lista de la forma: \n");
        printf("archivo.c nombre_archivo.txt");
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("El archivo ingresado no existe!");
        return 1;
    }

    FILE *fp1 = fopen("salida.txt", "w");
    int nDatos, numero, i, inicio, final;
    lista *listaNumeros = crearLista();

    // Obtiene los datos de la lista a partir del archivo
    fscanf(fp, "%d", &nDatos);
    for (i = 0; i < nDatos; i++) {
        fscanf(fp, "%d", &numero);
        agregarFinalLista(listaNumeros, crearNodo(numero));
    }

    // Escribe el archivo con la lista sin alterar
    escribirArchivoLista(fp1, listaNumeros);
    fputc('\n', fp1);

    // Obtiene los límites del archivo, luego calcula cuántas inversiones debe hacer
    // El módulo ayuda en caso de que el índice sea mayor que el número de datos
    fscanf(fp, "%d %d", &inicio, &final);
    inicio -= 1;
    final -= 1;
    int distancia = (int)(((float)(abs(inicio - final) + 1))/2);
    for (i = 0; i < distancia; i++) {
        invertirElementos(listaNumeros, (inicio + i) % (nDatos), (final - i) % (nDatos));
    }
    
    // Escribe en el archivo luego de alterar la lista y cierra los archivos
    nodo *puntero = listaNumeros->inicio;
    escribirArchivoLista(fp1, listaNumeros);
    fclose(fp);
    fclose(fp1);
    return 0;
}
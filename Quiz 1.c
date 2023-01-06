#include <stdio.h>

// Función para crear arreglo con los precios de las acciones
// Guarda un valor tipo int por línea (Posterior a la lectura de la primera línea del archivo.)
void crearListaPrecios(FILE *archivo, int *punteroprecios, int n_precios) {
    int i;
    for (i = 0; i < n_precios; i++) {
    fscanf(archivo, "%d", &punteroprecios[i]);
    }
    fclose(archivo);
}

// Va guardando información en la matriz (Arreglo[x][y]) a partir del archivo 2, guardando solo los 1's y 0's encontrados.
// Gracias a los punteros, sólo es necesario guardar linealmente los números encontrados.
void crearMatrizPaquetes(FILE *archivo, int *punteromat) {
    char caracter;
    int i = 0;
    while ((caracter = getc(archivo)) != EOF) {
        if ((caracter == '0') || (caracter == '1')) {
            punteromat[i++] = caracter - '0';
        } 
    }
    fclose(archivo);
}

// Función encargada de imprimir los valores de una fila de la matriz, junto al total entregado
// para la comunicación con el usuario.
void impresionLinea(int *punteromat, int linea, int n_precios, int total) {
    int i; 
    for (i = 0; i < n_precios; i++) {
        printf("%d ", punteromat[(linea * n_precios) + i]);
    }
    printf("con beneficio de %d. \n", total);

}

// Función encargada de recibir la matriz de paquetes y el arreglo de los precios
// multiplicarlos por índice y generar el archivo de salida junto a la impresión
// por consola de la información solicitada
// Además, guarda la posición y valor de los precios más altos y bajos para la salida 
// por consola.
void obtenerBeneficios(int *punteromat, int *punteroprecios, int largo, int n_precios) {
    int i, j, total, posmax = 0, posmin = 0, preciomax, preciomin;
    FILE *archivonuevo;
    archivonuevo = fopen("salida.txt", "w");
    
    // Ciclo para recorrer la matriz y multiplicarla
    // siendo (i * n_precios) la fila y j la columna
    // Así, sumando matriz[x][y] * puntero[j] al total.
    for (i = 0; i < largo; i++) {
        total = 0;
        for (j = 0; j < n_precios; j++) {
            total += (punteromat[(i * n_precios) + j]) * (punteroprecios[j]);
            
            // Parte de creación del archivo.
            fprintf(archivonuevo, "%d", punteromat[(i * n_precios) + j]);
            if (j == n_precios - 1) {
                fputc(':', archivonuevo);
            }
            else {
                fputc(' ', archivonuevo);
            }
        }


        // Parte de creación del archivo.
        fputc(' ', archivonuevo);
        fprintf(archivonuevo, "%d", total);
        fputc('\n', archivonuevo);


        // Obtención del máximo y mínimo de los beneficios,
        // reemplazando en caso de obtener un total mayor que el máximo anterior
        // o menor que el mínimo anterior, y recordando a cuál paquete corresponden.
        if (i == 0) {
            preciomin = total;
            preciomax = total;
        }
        else {
            if (total < preciomin) {
                preciomin = total;
                posmin = i;
            }
            else if (total > preciomax) {
                preciomax = total;
                posmax = i;
            }
        }
    }
    // Se cierra el archivo y se imprimen por consola los resultados obtenidos.
    fclose(archivonuevo);
    printf("La mejor configuracion es: ");
    impresionLinea(punteromat, posmax, n_precios, preciomax);
    printf("La peor configuracion es: ");
    impresionLinea(punteromat, posmin, n_precios, preciomin);

}



int main(int argc, char *argv[]) {
    // Variables
    FILE *fp1, *fp2;
    int largo, n_precios;

    // Se asegura de que se entregan los 2 archivos por consola y que existan.
    if (argc == 3) {
        fp1 = fopen(argv[1], "r");
        fp2 = fopen(argv[2], "r");

        if (fp1 == NULL) {
            printf("El archivo %s no existe o no se encuentra.\n", argv[1]);
        }

        else if (fp2 == NULL) {
            printf("El archivo %s no existe o no se encuentra.\n", argv[2]);
        }
        else {

            // Ejecuta en caso de no haber encontrado problemas, obteniendo el número de acciones y
            // número de paquetes para crear la matriz de paquetes y el arreglo de precios
            fscanf(fp1, "%d", &n_precios);
            fscanf(fp2, "%d", &largo);
            int matriz[largo][n_precios], arregloprecios[n_precios];

            // Además, crea un puntero a los arreglos para ser utilizados en
            // las funciones creadas anteriormente.
            int *punteromatriz, *punteroprecios;
            punteroprecios = &arregloprecios[0];
            punteromatriz = &matriz[0][0];

            // Bloque final ejecutando las funciones creadas.
            crearListaPrecios(fp1, punteroprecios, n_precios);
            crearMatrizPaquetes(fp2, punteromatriz);
            obtenerBeneficios(punteromatriz, punteroprecios, largo, n_precios);
        }
        

    }
    else {
        printf("Debe ingresar el nombre de los dos archivos. Intente de nuevo.");
    }
    
    
    
    return 0;
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct del libro de notas
typedef struct sLibroNotas {
    char asignatura[30];
    char nombreProfesor[30];
    int nivelAsignatura;
    float promedioNotas[3];
    float porcentajeEvaluacion[3];
} libroNotas;

// Struct nodo
typedef struct sNodo {
    libroNotas *libro;
    struct sNodo *siguiente;
} Nodo;

// Stuct lista
typedef struct sLista {
    Nodo *inicio; 
} Lista;

// Función para crear nodo a partir de un libro de notas
Nodo* crearNodo(libroNotas *libro) {
    int i;
    Nodo *nodo = (Nodo*)malloc(sizeof(Nodo));
    libroNotas *notas = (libroNotas*)malloc(sizeof(libroNotas));
    strncpy(notas->asignatura, libro->asignatura, 30);
    strncpy(notas->nombreProfesor, libro->nombreProfesor, 30);
    notas->nivelAsignatura = libro->nivelAsignatura;
    for (i=0; i < 3; i++) {
        notas->promedioNotas[i] = libro->promedioNotas[i];
        notas->porcentajeEvaluacion[i] = libro->porcentajeEvaluacion[i];
    }
    nodo->siguiente = NULL;
    nodo->libro = notas;
    return nodo;
}

// Inicia una lista, alocando memoria y retornando su puntero
Lista *iniciarLista() {
    Lista *nuevaLista = (Lista*)malloc(sizeof(Lista));
    nuevaLista->inicio = NULL;
    return nuevaLista;
}

// Inserta un elemento al inicio de la lista
void insertarInicio(Lista *listaEstudiantes, libroNotas *notas) {
    Nodo *nodo = crearNodo(notas);
    nodo->siguiente = listaEstudiantes->inicio;
    listaEstudiantes->inicio = nodo;
}

// Calculador nota final de asignatura
float notaFinal(Nodo *nodo) {
    int i;
    float nota = 0;
    for (i=0; i < 3; i++) {
        nota += (nodo->libro->promedioNotas[i] * nodo->libro->porcentajeEvaluacion[i]);
    }
    nota = (nota / 100);
    return nota;
}

// Función para ordenar de mayor a menor la lista
void ordenarNotas(Lista *listaEstudiantes) {
    Nodo *puntero = listaEstudiantes->inicio;
    libroNotas *aux;
    int ordenando = 1;
    while (ordenando == 1) {
        puntero = listaEstudiantes->inicio;
        while (puntero->siguiente != NULL) {
            if (notaFinal(puntero) < notaFinal(puntero->siguiente)) {
                aux = puntero->libro;
                puntero->libro = puntero->siguiente->libro;
                puntero->siguiente->libro = aux;
            }
            puntero = puntero->siguiente;
        }
        
        // Comprobación de si la lista está ordenada
        ordenando = 0;
        while (puntero->siguiente != NULL) {
            if (notaFinal(puntero) < notaFinal(puntero->siguiente)) {
                ordenando = 1;
            }
            puntero = puntero->siguiente;
        }
    }
}

// Revisa el archivo en búsqueda de asignaturas, con el formato
// asignatura, profesor, nivel, tipo de evaluacion, porcentaje de evaluación
void revisarAsignaturas(FILE *archivo1, Lista *Libros) {
    char caracter;
    char asignatura[30];
    char nombreProfesor[30];
    int nivel;
    char tipoEvaluacion;
    int porcentaje, i = 0;
    int eliminarLinea = 1;
    struct sLibroNotas notas;
    // Elimina la primera línea del archivo
    while (eliminarLinea == 1) {
        caracter = fgetc(archivo1);
        if (caracter == '\n') {
            eliminarLinea = 0;
        }
    }
    // Escanea la línea, y asigna en base al caracter C S T y cada 3 líneas, en un nodo
    while (fscanf(archivo1, "%s %s %d %c %d", asignatura, nombreProfesor, &nivel, &tipoEvaluacion, &porcentaje) == 5) {
        i++;
        strncpy(notas.asignatura, asignatura, 30);
        strncpy(notas.nombreProfesor, nombreProfesor, 30);
        notas.nivelAsignatura = nivel;
        switch (tipoEvaluacion) {
            case 'C':
                notas.porcentajeEvaluacion[0] = (float)porcentaje;
                notas.promedioNotas[0] = 0.0;
                break;
            case 'S':
                notas.porcentajeEvaluacion[1] = (float)porcentaje;
                notas.promedioNotas[1] = 0.0;
                break;
            case 'T':
                notas.porcentajeEvaluacion[2] = (float)porcentaje;
                notas.promedioNotas[2] = 0.0;
        }

        if (i == 3) {
            insertarInicio(Libros, &notas);
            i = 0;
        }
    }
}

// Muestra los porcentajes de cada tipo de evaluación guardados en un nodo
void mostrarPorcentajes(Lista *listaNotas) {
    Nodo *puntero = listaNotas->inicio;
    int iPorcentaje;
    printf("------------------------------------------------------\n");
    printf("\nLos porcentajes de cada evaluación por asignatura son: \n");
    while (puntero != NULL) {
        iPorcentaje = 0;
        printf("%s \n", puntero->libro->asignatura);
        printf("Profesor: %s\n", puntero->libro->nombreProfesor);
        printf("El porcentaje de controles es: %.0f\n", puntero->libro->porcentajeEvaluacion[iPorcentaje++]);
        printf("El porcentaje de solemnes es: %.0f\n", puntero->libro->porcentajeEvaluacion[iPorcentaje++]);
        printf("El porcentaje de tareas es: %.0f\n", puntero->libro->porcentajeEvaluacion[iPorcentaje]);
        printf("------------------------------------------------------\n");
        puntero = puntero->siguiente;
    }
}

// Busca una asignatura a partir de su nombre
Nodo* buscarAsignatura(Lista *listaNotas, char *asignatura) {
    Nodo *puntero = listaNotas->inicio;
    while (puntero != NULL) {
        if (strncmp(asignatura, puntero->libro->asignatura, 30) == 0) {
            return puntero;
        }
        puntero = puntero->siguiente;
    }
}

// Extrae las notas del archivo a partir del caracter C S T, y las asigna a su nodo a partir de los cambios de nombre o el final del archivo
void obtenerNotas(FILE *archivoNotas, Lista *listaNotas) {
    float promControl = 0, promSolemnes = 0, promTareas = 0, notaActual;
    int eliminarLinea = 1, totalControles = 0, totalSolemnes = 0, totalTareas = 0, totalPalabras;
    char asignatura[30], asignaturaAnterior[30], tipoEvaluacion, caracter;
    Nodo *puntero;
    while (eliminarLinea == 1) {
        caracter = fgetc(archivoNotas);
        if (caracter == '\n') {
            eliminarLinea = 0;
        }
    }
    totalPalabras = fscanf(archivoNotas, "%s %c %f", asignatura, &tipoEvaluacion, &notaActual);
    switch (tipoEvaluacion) {
        case 'C':
            promControl += notaActual;
            totalControles++;
            break;
        case 'S':
            promSolemnes += notaActual;
            totalSolemnes++;
            break;
        case 'T':
            promTareas += notaActual;
            totalTareas++;
    }
    
    int leyendo = 1;
    while (leyendo == 1) {
        strncpy(asignaturaAnterior, asignatura, 30);
        totalPalabras = fscanf(archivoNotas, "%s %c %f", asignatura, &tipoEvaluacion, &notaActual);
        // Asigna en base a el caracter C S T
        if (totalPalabras == 3) {
            if (strncmp(asignatura, asignaturaAnterior, 30) == 0) {
                switch (tipoEvaluacion) {
                    case 'C':
                        promControl += notaActual;
                        totalControles++;
                        break;
                    case 'S':
                        promSolemnes += notaActual;
                        totalSolemnes++;
                        break;
                    case 'T':
                        promTareas += notaActual;
                        totalTareas++;
                }
            }
            else {
                // Se asegura de no realizar una división 0/0 en caso de no haber
                // notas en un tipo de evaluación
                puntero = buscarAsignatura(listaNotas, asignaturaAnterior);
                if (totalControles > 0) {
                    puntero->libro->promedioNotas[0] = promControl / (float)totalControles;
                }
                if (totalSolemnes > 0) {
                    puntero->libro->promedioNotas[1] = promSolemnes / (float)totalSolemnes;
                }
                if (totalTareas > 0) {
                    puntero->libro->promedioNotas[2] = promTareas / (float)totalTareas;
                }
                promControl = 0;
                promSolemnes = 0;
                promTareas = 0;
                totalControles = 0;
                totalSolemnes = 0;
                totalTareas = 0;
                switch (tipoEvaluacion) {
                    case 'C':
                        promControl += notaActual;
                        totalControles++;
                        break;
                    case 'S':
                        promSolemnes += notaActual;
                        totalSolemnes++;
                        break;
                    case 'T':
                        promTareas += notaActual;
                        totalTareas++;
                }
            }
        }
        else {
            leyendo = 0;
            puntero = buscarAsignatura(listaNotas, asignaturaAnterior);
            if (totalControles > 0) {
                    puntero->libro->promedioNotas[0] = promControl / (float)totalControles;
                }
                if (totalSolemnes > 0) {
                    puntero->libro->promedioNotas[1] = promSolemnes / (float)totalSolemnes;
                }
                if (totalTareas > 0) {
                    puntero->libro->promedioNotas[2] = promTareas / (float)totalTareas;
                }
        }
    }
}

// Muestra las notas de un nodo entregado por puntero
void mostrarNotasAsignatura(Nodo *puntero) {
    int iPorcentaje = 0;
    printf("%s \n", puntero->libro->asignatura);
    printf("Profesor: %s\n", puntero->libro->nombreProfesor);
    printf("El promedio de controles es: %.2f\n", puntero->libro->promedioNotas[iPorcentaje++]);
    printf("El promedio de solemnes es: %.2f\n", puntero->libro->promedioNotas[iPorcentaje++]);
    printf("El promedio de tareas es: %.2f\n", puntero->libro->promedioNotas[iPorcentaje++]);
    printf("La nota final de la asignatura en lo que va de semestre es: %.2f\n", notaFinal(puntero));
    printf("------------------------------------------------------\n");
}

// Recorre todo el libro mostrando las notas de las evaluaciones
void consultarLibro(Lista *listaNotas) {
    Nodo *puntero = listaNotas->inicio;
    int iPorcentaje;
    float notaAsignatura;
    printf("------------------------------------------------------\n");
    printf("\nLos promedios de cada asignatura son: \n");
    while (puntero != NULL) {
        mostrarNotasAsignatura(puntero);
        puntero = puntero->siguiente;
    }
}

// Muestra todas las asignaturas presentes en listaNotas, además retorna la cantidad de asignaturas en la lista
int mostrarAsignaturas(Lista *listaNotas) {
    int posicion = 0;
    Nodo *puntero = listaNotas->inicio;
    while (puntero != NULL) {
        printf("%d.- %s\n", ++posicion, puntero->libro->asignatura);
        puntero = puntero->siguiente;
    }
    return posicion;
}

// Muestra la nota de una asignatura específica
void seleccionarAsignaturaNotas(Lista *listaNotas) {
    int max = mostrarAsignaturas(listaNotas), seleccion, i = 1, funcionando = 1;
    Nodo *puntero = listaNotas->inicio;
    while (funcionando == 1) {
        printf("\nIngrese la posicion de la asignatura para ver sus notas: ");
        scanf("%d", &seleccion);
        if (seleccion < 1 || seleccion > max) {
            printf("\nIngrese una opcion valida");
        }
        else {
            funcionando = 0;
            while (i++ < seleccion) {
                puntero = puntero->siguiente;
            }
            mostrarNotasAsignatura(puntero);
        }
    }
}

// Actualiza la nota seleccionada por el usuario
void actualizarNota(Lista *listaNotas) {
    int max, tipo, asignatura, seleccionAsignatura = 1, seleccionTipo = 1, seleccionNota = 1, i = 1;
    float nota;
    // Selección de la asignatura
    printf("------------------------------------------------------\n");
    printf("Las asignaturas para modificar son:\n");
    max = mostrarAsignaturas(listaNotas);
    while (seleccionAsignatura == 1) {
        printf("Ingrese el numero de la asignatura a modificar: ");
        scanf("%d", &asignatura);
        if (asignatura < 1 || asignatura > max) {
            printf("\nIngrese una opcion valida\n");
        }
        else {
            seleccionAsignatura = 0;
        }
    }

    // Selección del tipo de evaluación
    printf("Los promedios a reemplazar son:\n1.- Controles\n2.- Solemnes\n3.- Tareas\n");
    while (seleccionTipo == 1) {
        printf("Ingrese el numero de la asignatura a modificar: ");
        scanf("%d", &tipo);
        if (tipo < 1 || tipo > 3) {
            printf("\nIngrese una opcion valida\n");
        }
        else {
            seleccionTipo = 0;
        }
    }
    
    // Input de la nota para reemplazar
    while (seleccionNota == 1) {
        printf("Ingrese la nota que desea ingresar: ");
        scanf("%f", &nota);
        if (nota < 1.0 || nota > 7.0) {
            printf("\nIngrese una nota valida\n");
        }
        else {
            seleccionNota = 0;
        }
    }

    // Busca la asignatura en la lista de notas y modifica
    Nodo *puntero = listaNotas->inicio;
    while (i++ < asignatura) {
        puntero = puntero->siguiente;
    }
    puntero->libro->promedioNotas[tipo - 1] = nota;
    printf("La nota ha sido modificada\n");
    printf("------------------------------------------------------\n");
}

// Categoriza por notas rojas y azules
void separarNotas(Lista *listaNotas) {
    float nota;
    Nodo *puntero = listaNotas->inicio;
    printf("------------------------------------------------------\n");
    printf("Notas rojas:\n");
    while (puntero != NULL) {
        nota = notaFinal(puntero);
        if (nota < 4.0) {
            printf("%s: %.2f\n", puntero->libro->asignatura, nota);
        }
        puntero = puntero->siguiente;
    }
    printf("Notas azules: \n");
    puntero = listaNotas->inicio;
    while (puntero != NULL) {
        nota = notaFinal(puntero);
        if (nota >= 4.0) {
            printf("%s: %.2f\n", puntero->libro->asignatura, nota);
        }
        puntero = puntero->siguiente;
    }
    printf("------------------------------------------------------\n");
}

// Obtiene el promedio general sumando y contando los elementos de la lista
void promedioGeneral(Lista *listaNotas) {
    float promedioTotal = 0;
    int cAsignaturas = 0;
    Nodo *puntero = listaNotas->inicio;
    while (puntero != NULL) {
        promedioTotal += notaFinal(puntero);
        cAsignaturas++;
        puntero = puntero->siguiente;
    }
    printf("------------------------------------------------------\n\n");
    printf("El promedio general en lo que va de semestre es: %.2f\n\n", promedioTotal / (float)cAsignaturas);
    printf("------------------------------------------------------\n");
}

// Bloque principal
int main(int argc, char *argv[]) {
    // Se asegura de que estén los dos archivos necesarios
    if (argc != 3) {
        printf("Ingrese los dos archivos con los datos del libro de notas\n");
        printf("Recuerde que se deben ingresar por linea de comando en la ejecucion del programa, de la forma:\n");
        printf("nombre_programa nombre_archivo1.txt nombre_archivo2.txt");
        return 1;
    }
    // Apertura de archivos
    FILE *archivo1;
    FILE *archivo2;
    archivo1 = fopen(argv[1], "r");
    archivo2 = fopen(argv[2], "r");
    Lista *listaNotas = iniciarLista();
    int asignaturasAbiertas = 0, notasAbiertas = 0, funcionando = 1, opcion;
    printf("Bienvenido a su libro de notas\n");
    while (funcionando == 1) {
        printf("Que desea hacer?\n1.- Cargar porcentajes y asignaturas\n");
        printf("2.- Consultar porcentajes por asignatura \n3.- Cargar notas \n4.- Consultar libro\n");
        printf("5.- Consultar notas de una asignatura\n6.- Consultar notas rojas y azules\n");
        printf("7.- Actualizar una nota\n8.- Mostrar el promedio general\n9.- Salir\n");
        printf("Escriba la opcion a realizar: ");
        scanf("%d", &opcion);
        printf("\n");
        if (opcion < 10 && opcion > 0) {
            switch (opcion) {
                case 1:
                    revisarAsignaturas(archivo1, listaNotas);
                    asignaturasAbiertas = 1;
                    printf("Los porcentajes y asignaturas han sido cargados\n");
                    break;
                case 2:
                    if (asignaturasAbiertas == 1) {
                        mostrarPorcentajes(listaNotas);
                    }
                    else {
                        printf("Primero debe cargar los porcentajes y asignaturas!\n");
                    }
                    break;
                case 3:
                    if (asignaturasAbiertas == 1) {
                        obtenerNotas(archivo2, listaNotas);
                        ordenarNotas(listaNotas);
                        notasAbiertas = 1;
                        printf("Las notas han sido cargadas\n");
                    }
                    else {
                        printf("Primero debe cargar los porcentajes y asignaturas!\n");
                    }
                    break;
                case 4:
                    if (asignaturasAbiertas == 1) {
                        ordenarNotas(listaNotas);
                        consultarLibro(listaNotas);
                    }
                    else {
                        printf("Primero debe cargar las notas\n");
                    }
                    break;
                case 5:
                    if (notasAbiertas == 1) {
                        ordenarNotas(listaNotas);
                        seleccionarAsignaturaNotas(listaNotas);
                    }
                    else {
                        printf("Primero debe cargar las notas\n");
                    }
                    break;
                case 6:
                    if (notasAbiertas == 1) {
                        ordenarNotas(listaNotas);
                        separarNotas(listaNotas);
                    }
                    else {
                        printf("Primero debe cargar las notas\n");
                    }
                    break;
                case 7:
                    if (asignaturasAbiertas == 1) {
                        actualizarNota(listaNotas);
                    }
                    else {
                        printf("Primero debe cargar los porcentajes y asignaturas\n");
                    }
                    break;
                case 8:
                    if (asignaturasAbiertas == 1) {
                        promedioGeneral(listaNotas);
                    }
                    else {
                        printf("Primero debe cargar los porcentajes y asignaturas\n");
                    }
                    break;
                case 9:
                    funcionando = 0;
                    printf("Ten un lindo semestre\n");
            }
        }
        else {
            printf("Ingrese una opcion valida\n");
        }
    }
    return 0;
}
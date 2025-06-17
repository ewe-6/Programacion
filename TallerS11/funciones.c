#include <stdio.h>
#include <string.h>
#include"funciones.h"
Libros libro[MAX_LIBROS];
int LeerCantidadLibros(char* mensaje, int min, int max){
    int cantidad;
    printf("%s (entre %d y %d): ", mensaje, min, max);
    while (scanf("%d", &cantidad)!=1 || cantidad<min || cantidad>max) {
        printf("Dato mal ingresado, debe ser un numero entre %d y %d\n", min, max);
        while(getchar() != '\n');
        printf("%s (entre %d y %d): ", mensaje, min, max);
    }
    while(getchar() != '\n');
    return cantidad;
}
int LeerID(char* mensaje){
    int id;
    printf("%s: ", mensaje);
    while (scanf("%d", &id)!=1 || id <= 0) {
        printf("Dato mal ingresado\n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    while(getchar() != '\n');
    return id;
}
void LeerTitulo(char* mensaje, char* titulo, int tam){
    printf("%s: ", mensaje);
    if (fgets(titulo, tam, stdin) != NULL) {
        titulo[strcspn(titulo, "\n")] = 0;
    }
}
void LeerAutor(char* mensaje, char* autor, int tam){
    printf("%s: ", mensaje);
    if (fgets(autor, tam, stdin) != NULL) {
        autor[strcspn(autor, "\n")] = 0;
    }
}
int LeerAnio(char* mensaje, int min, int max){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1 || valor>max || valor<min) {
        printf("Dato mal ingresado, no puede ser mayor al anio actual (%d) o menor a 0\n", max);
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    while(getchar() != '\n');
    return valor;
}
void LeerEstado(char* mensaje, char* estado, int tam){
    do{
        printf("%s: ", mensaje);
        if (fgets(estado, tam, stdin) != NULL){
            estado[strcspn(estado, "\n")] = 0;
        }
        if (strcmp(estado, "Disponible")!=0 && strcmp(estado, "Prestado")!=0) {
            printf("Estado no valido, debe ser 'Disponible' o 'Prestado'\n");
        }
    } while (strcmp(estado, "Disponible")!=0 && strcmp(estado, "Prestado")!=0);
}
void LeerDatosLibros(int cantidad){
    for (int i=0; i<cantidad; i++){
        printf("LIBRO #%d:\n", i+1);
        do{
            libro[i].ids = LeerID("Ingrese ID del libro (tiene que ser un numero positivo, diferente de cero y unico)");
            if (BuscarLibroID(libro[i].ids, i) != -1) {
                printf("Esa ID ya existe, por favor ingresar una ID unica\n");
            }
        } while(BuscarLibroID(libro[i].ids, i) != -1);
        LeerTitulo("Ingrese Titulo del libro", libro[i].titulos, sizeof(libro[i].titulos));
        LeerAutor("Ingrese Autor del libro", libro[i].autores, sizeof(libro[i].autores));
        libro[i].anios = LeerAnio("Ingrese Anio de publicacion", 0, 2025);
        LeerEstado("Ingrese Estado del libro (Disponible/Prestado)", libro[i].estados, sizeof(libro[i].estados));
    }
}
void Menu(){
    printf("----------------------------------MENU----------------------------------\n");
    printf("1. Mostrar lista completa de libros\n");
    printf("2. Buscar libro\n");
    printf("3. Actualizar estado de un libro\n");
    printf("4. Eliminar libro\n");
    printf("5. Salir\n");
}
int LeerMenu(char* mensaje, int min, int max){
    int opcion;
    printf("%s: ", mensaje);
    while (scanf("%d", &opcion)!=1 || opcion<min || opcion>max){
        printf("Dato mal ingresado, debe ser un numero entre %d y %d\n", min, max);
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    while(getchar() != '\n');
    return opcion;
}
void MostrarLibros(int cantidad){
    printf("Lista de libros:\n");
    printf("ID\t\tTitulo\t\t\tAutor\t\tAnio\tEstado\n");
    for (int i = 0; i < cantidad; i++){
        printf("%d\t\t%s\t\t\t%s\t\t%d\t%s\n", libro[i].ids, libro[i].titulos, libro[i].autores, libro[i].anios, libro[i].estados);
    }
}
int OpcionBuscarLibro(char* mensaje){
    int opcion;
    printf("%s:\n", mensaje);
    printf("1. Buscar por ID\n");
    printf("2. Buscar por Titulo\n");
    printf("3. Volver al menu principal\n");
    opcion = LeerMenu("Ingrese su opcion", 1, 3);
    return opcion;
}
int BuscarLibroID(int idbuscar, int cantidad){
    int posicion=-1;
    for (int i=0; i<cantidad; i++){
        if (libro[i].ids==idbuscar){
            posicion=i;
            return posicion;
        }
    }
    return posicion;
}
int BuscarLibroTitulo(char titulobuscar[100], int cantidad){
    int posicion=-1;
    for (int i=0; i<cantidad; i++){
        if (strcmp(libro[i].titulos, titulobuscar) == 0){
            posicion=i;
            return posicion;
        }
    }
    return posicion;
}
void MostrarDatosLibro(int posicion){
    printf("DATOS DEL LIBRO #%d:\n", posicion+1);
    printf("ID: %d\nTitulo: %s\nAutor: %s\nAnio: %d\nEstado: %s\n", libro[posicion].ids, libro[posicion].titulos, libro[posicion].autores, libro[posicion].anios, libro[posicion].estados);
}
void ActualizarEstado(int posicion, char nuevoestado[11], char* estado){
    if (strcmp(libro[posicion].estados, nuevoestado) == 0) {
        printf("El estado del libro '%s' ya es '%s'\n", libro[posicion].titulos, nuevoestado);
        return;
    }
    else {
        strcpy(libro[posicion].estados, nuevoestado);
        printf("Estado del libro '%s' actualizado a '%s'\n", libro[posicion].titulos, libro[posicion].estados);
    }
}
void EliminarLibro(int posicion, int* cantidad){
    if(strcmp(libro[posicion].estados, "Prestado")==0) {
        printf("No se puede eliminar el libro '%s' porque esta prestado\n", libro[posicion].titulos);
        return;
    }
    else{
        for (int i=posicion; i<*cantidad; i++){
            libro[i] = libro[i+1];
            if (i==*cantidad-1) {
                libro[i+1].ids = 0;
            }
        }
        (*cantidad)--;
        printf("Libro eliminado exitosamente\n");
        printf("Cantidad actual de libros: %d\n", *cantidad);
    }
}

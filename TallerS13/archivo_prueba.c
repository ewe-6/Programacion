#include <stdio.h>
#include <string.h>
#define MAX_LIBROS 10
typedef struct {
    int ids, anios;
    char titulos[100], autores[50], estados[11];
} Libros;
Libros libro[MAX_LIBROS];

void GuardarLibrosEnArchivo(const char* libros, int cantidad) {
    FILE* archivo = fopen(libros, "w");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los datos.\n");
        return;
    }
    fprintf(archivo, "%5s%20s%20s%20s%20s%20s\n", "Num", "ID", "Titulo", "Autor", "Anio", "Estado");
    for (int i = 0; i < cantidad; i++) {
        fprintf(archivo, "%5d%20d%20s%20s%20d%20s\n", i+1, libro[i].ids, libro[i].titulos, libro[i].autores, libro[i].anios, libro[i].estados);
    }

    fclose(archivo);
}

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
    printf("1. Ingresar datos\n");
    printf("2. Mostrar lista completa de libros\n");
    printf("3. Buscar libro\n");
    printf("4. Actualizar estado de un libro\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
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
    printf("%20s%20s%20s%20s%20s\n", "ID", "Titulo", "Autor", "Anio", "Estado");
    for (int i = 0; i < cantidad; i++){
        printf("%20d%20s%20s%20d%20s\n", libro[i].ids, libro[i].titulos, libro[i].autores, libro[i].anios, libro[i].estados);
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

int main(){
    int opcion, cantlibros, idbusc, posidbusc, postitulobusc, opcionbuscar;
    char titulobusc[100], nuevoestado[11];
    do{
        Menu();
        opcion = LeerMenu("Seleccione una opcion del menu", 1, 6);
        switch (opcion){
            case 1:
                cantlibros=LeerCantidadLibros("Ingrese la cantidad de libros que desea registrar", 1, MAX_LIBROS);
                LeerDatosLibros(cantlibros);
                GuardarLibrosEnArchivo("libros.txt", cantlibros);
            break;
            case 2:
                MostrarLibros(cantlibros);
            break;
            case 3:
                opcionbuscar = OpcionBuscarLibro("Elija una opcion de busqueda");
                switch (opcionbuscar){
                    case 1:
                        idbusc = LeerID("Ingrese ID del libro a buscar");
                        posidbusc = BuscarLibroID(idbusc, cantlibros);
                        if (posidbusc != -1) {
                            MostrarDatosLibro(posidbusc);
                        } else {
                            printf("No se encontro el libro con ID: '%d'\n", idbusc);
                        }
                    break;
                    case 2:
                        LeerTitulo("Ingrese Titulo del libro a buscar", titulobusc, sizeof(titulobusc));
                        postitulobusc=BuscarLibroTitulo(titulobusc, cantlibros);
                        if (postitulobusc != -1) {
                            MostrarDatosLibro(postitulobusc);
                        } else {
                            printf("No se encontro el libro con el titulo: '%s'\n", titulobusc);
                        }
                    break;
                    case 3:
                        printf("Volviendo al menu principal\n");
                }
                        
            break;
            case 4:
                opcionbuscar=OpcionBuscarLibro("Como desea buscar el libro a actualizar?");
                switch (opcionbuscar){
                    case 1:
                        idbusc = LeerID("Ingrese ID del libro a actualizar");
                        posidbusc = BuscarLibroID(idbusc, cantlibros);
                        if (posidbusc != -1) {
                            LeerEstado("Ingrese el nuevo estado del libro", nuevoestado, sizeof(nuevoestado));
                            ActualizarEstado(posidbusc, nuevoestado, libro[posidbusc].estados);
                        } else {
                            printf("No se encontro el libro con ID: '%d'\n", idbusc);
                        }
                    break;
                    case 2:
                        LeerTitulo("Ingrese Titulo del libro a actualizar", titulobusc, sizeof(titulobusc));
                        postitulobusc = BuscarLibroTitulo(titulobusc, cantlibros);
                        if (postitulobusc != -1) {
                            LeerEstado("Ingrese el nuevo estado del libro", nuevoestado, sizeof(nuevoestado));
                            ActualizarEstado(postitulobusc, nuevoestado, libro[postitulobusc].estados);
                        } else {
                            printf("No se encontro el libro con el titulo: '%s'\n", titulobusc);
                        }
                    break;
                    case 3:
                        printf("Volviendo al menu principal\n");
                }
            break;
            case 5:
                opcionbuscar=OpcionBuscarLibro("Como desea buscar el libro a eliminar?");
                switch (opcionbuscar){
                    case 1:
                        idbusc = LeerID("Ingrese ID del libro a eliminar");
                        posidbusc = BuscarLibroID(idbusc, cantlibros);
                        if (posidbusc != -1) {
                            EliminarLibro(posidbusc, &cantlibros);
                        } else {
                            printf("No se encontro el libro con ID: '%d'\n", idbusc);
                        }
                    break;
                    case 2:
                        LeerTitulo("Ingrese Titulo del libro a eliminar", titulobusc, sizeof(titulobusc));
                        postitulobusc = BuscarLibroTitulo(titulobusc, cantlibros);
                        if (postitulobusc != -1) {
                            EliminarLibro(postitulobusc, &cantlibros);
                        } else {
                            printf("No se encontro el libro con el titulo: '%s'\n", titulobusc);
                        }
                    break;
                    case 3:
                        printf("Volviendo al menu principal\n");
                }
            break;
            case 6:
                printf("Saliendo del programa\n");
            break;
        }
    } while (opcion != 6);
    return 0;
}

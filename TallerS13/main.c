#include <stdio.h>
#include <string.h>

int NumeroDeLibros(){
    int num=0;
    FILE* archivo = fopen("libros.txt", "r");
    char linea[256];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
    num++;
    }
    fclose(archivo);
    return num;
}

void GuardarLibros(const char* nombre_archivo, int num, int id, const char* titulo, const char* autor, int anio, const char* estado) {
    FILE* archivo = fopen(nombre_archivo, "a");
    if (archivo == NULL) {
        return;
    }
    fprintf(archivo, "%5d%20d%20s%20s%20d%20s\n", num, id, titulo, autor, anio, estado);
    fclose(archivo);
}

int LeerCantidadLibros(char* mensaje, int min){
    int cantidad;
    printf("%s (mayor a %d): ", mensaje, min);
    while (scanf("%d", &cantidad)!=1 || cantidad<min) {
        printf("Dato mal ingresado, debe ser un numero mayor a %d\n", min);
        while(getchar() != '\n');
        printf("%s (mayor a %d): ", mensaje, min);
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
        printf("Dato mal ingresado, no puede ser mayor al anio actual (%d) o menor a %d\n", max, min);
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

void BuscarYMostrarPorID(const char* nombre_archivo, int id_buscado){
    FILE* archivo=fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    char linea[256];
    int id;
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%*d%d", &id);
        if (id == id_buscado) {
            printf("Libro encontrado:\n %s", linea);
            fclose(archivo);
            return;
        }
    }
    printf("No se encontró el libro con ID %d\n", id_buscado);
    fclose(archivo);
}

void LeerDatosLibros(int cantidad, int inicio){
    int ids, anios;
    char titulos[100], autores[50], estados[11];
    for (int i=inicio-1; i<cantidad; i++){
        printf("LIBRO #%d:\n", i+1);
        do{
            ids = LeerID("Ingrese ID del libro (tiene que ser un numero positivo, diferente de cero y unico)");
            if (BuscarLibroID(ids, i) != -1) {
                printf("Esa ID ya existe, por favor ingresar una ID unica\n");
            }
        } while(BuscarLibroID(ids, i) != -1);
        LeerTitulo("Ingrese Titulo del libro", titulos, sizeof(titulos));
        LeerAutor("Ingrese Autor del libro", autores, sizeof(autores));
        anios = LeerAnio("Ingrese Anio de publicacion", 0, 2025);
        LeerEstado("Ingrese Estado del libro (Disponible/Prestado)", estados, sizeof(estados));
        GuardarLibros("libros.txt", i+1, ids, titulos, autores, anios, estados);
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

void MostrarLibros(const char* nombre_archivo){
    printf("Lista de libros:\n");
    FILE* archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("No tiene ningun libro registrado\n");
        return;
    }
    char linea[256];
    fgets(linea, sizeof(linea), archivo);
    printf("%s", linea);
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        printf("%s", linea);
    }
    fclose(archivo);
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

void BuscarYMostrarPorTitulo(const char* nombre_archivo, const char* titulo_buscado) {
    FILE* archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    char linea[256], titulo[100];
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%*d%*d%99s", titulo);
        if (strcmp(titulo, titulo_buscado) == 0) {
            printf("Libro encontrado:\n %s", linea);
            fclose(archivo);
            return;
        }
    }
    printf("No se encontró el libro con título %s\n", titulo_buscado);
    fclose(archivo);
}

void ActualizarEstadoPorTitulo(const char* nombre_archivo, const char* titulo_buscado, const char* nuevo_estado){
    FILE* archivo = fopen(nombre_archivo, "r");
    FILE* temp = fopen("temp.txt", "w");
    if (!archivo || !temp) {
        printf("Error abriendo archivos.\n");
        return;
    }
    char linea[256], titulo[100], autor[50], estado[11];
    int num, id, anio, encontrado = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%d%d%99s%49s%d%10s", &num, &id, titulo, autor, &anio, estado);
        if (strcmp(titulo, titulo_buscado)==0) {
            fprintf(temp, "%5d%20d%20s%20s%20d%20s\n", num, id, titulo, autor, anio, nuevo_estado);
            encontrado = 1;
        } else {
            fputs(linea, temp);
        }
    }
    fclose(archivo);
    fclose(temp);
    remove(nombre_archivo);
    rename("temp.txt", nombre_archivo);
    if (encontrado)
        printf("Estado actualizado correctamente.\n");
    else
        printf("No se encontró el libro con Titulo %s\n", titulo_buscado);
}

void ActualizarEstadoPorID(const char* nombre_archivo, int id_buscado, const char* nuevo_estado) {
    FILE* archivo = fopen(nombre_archivo, "r");
    FILE* temp = fopen("temp.txt", "w");
    if (!archivo || !temp) {
        printf("Error abriendo archivos.\n");
        return;
    }
    char linea[256], titulo[100], autor[50], estado[11];
    int num, id, anio, encontrado = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%d%d%99s%49s%d%10s", &num, &id, titulo, autor, &anio, estado);
        if (id == id_buscado) {
            fprintf(temp, "%5d%20d%20s%20s%20d%20s\n", num, id, titulo, autor, anio, nuevo_estado);
            encontrado = 1;
        } else {
            fputs(linea, temp);
        }
    }
    fclose(archivo);
    fclose(temp);
    remove(nombre_archivo);
    rename("temp.txt", nombre_archivo);
    if (encontrado){
        printf("Estado actualizado correctamente.\n");
    }else{
        printf("No se encontró el libro con ID %d\n", id_buscado);
    }
}

void EliminarPorID(const char* nombre_archivo, int id_buscado) {
    FILE* archivo = fopen(nombre_archivo, "r");
    FILE* temp = fopen("temp.txt", "w");
    if (!archivo || !temp) {
        printf("Error abriendo archivos.\n");
        return;
    }
    char linea[256], titulo[100], autor[50], estado[11];
    int num, id, anio, eliminado = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%d%d%99s%49s%d%10s", &num, &id, titulo, autor, &anio, estado);
        if (id == id_buscado) {
            eliminado = 1; // No escribir esta línea
        } else {
            fputs(linea, temp);
        }
    }
    fclose(archivo);
    fclose(temp);
    remove(nombre_archivo);
    rename("temp.txt", nombre_archivo);
    if (eliminado){
        printf("Libro eliminado correctamente.\n");
    }else{
        printf("No se encontró el libro con ID %d\n", id_buscado);
    }
}

void EliminarPorTitulo(const char* nombre_archivo, const char* titulo_buscado) {
    FILE* archivo = fopen(nombre_archivo, "r");
    FILE* temp = fopen("temp.txt", "w");
    if (!archivo || !temp) {
        printf("Error abriendo archivos.\n");
        return;
    }
    char linea[256], titulo[100], autor[50], estado[11];
    int num, id, anio, eliminado = 0;
    while (fgets(linea, sizeof(linea), archivo)) {
        sscanf(linea, "%d%d%99s%49s%d%10s", &num, &id, titulo, autor, &anio, estado);
        if (strcmp(titulo, titulo_buscado)==0) {
            eliminado = 1;
        } else {
            fputs(linea, temp);
        }
    }
    fclose(archivo);
    fclose(temp);
    remove(nombre_archivo);
    rename("temp.txt", nombre_archivo);
    if (eliminado){
        printf("Libro eliminado correctamente.\n");
    }else{
        printf("No se encontró el libro con Titulo %s\n", titulo_buscado);
    }
}

int main(){
    int opcion, cantlibros, cantlibrosinicial, idbusc, posidbusc, postitulobusc, opcionbuscar;
    char titulobusc[100], nuevoestado[11];
    do{
        Menu();
        opcion = LeerMenu("Seleccione una opcion del menu", 1, 6);
        switch (opcion){
            case 1:
                cantlibrosinicial = NumeroDeLibros();
                cantlibros=cantlibrosinicial+LeerCantidadLibros("Ingrese la cantidad de libros que desea registrar", 1);
                LeerDatosLibros(cantlibros, cantlibrosinicial);
            break;
            case 2:
                MostrarLibros(cantlibros);
            break;
            case 3:
                opcionbuscar = OpcionBuscarLibro("Elija una opcion de busqueda");
                switch (opcionbuscar){
                    case 1:
                        idbusc = LeerID("Ingrese ID del libro a buscar");
                        BuscarYMostrarPorID("libros.txt", idbusc);
                    break;
                    case 2:
                        LeerTitulo("Ingrese Titulo del libro a buscar", titulobusc, sizeof(titulobusc));
                        BuscarYMostrarPorTitulo("libros.txt", titulobusc);
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
                        LeerEstado("Ingrese el nuevo estado del libro", nuevoestado, sizeof(nuevoestado));
                        ActualizarEstadoPorID("libros.txt", idbusc, nuevoestado);
                    break;
                    case 2:
                        LeerTitulo("Ingrese Titulo del libro a actualizar", titulobusc, sizeof(titulobusc));
                        LeerEstado("Ingrese el nuevo estado del libro", nuevoestado, sizeof(nuevoestado));
                        ActualizarEstadoPorTitulo("libros.txt", titulobusc, nuevoestado);
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
                        EliminarPorID("libros.txt", idbusc);
                    break;
                    case 2:
                        LeerTitulo("Ingrese Titulo del libro a eliminar", titulobusc, sizeof(titulobusc));
                        EliminarPorTitulo("libros.txt", titulobusc);
                        
                    break;
                    case 3:
                        printf("Volviendo al menu principal\n");

                }
            break;
            case 6:
                printf("Saliendo del programa\n");
            break;
        }
    } while(opcion!=6);
    return 0;
}

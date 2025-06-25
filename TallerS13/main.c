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
        printf("Error al abrir el archivo '%s' para guardar los datos.\n", nombre_archivo);
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

int BuscarLibroTitulo(const char* nombre_archivo, const char* titulo_buscar, char* linea_encontrada){
    FILE* archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo '%s'.\n", nombre_archivo);
        return -1;
    }

    char linea[256];
    fgets(linea, sizeof(linea), archivo); // Leer la cabecera del archivo

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        char titulo[100];
        sscanf(linea, "%*d %*d %99s", titulo); // Extraer el título
        if (strcmp(titulo, titulo_buscar) == 0) {
            strcpy(linea_encontrada, linea); // Copiar la línea encontrada
            fclose(archivo);
            return 1; // Encontrado
        }
    }

    fclose(archivo);
    return 0; // No encontrado
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
    int opcion, cantlibros, cantlibrosinicial, idbusc, posidbusc, postitulobusc, opcionbuscar;
    char titulobusc[100], nuevoestado[11];
    do{
        Menu();
        opcion = LeerMenu("Seleccione una opcion del menu", 1, 6);
        switch (opcion){
            case 1:
                cantlibrosinicial = NumeroDeLibros();
                cantlibros=LeerCantidadLibros("Ingrese la cantidad de libros que desea registrar", 1);
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
                GuardarLibrosFinal("libros.txt", cantlibros);
                printf("Saliendo del programa\n");
            break;
        }
    } while(opcion!=6);
    return 0;
}

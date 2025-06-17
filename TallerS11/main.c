#include <stdio.h>
#include <string.h>
#include"funciones.h"
int main(){
    int opcion, cantlibros, idbusc, posidbusc, postitulobusc, opcionbuscar;
    char titulobusc[100], nuevoestado[11];
    cantlibros=LeerCantidadLibros("Ingrese la cantidad de libros que desea registrar", 1, MAX_LIBROS);
    LeerDatosLibros(cantlibros);
    do{
        Menu();
        opcion = LeerMenu("Seleccione una opcion del menu", 1, 5);
        switch (opcion){
            case 1:
                MostrarLibros(cantlibros);
            break;
            case 2:
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
            case 3:
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
            case 4:
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
            case 5:
                printf("Saliendo del programa\n");
            break;
        }
    } while (opcion != 5);
    return 0;
}

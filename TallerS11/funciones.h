#define MAX_LIBROS 10
typedef struct {
    int ids, anios;
    char titulos[100], autores[50], estados[11];
} Libros;
extern Libros libro[MAX_LIBROS];
int LeerCantidadLibros(char* mensaje, int min, int max);
int LeerID(char* mensaje);
int LeerAnio(char* mensaje, int min, int max);
void LeerTitulo(char* mensaje, char* titulo, int tam);
void LeerAutor(char* mensaje, char* autor, int tam);
void LeerEstado(char* mensaje, char* estado, int tam);
void LeerDatosLibros(int cantidad);
void Menu();
int LeerMenu(char* mensaje, int min, int max);
void MostrarLibros(int cantidad);
int OpcionBuscarLibro(char* mensaje);
int BuscarLibroID(int idbuscar, int cantidad);
int BuscarLibroTitulo(char titulobuscar[100], int cantidad);
void MostrarDatosLibro(int posicion);
void ActualizarEstado(int posicion, char nuevoestado[11], char* estado);
void EliminarLibro(int posicion, int* cantidad);

#define PRODUCTOS 10
#define LONG 50
float RLeer(char mensaje[], float min, int num);
float Suma(float valor[PRODUCTOS], int num);
float Promedio(float total, float cant);
float Min(float valor[PRODUCTOS], int num);
int NumMin(float valor[PRODUCTOS], int num);
float Max(float valor[PRODUCTOS], int num);
int NumMax(float valor[PRODUCTOS], int num);
void Menu();
int LeerMenu(char mensaje[], int min, int max);
int ContinuarLectura(char mensaje[], int min, int max);
float EncontrarProducto(char nombre[][LONG], float precio[], int num);
int Programa(char nombre[][LONG], float precios[], int cont);
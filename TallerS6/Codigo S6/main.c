/*  Comandos para enlazar los archivos
gcc -c .\funciones.c .\main.c
gcc .\funciones.o .\main.o -o TallerS6
.\TallerS6.exe
*/
#include<stdio.h>
#include"funciones.h"
int main(){
    int cont, seguir, contador=0;
    float precio[PRODUCTOS];
    char nombre[PRODUCTOS][LONG];
    for(int i=0; i<PRODUCTOS; i++){
        printf("Colocar el nombre del producto #%d: ", i+1);
        scanf("%s", nombre[i]);
        while(getchar()!='\n');
        precio[i]=RLeer("Colocar el precio del producto", 0, i+1);
        seguir=ContinuarLectura("Desea registrar otro producto? 1=SI 0=NO: ", 0, 1);
        if (seguir==0){
            i=20;
        }
        contador++;
    }
    Menu();
    cont=Programa(nombre, precio, contador);
}
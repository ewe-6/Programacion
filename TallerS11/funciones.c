#include <stdio.h>
#include <string.h>
#include"funciones.h"
int LeerCodigo(char* mensaje){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
int LeerAnio(char* mensaje){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
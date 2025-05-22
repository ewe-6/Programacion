#include <stdio.h>
#include "lecturas.h"
// Para la lectura de números enteros, sin condiciones
int LeerEnteros(char* mensaje){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números enteros entre dos números, sin incluirlos
int E2LeerEnteros (char* mensaje, int min, int max){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor<=min, valor>=max){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números enteros mayores a cierto número
int E1MinLeerEnteros (char* mensaje, int min){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor<=min){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números enteros menores a cierto número
int E1MaxLeerEnteros (char* mensaje, int max){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor>=max){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números enteros entre dos números, incluyendo estos
int C2LeerEnteros (char* mensaje, int min, int max){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor<min, valor>max){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números enteros mayores o iguales a cierto número
int C1MinLeerEnteros (char* mensaje, int min){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor<min){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números enteros menores o iguales a cierto número
int C1MaxLeerEnteros (char* mensaje, int max){
    int valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor>max){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números reales, sin condiciones
float LeerReal(char* mensaje){
    float valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números reales entre dos números, sin incluirlos
float E2LeerReal (char* mensaje, float min, float max){
    float valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor<=min, valor>=max){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números reales mayores a cierto número
float E1MinLeerReal (char* mensaje, float min){
    float valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor<=min){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números reales menores a cierto número
float E1MaxLeerReal (char* mensaje, float max){
    float valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor>=max){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números reales entre dos números, incluyendo estos
float C2LeerReal (char* mensaje, float min, float max){
    float valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor<min, valor>max){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números reales mayores o iguales a cierto número
float C1MinLeerReal (char* mensaje, float min){
    float valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor<min){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
// Para la lectura de números reales menores o iguales a cierto número
float C1MaxLeerReal (char* mensaje, float max){
    float valor;
    printf("%s: ", mensaje);
    while (scanf("%d", &valor)!=1, valor>max){
        printf("Dato mal ingresado \n");
        while(getchar() != '\n');
        printf("%s: ", mensaje);
    }
    return valor;
}
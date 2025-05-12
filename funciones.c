#include <stdio.h>
#include <string.h>
#include"funciones.h"
float RLeer(char mensaje[], float min, int num){
    float valor;
    printf("%s #%d: ", mensaje, num);
    while(scanf("%f", &valor)!=1 || valor<=min){
        printf("Se ha colocado un valor erroneo\n");
        while(getchar()!='\n');
        printf("%s #%d: ", mensaje, num);
    }
    return valor;
}
float Suma(float valor[PRODUCTOS], int num){
    float resultado=0;
    for (int i=0; i<num; i++){
        resultado+=valor[i];
    }
    return resultado;
}
float Promedio(float total, float cant){
    float prom;
    prom=total/cant;
    return prom;
}
float Min(float valor[PRODUCTOS], int num){
    float menor;
    menor=valor[0];
    for (int i=1; i<num; i++){
        if (valor[i]<menor){
            menor=valor[i];
        }
    }
    return menor;
}
int NumMin(float valor[PRODUCTOS], int num){
    int numero;
    float menor;
    numero=0;
    menor=valor[0];
    for (int i=1; i<num; i++){
        if (valor[i]<menor){
            numero=i;
        }
    }
    return numero;
}
float Max(float valor[PRODUCTOS], int num){
    float mayor;
    mayor=valor[0];
    for (int i=1; i<num; i++){
        if (valor[i]>mayor){
            mayor=valor[i];
        }
    }
    return mayor;
}
int NumMax(float valor[PRODUCTOS], int num){
    int numero;
    float mayor;
    numero=0;
    mayor=valor[0];
    for (int i=1; i<num; i++){
        if (valor[i]>mayor){
            numero=i;
        }
    }
    return numero;
}
void Menu(){
    printf("------------------------MENU DE ACCIONES------------------------\n");
    printf("0. Calculo de precio total del inventario\n");
    printf("1. Encontrar el producto mas caro y el mas barato\n");
    printf("2. Precio promedio de los productos\n");
    printf("3. Encontrar un producto por su nombre\n");
    printf("4. Salir del programa\n");
}
int LeerMenu(char mensaje[], int min, int max){
    int valor;
    printf("%s", mensaje);
    while(scanf("%d", &valor)!=1 || valor>max || valor<min){
        printf("Se ha colocado un valor erroneo\n");
        while(getchar()!='\n');
        printf("%s", mensaje);
    }
    return valor;
}
int ContinuarLectura(char mensaje[], int min, int max){
    int valor;
    printf("%s", mensaje);
    while(scanf("%d", &valor)!=1 || valor>max || valor<min){
        printf("Se ha colocado un valor erroneo\n");
        while(getchar()!='\n');
        printf("%s", mensaje);
    }
    return valor;
}
float EncontrarProducto(char nombre[][LONG], float precio[], int num){
    char encontrar[LONG];
    float precio_producto=0;
    int cont;
    do{
        printf("Ingrese el producto que desea buscar: ");
        scanf("%s", &encontrar);
        for(int i=0; i<num; i++){
            if(strcmp(encontrar, nombre[i])==0){
                precio_producto=precio[i];
            }
        }
        if(precio_producto==0){
            cont=ContinuarLectura("Ha colocado un producto no existente, desea intentar otra vez? 1=SI 0=No: ", 0, 1);
            if (cont==0){
                return -1;
            }
        }
    } while (precio_producto==0);
    return precio_producto;
}
int Programa(char nombre[][LONG], float precios[], int cont){
    int contin, num_max, num_min, count=0, conta;
    float total_precio, menor, mayor, promedio_prod, prod_busc;
    do{
        if (count>0){
            conta=LeerMenu("Desea ver el menu? SI=1, NO=0: ", 0, 1);
            if(conta==1){
                Menu();
            }
        }
        contin=LeerMenu("Que desea hacer? (Ingrese un numero del 0 al 4): ", 0, 4);
        switch (contin){
        case 0:
            printf("El precio total del inventario es de $%.2f\n", total_precio=Suma(precios, cont));
            break;
        case 1:
            num_min=NumMin(precios, cont);
            num_max=NumMax(precios, cont);
            printf("El producto con el menor precio es '%s', con un precio de $%.2f\n", nombre[num_min], menor=Min(precios, cont));
            printf("El producto con el mayor precio es '%s', con un precio de $%.2f\n", nombre[num_max], mayor=Max(precios, cont));
            break;
        case 2:
            printf("El precio promedio de los productos es $%.2f\n", promedio_prod=Promedio(total_precio, cont));
            break;
        case 3:
            prod_busc=EncontrarProducto(nombre, precios, cont);
            if (prod_busc==-1){
                printf("El producto que se intento buscar no existe\n");
            }
            else {
                printf("El precio del producto buscado es de $%.2f\n", prod_busc);
            }
            break;
        case 4:
            printf("\nSaliendo del programa\n");
            return 0;
            break;
        default:
            break;
        }
        count++;
        printf("------------------------------------------------------------\n");
    } while (contin!=4);
}
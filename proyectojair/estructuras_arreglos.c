    /*#include<stdio.h>
    #define MAX 3
  
    struct Estudiante
        {
            int codigo;
            char nombre[15];
            float notas[3];
        };
        struct Estudiante estudiantes[MAX];
        void ingresarDatos();
        void imprimir();

    int main(){
        
        
        void imprimir(){
            printf("%20s%20s%20s%20s%20s", "Codigo", "Nombre", "Nota1", "Nota2", "Nota3\n");
            for (int i = 0; i < MAX; i++)
            {
                printf("%20d%20s%20.2f%20.2f%20.2f",estudiantes[i].codigo,estudiantes[i].nombre,estudiantes[i].notas[0],estudiantes[i].notas[1],estudiantes[i].notas[2]);
            }
            
            
        }
    
        return 0;
    
    void ingresarDatos()
    {
        for (int i = 0; i < MAX; i++)
        {
            printf("Ingrese el codigo del estudiante");
            scanf("%d", &estudiantes[i].codigo);
            printf("Ingrese el nombre del estudiante");
            scanf("%s", &estudiantes[i].nombre);
            for (int j = 0; j < 3; j++)
            {
                printf("Ingrese las notas del estudiante");
                scanf("%f", &estudiantes[i].notas[j]);
            }


        }
    
    }
}
    */
   #include <stdio.h>
#define MAX 3

struct Estudiante {
    int codigo;
    char nombre[15];
    float notas[3];
};

struct Estudiante estudiantes[MAX];

void ingresarDatos();
void imprimir();

int main() {
    ingresarDatos(); // Llamar a la función para ingresar datos
    imprimir();      // Llamar a la función para imprimir los datos
    return 0;
}

void ingresarDatos() {
    for (int i = 0; i < MAX; i++) {
        printf("Ingrese el codigo del estudiante: ");
        scanf("%d", &estudiantes[i].codigo);
        printf("Ingrese el nombre del estudiante: ");
        scanf("%s", estudiantes[i].nombre); // No necesitas el operador '&' para cadenas
        for (int j = 0; j < 3; j++) {
            printf("Ingrese la nota %d del estudiante: ", j + 1);
            scanf("%f", &estudiantes[i].notas[j]);
        }
    }
}

void imprimir() {
    printf("%20s%20s%20s%20s%20s\n", "Codigo", "Nombre", "Nota1", "Nota2", "Nota3");
    for (int i = 0; i < MAX; i++) {
        printf("%20d%20s%20.2f%20.2f%20.2f\n",
               estudiantes[i].codigo,
               estudiantes[i].nombre,
               estudiantes[i].notas[0],
               estudiantes[i].notas[1],
               estudiantes[i].notas[2]);
    }
}
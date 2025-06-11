#include <stdio.h>
int main(){
    struct Estudiante
    {
        int codigo;
        char nombre[15];
        float notas[3];
    }estudiante1, estudiante2;
    printf("Ingrese el codigo del estudiante");
    scanf("%d", &estudiante1.codigo);
    printf("Ingrese el nombre del estudiante");
    scanf("%s", &estudiante1.nombre);
    for (int i = 0; i < 3; i++)
    {
        printf("Ingrese las notas del estudiante");
        scanf("%f", &estudiante1.notas[i]);
    }
    
printf("%20s%20s%20s%20s%20s", "Codigo", "Nombre", "Nota1", "Nota2", "Nota3\n");
printf("%20d%20s%20.2f%20.2f%20.2f",estudiante1.codigo,estudiante1.nombre,estudiante1.notas[0],estudiante1.notas[1],estudiante1.notas[2]);
    return 0;
}
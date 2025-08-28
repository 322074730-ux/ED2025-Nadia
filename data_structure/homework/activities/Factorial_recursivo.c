#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

int factRecursion(int n) {
    if (n < 0)
        return 0; // No definido para negativos
    else if (n == 0 || n == 1)
        return 1;
    else
        return n * factRecursion(n - 1);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <numero>\n", argv[0]);
        return 1;
    }

    int num = atoi(argv[1]);   // convertir argumento a entero
    int resultado = factRecursion(num); // calcular factorial
    
    printf("El factorial de %d es: %d\n", num, resultado);

    return 0;
}

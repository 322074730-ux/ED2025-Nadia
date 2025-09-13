#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int factTail(int n, int a) {
    if (n < 0)
        return 0;
    else if (n == 0)
        return 1;
    else if (n == 1)
        return a;
    else
        return factTail(n - 1, n * a);
}

int factorial(int n) {
    return factTail(n, 1);
}

int main(int argc, char *argv[]) {
    int i;
    char *num = argv[1]; 
    int valor = atoi(num);
    int resultado = factorial(valor);

    for (i = 0; i < argc; i++) 
        printf("argv[%d] = '%s'\n", i, argv[i]);

    for (i = 0; i < strlen(num); i++) 
        printf("num[%d] = '%c'\n", i, num[i]);

    printf("factorial(%d) = %d\n", valor, resultado);

    return 0;
}

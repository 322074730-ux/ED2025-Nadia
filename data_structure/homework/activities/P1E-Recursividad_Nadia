#include <stdio.h>
#include <stdlib.h>
long long int factRecursion(long long int n) {
    if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (n == 1) {
        return 1;
    } else {
        return n * factRecursion(n - 1);
    }
}
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <numero>\n", argv[0]);
        return 1;
    }
    char *endptr;
    long long num = strtoll(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        fprintf(stderr, "Error: '%s' no es un numero entero valido\n", argv[1]);
        return 1;
    }
    long long resultado = factRecursion(num);

    if (num < 0) {
        fprintf(stderr, "Error: No existe factorial para numeros negativos (%lld)\n", num);
        return 1;
    }
    printf("%lld! = %lld\n", num, resultado);
    return 0;
}

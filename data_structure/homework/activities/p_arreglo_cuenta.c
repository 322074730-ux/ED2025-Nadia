#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Error: Debe proporcionar el número de cuenta como argumento.\n");
        printf("Uso: %s <numero_de_cuenta>\n", argv[0]);
        return 1;
    }
    
    char *num_cuenta = argv[1];
    int cantidad_numeros = 10;
    int longitud = strlen(num_cuenta);
    int ultimo_digito = num_cuenta[longitud - 1] - '0';
    
    int pares[cantidad_numeros];
    for (int i = 0; i < cantidad_numeros; i++) {
        pares[i] = (i + 1) * 2;
    }
    
    printf("| ");
    for (int i = cantidad_numeros - 1; i >= 0; i--) {
        printf("%d | ", pares[i]);
    }
    printf("\n");
    
    if (ultimo_digito >= 0 && ultimo_digito < cantidad_numeros) {
        pares[ultimo_digito] = -1;
    }
    
    printf("Indice | ");
    for (int i = 0; i < cantidad_numeros; i++) {
        printf("%d | ", i);
    }
    printf("\n");
    
    printf("Valor  | ");
    for (int i = 0; i < cantidad_numeros; i++) {
        printf("%d | ", pares[i]);
    }
    printf("\n");
    return 0;
}

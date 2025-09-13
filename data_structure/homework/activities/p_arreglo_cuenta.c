#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <numero_de_cuenta>\n", argv[0]);
        return 1;
    }
    
    int ultimo_digito = argv[1][strlen(argv[1])-1] - '0';
    int pares[10];
    
    for (int i = 0; i < 10; i++) pares[i] = (i+1)*2;
    
    printf("| ");
    for (int i = 9; i >= 0; i--) printf("%d | ", pares[i]);
    printf("\n");
    
    if (ultimo_digito >= 0 && ultimo_digito < 10) pares[ultimo_digito] = -1;
    
    printf("Indice | ");
    for (int i = 0; i < 10; i++) printf("%d | ", i);
    printf("\nValor  | ");
    for (int i = 0; i < 10; i++) printf("%d | ", pares[i]);
    printf("\n");
    
    return 0;
}

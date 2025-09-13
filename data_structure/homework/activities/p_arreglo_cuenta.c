#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int pares[10];
    
    for (int i = 0; i < 10; i++) 
        pares[i] = (i + 1) * 2;
    
    printf("| ");
    for (int i = 9; i >= 0; i--) 
        printf("%d | ", pares[i]);
    printf("\n");
    
    if (argc > 1) {
        char *cuenta = argv[1];
        int ultimo = cuenta[strlen(cuenta) - 1] - '0';
        
        for (int i = 0; i < 10; i++) {
            if (pares[i] == ultimo * 2) {
                pares[i] = -1;
                break;
            }
        }
    }
    
    printf("Indice | ");
    for (int i = 0; i < 10; i++) 
        printf("%d | ", i);
    printf("\n");
    
    printf("Valor  | ");
    for (int i = 0; i < 10; i++) 
        printf("%d | ", pares[i]);
    printf("\n");
    
    return 0;
}

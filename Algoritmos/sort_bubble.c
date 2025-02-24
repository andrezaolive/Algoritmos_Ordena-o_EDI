#include <stdio.h>

void bubble_sort(int lista[], int n) {
    int i, j, aux;
    
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (lista[j] > lista[j + 1]) {
                // Troca os elementos se estiverem fora de ordem
                aux = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = aux;
            }
        }
    }
}

// Função para imprimir a lista
void imprimir_lista(int lista[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", lista[i]);
    }
    printf("\n");
}

int main() {
    int numeros[] = {8, 4, 2, 7, 1, 5};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    printf("Lista antes da ordenação:\n");
    imprimir_lista(numeros, n);

    bubble_sort(numeros, n);

    printf("Lista após ordenação:\n");
    imprimir_lista(numeros, n);

    return 0;
}

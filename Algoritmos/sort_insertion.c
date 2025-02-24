#include <stdio.h>

void insertion_sort(int lista[], int n) {
    int i, j, aux;

    for (i = 1; i < n; i++) {
        aux = lista[i];
        j = i - 1;

        // Move os elementos da parte ordenada que são maiores que o auxiliar
        while (j >= 0 && lista[j] > aux) {
            lista[j + 1] = lista[j];  
            j--;
        }
        // Insere o elemento na posição correta
        lista[j + 1] = aux;  
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

    insertion_sort(numeros, n);

    printf("Lista após ordenação:\n");
    imprimir_lista(numeros, n);

    return 0;
}

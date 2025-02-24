#include <stdio.h>

// Função auxiliar para particionar a lista
int particionar(int lista[], int inicio, int fim) {
    int pivo = lista[fim];  // Escolhendo o último elemento como pivô
    int i = inicio - 1;      // Índice para elementos menores

    for (int j = inicio; j < fim; j++) {
        if (lista[j] < pivo) {
            i++;
            // Troca lista[i] e lista[j]
            int aux = lista[i];
            lista[i] = lista[j];
            lista[j] = aux;
        }
    }
    // Coloca o pivô na posição correta
    int aux = lista[i + 1];
    lista[i + 1] = lista[fim];
    lista[fim] = aux;

    return i + 1;  // Retorna o índice do pivô
}

// Função principal do Quick Sort (recursiva)
void quick_sort(int lista[], int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particionar(lista, inicio, fim);

        // Chamadas recursivas para ordenar as duas metades
        quick_sort(lista, inicio, pivo - 1);
        quick_sort(lista, pivo + 1, fim);
    }
}

// Função para imprimir a lista
void imprimir_lista(int lista[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", lista[i]);
    printf("\n");
}

int main() {
    int numeros[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    printf("Lista antes da ordenação:\n");
    imprimir_lista(numeros, n);

    quick_sort(numeros, 0, n - 1);

    printf("Lista após ordenação:\n");
    imprimir_lista(numeros, n);

    return 0;
}

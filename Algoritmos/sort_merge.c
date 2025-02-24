#include <stdio.h>

// Função para mesclar (merge) duas partes da lista
void mesclar(int lista[], int inicio, int meio, int fim) {
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    int esquerda[n1], direita[n2];

    // Copia os elementos para os vetores temporários
    for (int i = 0; i < n1; i++)
        esquerda[i] = lista[inicio + i];
    for (int j = 0; j < n2; j++)
        direita[j] = lista[meio + 1 + j];

    int i = 0, j = 0, k = inicio;

    // Mescla os vetores ordenadamente
    while (i < n1 && j < n2) {
        if (esquerda[i] <= direita[j]) {
            lista[k] = esquerda[i];
            i++;
        } else {
            lista[k] = direita[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes, se houver
    while (i < n1) {
        lista[k] = esquerda[i];
        i++;
        k++;
    }

    while (j < n2) {
        lista[k] = direita[j];
        j++;
        k++;
    }
}

// Função principal do Merge Sort (recursiva)
void merge_sort(int lista[], int inicio, int fim) {
    if (inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        merge_sort(lista, inicio, meio);
        merge_sort(lista, meio + 1, fim);
        mesclar(lista, inicio, meio, fim);
    }
}

// Função para imprimir a lista
void imprimir_lista(int lista[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", lista[i]);
    printf("\n");
}

int main() {
    int numeros[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    printf("Lista antes da ordenação:\n");
    imprimir_lista(numeros, n);

    merge_sort(numeros, 0, n - 1);

    printf("Lista após ordenação:\n");
    imprimir_lista(numeros, n);

    return 0;
}

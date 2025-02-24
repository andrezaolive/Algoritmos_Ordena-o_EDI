#include <stdio.h>

// Função para transformar a lista em um heap máximo
void heapify(int lista[], int n, int i) {
    int maior = i;  // Assume que a raiz é o maior elemento
    int esquerda = 2 * i + 1;  // Filho esquerdo
    int direita = 2 * i + 2;   // Filho direito
    int aux;

    // Se o filho esquerdo for maior que a raiz
    if (esquerda < n && lista[esquerda] > lista[maior]) {
        maior = esquerda;
    }
    // Se o filho direito for maior que o maior até agora
    if (direita < n && lista[direita] > lista[maior]) {
        maior = direita;
    }
    // Se o maior não for a raiz, troca e chama recursivamente
    if (maior != i) {
        aux = lista[i];
        lista[i] = lista[maior];
        lista[maior] = aux;

        // Recursivamente ajusta a subárvore afetada
        heapify(lista, n, maior);
    }
}

// Função principal do Heap Sort
void heap_sort(int lista[], int n) {
    int aux;

    // Constrói o heap máximo
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(lista, n, i);
    }
    // Extrai um por um do heap
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz (maior elemento) para o final
        aux = lista[0];
        lista[0] = lista[i];
        lista[i] = aux;

        // Reconstrói o heap
        heapify(lista, i, 0);
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

    heap_sort(numeros, n);

    printf("Lista após ordenação:\n");
    imprimir_lista(numeros, n);

    return 0;
}

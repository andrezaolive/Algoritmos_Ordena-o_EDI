#include <stdio.h>
#include <stdlib.h>

#define TAMANHO 10  // Definição do tamanho do vetor de contagem (0 a 9)

// Função auxiliar para encontrar o maior número da lista
int encontrar_maior(int lista[], int n) {
    int maior = lista[0];
    for (int i = 1; i < n; i++) {
        if (lista[i] > maior)
            maior = lista[i];
    }
    return maior;
}

// Função auxiliar que faz a ordenação por um dígito específico usando Counting Sort
void ordenar_por_digito(int lista[], int n, int exp) {
    int saida[n];  // Vetor temporário para armazenar a saída ordenada
    int contador[TAMANHO] = {0};

    // Contagem das ocorrências dos dígitos
    for (int i = 0; i < n; i++)
        contador[(lista[i] / exp) % 10]++;

    // Ajuste da contagem para determinar as posições corretas
    for (int i = 1; i < TAMANHO; i++)
        contador[i] += contador[i - 1];

    // Construção da lista ordenada
    for (int i = n - 1; i >= 0; i--) {
        saida[contador[(lista[i] / exp) % 10] - 1] = lista[i];
        contador[(lista[i] / exp) % 10]--;
    }

    // Copiando a lista ordenada para a original
    for (int i = 0; i < n; i++)
        lista[i] = saida[i];
}

// Função principal do Radix Sort
void radix_sort(int lista[], int n) {
    int maior = encontrar_maior(lista, n);

    // Aplica a ordenação para cada posição decimal (unidade, dezena, centena...)
    for (int exp = 1; maior / exp > 0; exp *= 10)
        ordenar_por_digito(lista, n, exp);
}

// Função para imprimir a lista
void imprimir_lista(int lista[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", lista[i]);
    printf("\n");
}

int main() {
    int numeros[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(numeros) / sizeof(numeros[0]);

    printf("Lista antes da ordenação:\n");
    imprimir_lista(numeros, n);

    radix_sort(numeros, n);

    printf("Lista após ordenação:\n");
    imprimir_lista(numeros, n);

    return 0;
}

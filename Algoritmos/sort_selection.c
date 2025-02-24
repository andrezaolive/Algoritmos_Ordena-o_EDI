#include <stdio.h>

int selection_sort(int lista[], int n) {
    int i, j, aux, menor_indice;

    for (i = 0; i < n - 1; i++) {
        menor_indice = i;
        // Encontra o menor elemento na parte não ordenada        
        for (j = i + 1; j < n; j++) {
            if (lista[j] < lista[menor_indice]) 
            menor_indice = j;    
        }
        // Troca os elementos
        aux = lista[i];
        lista[i] = lista[menor_indice];
        lista[menor_indice] = aux;
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
    
    selection_sort(numeros, n);

    printf("Lista após ordenação:\n");
    imprimir_lista(numeros, n);

    return 0;
}

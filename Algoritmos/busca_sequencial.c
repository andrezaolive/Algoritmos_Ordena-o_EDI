#include <stdio.h>

int busca_sequencial(int lista[], int n, int valor_procurado) {
    for (int i = 0; i < n; i++) {
        if (lista[i] == valor_procurado) {
            return i;  // Retorna o índice do elemento encontrado
        }
    }
    return -1;  // Retorna -1 se o elemento não for encontrado
}

// Programa principal
int main() {
    int numeros[] = {10, 20, 30, 40, 50};
    int n = sizeof(numeros) / sizeof(numeros[0]);
    int valor = 30;

    int resultado = busca_sequencial(numeros, n, valor);

    if (resultado != -1)
        printf("Valor %d encontrado na posição %d\n", valor, resultado);
    else
        printf("Valor %d não encontrado na lista\n", valor);

    return 0;
}

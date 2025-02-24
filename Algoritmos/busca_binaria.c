#include <stdio.h>

int busca_binaria(int lista[], int n, int valor_procurado) {
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (lista[meio] == valor_procurado) 
            return meio;  // Elemento encontrado

        if (lista[meio] < valor_procurado) 
            inicio = meio + 1;  // Busca na metade direita
        else 
            fim = meio - 1;  // Busca na metade esquerda
    }

    return -1;  // Elemento não encontrado
}

// Programa principal
int main() {
    int numeros[] = {10, 20, 30, 40, 50};
    int n = sizeof(numeros) / sizeof(numeros[0]);
    int valor = 30;

    int resultado = busca_binaria(numeros, n, valor);

    if (resultado != -1)
        printf("Valor %d encontrado na posição %d\n", valor, resultado);
    else
        printf("Valor %d não encontrado na lista\n", valor);

    return 0;
}

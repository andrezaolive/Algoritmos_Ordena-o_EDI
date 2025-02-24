#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_100 100
#define MAX_1000 1000
#define MAX_10000 10000
#define MAX_100000 100000

// Função para gerar números aleatórios e salvar em arquivos
void gerar_numeros(const char *nome, int quantidade) {
    FILE *arquivo = fopen(nome, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s\n", nome);
        return;
    }

    srand(time(NULL)); // Semente para gerar números aleatórios
    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d\n", rand() % 1000000); // Números entre 0 e 999999
    }

    fclose(arquivo);
}

// Função para carregar os números de um arquivo para um vetor
int carregar_numeros(const char *nome_arquivo, int *vetor, int tamanho) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nome_arquivo);
        return 0;
    }

    int i = 0;
    while (i < tamanho && fscanf(arquivo, "%d", &vetor[i]) != EOF) {
        i++;
    }

    fclose(arquivo);
    return i;
}

// Função para salvar os números ordenados em um novo arquivo
void salvar_ordenado(const char *nome_arquivo, int *vetor, int tamanho) {
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo %s\n", nome_arquivo);
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        fprintf(arquivo, "%d\n", vetor[i]);
    }

    fclose(arquivo);
}

// Algoritmo Selection Sort
void selection_sort(int *vetor, int n, int *comparacoes, int *trocas) {
    int i, j, menor, aux;
    for (i = 0; i < n - 1; i++) {
        menor = i;
        for (j = i + 1; j < n; j++) {
            (*comparacoes)++; 
            if (vetor[j] < vetor[menor]) {
                menor = j;
            }
        }
        if (menor != i) { 
            (*trocas)++;
            aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux;
        }
    }
}

// Algoritmo Insertion Sort
void insertion_sort(int *vetor, int n, int *comparacoes, int *trocas) {
    int i, j, chave;
    for (i = 1; i < n; i++) {
        chave = vetor[i];
        j = i - 1;
        while (j >= 0 && vetor[j] > chave) {
            (*comparacoes)++;
            vetor[j + 1] = vetor[j];
            j--;
        }
        if (chave != i) {
            (*trocas)++;
            vetor[j + 1] = chave;
        }
    }
}

// Algoritmo Bubble Sort
void bubble_sort(int *vetor, int n, int *comparacoes, int *trocas) {
    int i, j, aux;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparacoes)++;
            if (vetor[j] > vetor[j + 1]) {
                (*trocas)++;
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

// Algoritmo Heap Sort
void heapify(int *vetor, int n, int i, int *comparacoes, int *trocas) {
    int maior = i;  // Assume que a raiz é o maior elemento
    int esquerda = 2 * i + 1;  // Filho esquerdo
    int direita = 2 * i + 2;   // Filho direito
    int aux;

    // Se o filho esquerdo for maior que a raiz
    if (esquerda < n && vetor[esquerda] > vetor[maior]) {
        (*comparacoes)++;
        maior = esquerda;
    }
    // Se o filho direito for maior que o maior até agora
    if (direita < n && vetor[direita] > vetor[maior]) {
        (*comparacoes)++;
        maior = direita;
    }
    // Se o maior não for a raiz, troca e chama recursivamente
    if (maior != i) {
        aux = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = aux;
        (*trocas)++;

        // Recursivamente ajusta a subárvore afetada
        heapify(vetor, n, maior, comparacoes, trocas);
    }
}

// Função principal do Heap Sort
void heap_sort(int *vetor, int n, int *comparacoes, int *trocas) {
    int aux;

    // Constrói o heap máximo
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(vetor, n, i, comparacoes, trocas);

    // Extrai um por um do heap
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz (maior elemento) para o final
        aux = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = aux;
        (*trocas)++;

        // Reconstrói o heap
        heapify(vetor, i, 0, comparacoes, trocas);
    }
}

// Algoritmo Merge Sort
void merge(int *vetor, int inicio, int meio, int fim, int *comparacoes, int *trocas) {
    int i, j, k, n1 = meio - inicio + 1, n2 = fim - meio;
    int esquerda[n1], direita[n2];

    for (i = 0; i < n1; i++) esquerda[i] = vetor[inicio + i];
    for (j = 0; j < n2; j++) direita[j] = vetor[meio + 1 + j];

    i = j = 0;
    k = inicio;
    while (i < n1 && j < n2) {
        (*comparacoes)++;
        if (esquerda[i] <= direita[j]) {
            vetor[k++] = esquerda[i++];
        } else {
            vetor[k++] = direita[j++];
            (*trocas)++;
        }
    }

    while (i < n1) vetor[k++] = esquerda[i++];
    while (j < n2) vetor[k++] = direita[j++];
}
// Função principal Merge Sort
void merge_sort(int *vetor, int inicio, int fim, int *comparacoes, int *trocas) {
    if (inicio < fim) {

        int meio = inicio + (fim - inicio) / 2;
        merge_sort(vetor, inicio, meio, comparacoes, trocas);
        merge_sort(vetor, meio + 1, fim, comparacoes, trocas);
        merge(vetor, inicio, meio, fim, comparacoes, trocas);
    }
}

// Algoritmo Quick Sort
void quick_sort(int *vetor, int inicio, int fim, int *comparacoes, int *trocas) {
    if (inicio < fim) {
        int pivo = vetor[fim], i = inicio - 1, aux;
        for (int j = inicio; j < fim; j++) {
            (*comparacoes)++;
            if (vetor[j] < pivo) {
                (*trocas)++;
                i++;
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
            }
        }
        (*trocas)++;
        aux = vetor[i + 1];
        vetor[i + 1] = vetor[fim];
        vetor[fim] = aux;

        int p = i + 1;
        quick_sort(vetor, inicio, p - 1, comparacoes, trocas);
        quick_sort(vetor, p + 1, fim, comparacoes, trocas);
    }
}

// Algoritmo Radix Sort
int encontrar_maior(int *vetor, int n, int *comparacoes, int *trocas) {
    int maior = vetor[0];
    for (int i = 1; i < n; i++) {
        (*comparacoes)++;
        if (vetor[i] > maior)
            maior = vetor[i];
    }
    return maior;
}

// Função de ordenação por um dígito específico usando Counting Sort
void ordenar_por_digito(int *vetor, int n, int exp, int *comparacoes, int *trocas) {
    int saida[n];  // Vetor temporário para armazenar a saída ordenada
    int contador[10] = {0};

    // Contagem das ocorrências dos dígitos
    for (int i = 0; i < n; i++)
        contador[(vetor[i] / exp) % 10]++;

    // Ajuste da contagem para determinar as posições corretas
    for (int i = 1; i < 10; i++)
        contador[i] += contador[i - 1];

    // Construção da vetor ordenada
    for (int i = n - 1; i >= 0; i--) {
        saida[contador[(vetor[i] / exp) % 10] - 1] = vetor[i];
        contador[(vetor[i] / exp) % 10]--;
    }

    // Copiando a vetor ordenada para a original
    for (int i = 0; i < n; i++)
        vetor[i] = saida[i];
}

// Função principal do Radix Sort
void radix_sort(int *vetor, int n, int *comparacoes, int *trocas) {
    int maior = encontrar_maior(vetor, n, comparacoes, trocas);

    // Aplica a ordenação para cada posição decimal (unidade, dezena, centena...)
    for (int exp = 1; maior / exp > 0; exp *= 10) {
        (*comparacoes)++;
        ordenar_por_digito(vetor, n, exp, comparacoes, trocas);
    }
}

// Algoritmo Busca Binária
int busca_binaria(int *vetor, int n, int valor_procurado) {
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;

        if (vetor[meio] == valor_procurado) 
            return meio;  // Elemento encontrado

        if (vetor[meio] < valor_procurado) 
            inicio = meio + 1;  // Busca na metade direita
        else 
            fim = meio - 1;  // Busca na metade esquerda
    }

    return -1;  // Elemento não encontrado
}

// Algoritmo Busca Sequencial
int busca_sequencial(int *vetor, int n, int valor_procurado) {
    for (int i = 0; i < n; i++) {
        if (vetor[i] == valor_procurado) {
            return i;  // Retorna o índice do elemento encontrado
        }
    }
    return -1;  // Retorna -1 se o elemento não for encontrado
}

// Função principal
int main() {
    int opcao, tamanho, trocas, comparacoes, elemento;
    double tempo;
    char nome_arquivo[100];
    int vetor[MAX_100000];
    int tamanhos[] = {MAX_100, MAX_1000, MAX_10000, MAX_100000};
    const char *arquivos[] = {"seq_100.txt", "seq_1000.txt", "seq_10000.txt", "seq_100000.txt"};
    char *saida[] = {"ordenado_100.txt", "ordenado_1000.txt", "ordenado_10000.txt", "ordenado_100000.txt"};
    
    printf("\n-- MENU PARA ORDENAR --\n");
    printf("1 - Criar arquivo.\n 2 - Ordenar arquivo.\n 3- Buscar elemento.\n 4- Sair.\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    if(opcao == 1) {
        printf("-- Gerar arquivo --\n");
        printf("Escolha o tamanho do arquivo:\n 1 - 100 numeros.\n 2 - 1000 numeros.\n 3 - 10000 numeros.\n 4 - 100000 numeros.\n");
        printf("Opção: ");
        scanf("%d", &tamanho);

        if(tamanho == 1){
            gerar_numeros("seq_100.txt", MAX_100);
        } else if(tamanho == 2) {
            gerar_numeros("seq_1000.txt", MAX_1000);
        } else if(tamanho == 3) {
            gerar_numeros("seq_10000.txt", MAX_10000);
        } else{
            gerar_numeros("seq_100000.txt", MAX_100000);
        }
        printf("Arquivo gerado com sucesso!\n");
        main();
    
    } else if(opcao == 2) {
        printf("Digite o nome do arquivo: ");
        scanf("%s", nome_arquivo);

        for (int i = 0; i < 4; i++) {
            if (strcmp(nome_arquivo, arquivos[i]) == 0) {
                tamanho = tamanhos[i];
                break;
            }
        }

        if (tamanho == 0) {
            printf("Arquivo invalido!\n");
            return 1;
        }

        carregar_numeros(nome_arquivo, vetor, tamanho);

        clock_t inicio, fim;

        printf("\nOrdenando %s com Selection Sort...\n", nome_arquivo);
        inicio = clock();
        selection_sort(vetor, tamanho, &comparacoes, &trocas);
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        salvar_ordenado("selection_sort.txt", vetor, tamanho);
        printf("Comparações: %d comparacoes\n", comparacoes);
        printf("Trocas: %d trocas\n", trocas);
        printf("Tempo: %.6f segundos\n", tempo);

        printf("\nOrdenando %s com Insertion Sort...\n", nome_arquivo);
        inicio = clock();
        insertion_sort(vetor, tamanho, &comparacoes, &trocas);
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        salvar_ordenado("insertion_sort.txt", vetor, tamanho);
        printf("Comparações: %d comparacoes\n", comparacoes);
        printf("Trocas: %d trocas\n", trocas);
        printf("Tempo: %.6f segundos\n", tempo);

        printf("\nOrdenando %s com Bubble Sort...\n", nome_arquivo);
        inicio = clock();
        bubble_sort(vetor, tamanho, &comparacoes, &trocas);
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        salvar_ordenado("bubble_sort.txt", vetor, tamanho);
        printf("Comparações: %d comparacoes\n", comparacoes);
        printf("Trocas: %d trocas\n", trocas);
        printf("Tempo: %.6f segundos\n", tempo);

        printf("\nOrdenando %s com Merge Sort...\n", nome_arquivo);
        inicio = clock();
        merge_sort(vetor, 0, tamanho - 1, &comparacoes, &trocas);
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        salvar_ordenado("merge_sort.txt", vetor, tamanho);
        printf("Comparações: %d comparacoes\n", comparacoes);
        printf("Trocas: %d trocas\n", trocas);
        printf("Tempo: %.6f segundos\n", tempo);

        printf("\nOrdenando %s com Quick Sort...\n", nome_arquivo);
        inicio = clock();
        quick_sort(vetor, 0, tamanho - 1, &comparacoes, &trocas);
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        salvar_ordenado("quick_sort.txt", vetor, tamanho);
        printf("Comparações: %d comparacoes\n", comparacoes);
        printf("Trocas: %d trocas\n", trocas);
        printf("Tempo: %.6f segundos\n", tempo);

        printf("\nOrdenando %s com Radix Sort...\n", nome_arquivo);
        inicio = clock();
        radix_sort(vetor, tamanho, &comparacoes, &trocas);
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        salvar_ordenado("radix_sort.txt", vetor, tamanho);
        printf("Comparações: %d comparacoes\n", comparacoes);
        printf("Trocas: %d trocas\n", trocas);
        printf("Tempo: %.6f segundos\n", tempo);
        
        printf("\nOrdenando %s com Heap Sort...\n", nome_arquivo);
        inicio = clock();
        heap_sort(vetor, tamanho, &comparacoes, &trocas);
        fim = clock();
        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        salvar_ordenado("heap_sort.txt", vetor, tamanho);
        printf("Comparações: %d \n", comparacoes);
        printf("Trocas: %d trocas\n", trocas);
        printf("Tempo: %.6f segundos\n", tempo);

        main();

    } else if (opcao == 3) {
        printf("Buscar elemento.\n Digite o nome do arquivo onde deseja buscar: ");
        scanf("%s", nome_arquivo);
        printf("Digite o número a ser buscado: ");
        scanf("%d", &elemento);

        int encontrado = -1;
        
        // Verifica se o arquivo é ordenado ou não
        for (int i = 0; i < 4; i++) {
            if (strcmp(nome_arquivo, arquivos[i]) == 0) {
                tamanho = carregar_numeros(arquivos[i], vetor, tamanhos[i]);
                encontrado = busca_sequencial(vetor, tamanho, elemento);
                printf("Busca Sequencial: Elemento %d %s encontrado.\n", elemento, (encontrado != -1) ? "foi" : "NÃO foi");
                break;
            } else {
                tamanho = carregar_numeros(nome_arquivo, vetor, tamanhos[i]);
                encontrado = busca_binaria(vetor, tamanho, elemento);
                printf("Busca Binária: Elemento %d %s encontrado.\n", elemento, (encontrado != -1) ? "foi" : "NÃO foi");
                break;
            }
        }
        if (encontrado == -1) {
            printf("Arquivo não encontrado.\n");
        }
        main();

    } else if (opcao == 4) {
        printf("Programa encerrado.\n");
        return 0;
    } else {
        printf("Opcao invalida! Tente novamente.\n");
        main();
    }
    return 0;
}

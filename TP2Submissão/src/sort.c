#include "../include/sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/graph.h"

typedef struct s_verticecor {
    int indice;
    int cor;
} VerticeCor;

typedef struct s_vertice {
    int valor;
    struct s_vertice* prox;
    int cor; 
} Vertice;

typedef struct s_grafo {
    int num_vertices;
    int num_arestas;
    Vertice** lista_adjacencia;  
} Grafo;

void TrocaVerticeCor(VerticeCor* a, VerticeCor* b) {
    VerticeCor temp = *a;
    *a = *b;
    *b = temp;
}


int Partition(VerticeCor* array, int low, int high) {
    // Escolhendo o elemento do meio como pivô.
    int middle = low + (high - low) / 2;
    VerticeCor pivot = array[middle];

    // Coloca o pivô temporariamente no final para facilitar o loop de partição.
    TrocaVerticeCor(&array[middle], &array[high]);

    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (array[j].cor < pivot.cor || (array[j].cor == pivot.cor && array[j].indice < pivot.indice) ) {
            i++;
            TrocaVerticeCor(&array[i], &array[j]);
        }
    }
    // Coloca o pivô na posição correta.
    TrocaVerticeCor(&array[i + 1], &array[high]);
    return (i + 1);
}

void QSort(VerticeCor* array, int low, int high) {
    if (low < high) {
        int pi = Partition(array, low, high);

        QSort(array, low, pi - 1);
        QSort(array, pi + 1, high);
    }
}

VerticeCor* QuickSort(Grafo* g) {
    // Aloca o vetor de VerticeCor
    VerticeCor* vertices = (VerticeCor*)malloc(g->num_vertices * sizeof(VerticeCor));
    if (vertices == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return NULL;
    }

    // Preenche o vetor com os índices e cores dos vértices
    for (int i = 0; i < g->num_vertices; i++) {
        vertices[i].indice = i;
        vertices[i].cor = g->lista_adjacencia[i]->cor;
    }

    // Executa o QuickSort no vetor de vertices
    QSort(vertices, 0, g->num_vertices - 1);

    // Retorna o vetor ordenado
    return vertices;
}


void Merge(VerticeCor* array, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Cria arrays temporários
    VerticeCor* L = (VerticeCor*)malloc(n1 * sizeof(VerticeCor));
    VerticeCor* R = (VerticeCor*)malloc(n2 * sizeof(VerticeCor));

    // Copia os dados para os arrays temporários L[] e R[]
    for (int i = 0; i < n1; i++)
        L[i] = array[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = array[middle + 1 + j];

    // Intercala os arrays temporários de volta em array[left..right]
    int i = 0;    // Índice inicial do primeiro subarray
    int j = 0;    // Índice inicial do segundo subarray
    int k = left; // Índice inicial do subarray mergeado

    while (i < n1 && j < n2) {
        if (L[i].cor <= R[j].cor) {
            array[k] = L[i];
            i++;
        } else {
            array[k] = R[j];
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver algum
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver algum
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }

    // Libera os arrays temporários
    free(L);
    free(R);
}

void MSort(VerticeCor* array, int left, int right) {
    if (left < right) {
        // Encontra o ponto médio para dividir o array em dois
        int middle = left + (right - left) / 2;

        // Chamada recursiva para a primeira e segunda metade
        MSort(array, left, middle);
        MSort(array, middle + 1, right);

        // Combina as duas metades ordenadas
        Merge(array, left, middle, right);
    }
}

VerticeCor* MergeSort(Grafo* g) {
    // Aloca memória para o array de VerticeCor
    VerticeCor* vertices = (VerticeCor*)malloc(g->num_vertices * sizeof(VerticeCor));
    
    // Preenche o array com os vértices e suas cores
    for (int i = 0; i < g->num_vertices; i++) {
        vertices[i].indice = i; // Supomos que o índice do vértice corresponde à sua posição na lista de adjacências
        vertices[i].cor = g->lista_adjacencia[i]->cor;
    }
    
    // Ordena os vértices usando MergeSort
    MSort(vertices, 0, g->num_vertices - 1);
    
    return vertices;
}

void heapify(VerticeCor* array, int n, int i) {
    int largest = i; // Inicializa o maior como raiz
    int l = 2 * i + 1; // esquerda = 2*i + 1
    int r = 2 * i + 2; // direita = 2*i + 2

    // Se o filho esquerdo é maior que a raiz
    if (l < n && (array[l].cor > array[largest].cor || 
        (array[l].cor == array[largest].cor && array[l].indice > array[largest].indice))) {
        largest = l;
    }

    // Se o filho direito é maior que o maior até agora
    if (r < n && (array[r].cor > array[largest].cor || 
        (array[r].cor == array[largest].cor && array[r].indice > array[largest].indice))) {
        largest = r;
    }

    // Se o maior não é raiz
    if (largest != i) {
        TrocaVerticeCor(&array[i], &array[largest]);

        // Heapify recursivamente o sub-heap afetado
        heapify(array, n, largest);
    }
}

// Função principal para fazer o heap sort
void HSort(VerticeCor* array, int n) {
    // Construir heap (reorganizar o array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);

    // Extrair um por um elemento do heap
    for (int i = n - 1; i > 0; i--) {
        // Mover a raiz atual para o fim
        TrocaVerticeCor(&array[0], &array[i]);

        // chamar o heapify na heap reduzida
        heapify(array, i, 0);
    }
}

// Função para ordenar os vértices pelo método de HeapSort
VerticeCor* HeapSort(Grafo* g) {
    // Aloca memória para o array de VerticeCor
    VerticeCor* vertices = (VerticeCor*)malloc(g->num_vertices * sizeof(VerticeCor));

    // Preenche o array com os vértices e suas cores
    for (int i = 0; i < g->num_vertices; i++) {
        vertices[i].indice = i; // Supõe-se que o índice do vértice corresponde à sua posição na lista de adjacências
        vertices[i].cor = g->lista_adjacencia[i]->cor;
    }

    // Ordena os vértices usando HeapSort
    HSort(vertices, g->num_vertices);

    return vertices;
}

VerticeCor* BubbleSort(Grafo* g) {
    // Cria um array para armazenar índice e cor de cada vértice
    VerticeCor* vertices = (VerticeCor*)malloc(g->num_vertices * sizeof(VerticeCor));
    if (vertices == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    // Preenche o array com os índices e cores dos vértices
    for (int i = 0; i < g->num_vertices; i++) {
        vertices[i].indice = i;
        vertices[i].cor = g->lista_adjacencia[i]->cor;
    }

    // Ordena os vértices por cor usando Bubble Sort
    int houve_troca;
    do {
        houve_troca = 0;
        for (int i = 0; i < g->num_vertices - 1; i++) {
            if (vertices[i].cor > vertices[i + 1].cor) {
                // Troca os elementos de posição
                TrocaVerticeCor(&vertices[i], &vertices[i + 1]);
                houve_troca = 1;
            }
        }
    } while (houve_troca);

    // Retorna o array ordenado
    return vertices;
}

VerticeCor* InsertionSort(Grafo* g) {
    // Aloca o vetor de VerticeCor
    VerticeCor* vertices = (VerticeCor*)malloc(g->num_vertices * sizeof(VerticeCor));
    if (vertices == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return NULL;
    }

    // Preenche o vetor com os índices e cores dos vértices
    for (int i = 0; i < g->num_vertices; i++) {
        vertices[i].indice = i;
        vertices[i].cor = g->lista_adjacencia[i]->cor;
    }

    // Insertion Sort
    for (int i = 1; i < g->num_vertices; i++) {
        VerticeCor chave = vertices[i];
        int j = i - 1;

        // Move os elementos que são maiores que a chave
        while (j >= 0 && vertices[j].cor > chave.cor) {
            vertices[j + 1] = vertices[j];
            j--;
        }
        vertices[j + 1] = chave;
    }

    // Retorna o vetor ordenado
    return vertices;
}

VerticeCor* SelectionSort(Grafo* g) {
    // Aloca o vetor de VerticeCor
    VerticeCor* vertices = (VerticeCor*)malloc(g->num_vertices * sizeof(VerticeCor));
    if (vertices == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return NULL;
    }

    // Preenche o vetor com os índices e cores dos vértices
    for (int i = 0; i < g->num_vertices; i++) {
        vertices[i].indice = i;
        vertices[i].cor = g->lista_adjacencia[i]->cor;
    }

    // Selection Sort
    for (int i = 0; i < g->num_vertices - 1; i++) {
        // Encontra o mínimo elemento no vetor não ordenado
        int min_idx = i;
        for (int j = i + 1; j < g->num_vertices; j++) {
            if (vertices[j].cor < vertices[min_idx].cor || (vertices[j].cor == vertices[min_idx].cor && vertices[j].indice < vertices[min_idx].indice)) {
                min_idx = j;
            }
        }

        // Troca o elemento mínimo encontrado com o primeiro elemento
        TrocaVerticeCor(&vertices[min_idx], &vertices[i]);
    }

    // Retorna o vetor ordenado
    return vertices;
}

VerticeCor* BubbleSort_variation(Grafo* g){
    // Cria um array para armazenar índice e cor de cada vértice
    VerticeCor* vertices = (VerticeCor*)malloc(g->num_vertices * sizeof(VerticeCor));
    if (vertices == NULL) {
        printf("Erro ao alocar memória.\n");
        return NULL;
    }

    // Preenche o array com os índices e cores dos vértices
    for (int i = 0; i < g->num_vertices; i++) {
        vertices[i].indice = i;
        vertices[i].cor = g->lista_adjacencia[i]->cor;
    }

    int houve_troca;
    do {
        houve_troca = 0;
        for (int i = 1; i < g->num_vertices - 1; i+=2) //bubbleSort para os indices impares
        {
            if (vertices[i].cor > vertices[i + 1].cor) {
                // Troca os elementos de posição
                TrocaVerticeCor(&vertices[i], &vertices[i + 1]);
                houve_troca = 1;
            }
        }
        for (int i = 0; i < g->num_vertices - 1; i+=2) //bubbleSort para os indices pares
        {
            if (vertices[i].cor > vertices[i + 1].cor) {
                // Troca os elementos de posição
                TrocaVerticeCor(&vertices[i], &vertices[i + 1]);
                houve_troca = 1;
            }
        }
    } while (houve_troca);

    return  vertices;
}

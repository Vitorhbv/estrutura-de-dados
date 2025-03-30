#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/graph.h"
#include "../include/sort.h"


int main() {
    
    char opcao = getchar();

    int numVertices;
    scanf("%d", &numVertices);

    Grafo* g = NovoGrafo();
    
    for (int i = 0; i < numVertices; i++) {
        InsereVertice(g); // Insere o vértice no grafo
    }

    for (int i = 0; i < numVertices; i++) {
        int numVizinhos;
        scanf("%d", &numVizinhos);
        if (numVizinhos != 0){
            int* vizinhos = (int*)malloc(numVizinhos * sizeof(int));
            for (int j = 0; j < numVizinhos; j++) {
                scanf("%d", &vizinhos[j]);
            }

            for (int j = 0; j < numVizinhos; j++) {
                InsereAresta(g, i, vizinhos[j]);
            }

            free(vizinhos); // Libera a memória alocada para vizinhos após o uso
        }
    }

    int cores[numVertices];

    for (int i = 0; i < numVertices; i++){
        scanf("%d", &cores[i]);
    }

    InsereCores(g,cores);
    
    if (opcao == 'b') {
        if (VerificaColoracaoGulosa(g)== true){
            VerticeCor* VerticesOrdenados =  BubbleSort(g);
            ImprimeVertices(VerticesOrdenados,numVertices);
            free(VerticesOrdenados);
        }
        else{
            printf("0");
        }
    } else if (opcao == 's') {
        if (VerificaColoracaoGulosa(g)== true){
            VerticeCor* VerticesOrdenados =  SelectionSort(g);
            ImprimeVertices(VerticesOrdenados,numVertices);
            free(VerticesOrdenados);
        }
        else{
            printf("0");
        }
    } else if (opcao == 'i') {
        if (VerificaColoracaoGulosa(g)== true){
            VerticeCor* VerticesOrdenados =  InsertionSort(g);
            ImprimeVertices(VerticesOrdenados,numVertices);
            free(VerticesOrdenados);
        }
        else{
            printf("0");
        }
    } else if (opcao == 'q') {
        if (VerificaColoracaoGulosa(g)== true){
            VerticeCor* VerticesOrdenados =  QuickSort(g);
            ImprimeVertices(VerticesOrdenados,numVertices);
            free(VerticesOrdenados);
        }
        else{
            printf("0");
        }
    } else if (opcao == 'm') {
        if (VerificaColoracaoGulosa(g)== true){
            VerticeCor* VerticesOrdenados =  MergeSort(g);
            ImprimeVertices(VerticesOrdenados,numVertices);
            free(VerticesOrdenados);
        }
        else{
            printf("0");
        }
    } else if (opcao == 'p') {
        if (VerificaColoracaoGulosa(g)== true){
            VerticeCor* VerticesOrdenados =  HeapSort(g);
            ImprimeVertices(VerticesOrdenados,numVertices);
            free(VerticesOrdenados);
        }
        else{
            printf("0");
        }
    } else if (opcao == 'y') {
        if (VerificaColoracaoGulosa(g)== true){
            VerticeCor* VerticesOrdenados =  BubbleSort_variation(g);
            ImprimeVertices(VerticesOrdenados,numVertices);
            free(VerticesOrdenados);
        }
        else{
            printf("0");
        }
    }

    DeletaGrafo(g);

    return 0;
}

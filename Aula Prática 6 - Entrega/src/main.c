#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/graph.h"

int main(int argc, char* argv[]) {
    if (argc != 1) {
        printf("Uso: %s\n", argv[0]);
        return 1;
    }

    int numVertices;
    printf("Digite o número de vértices: ");
    scanf("%d", &numVertices);

    Grafo* g = NovoGrafo();

    for (int i = 0; i < numVertices; i++) {
        int numVizinhos;
        printf("Digite o número de vizinhos para o vértice %d: ", i);
        scanf("%d", &numVizinhos);

        int* vizinhos = (int*)malloc(numVizinhos * sizeof(int));
        printf("Digite os vizinhos para o vértice %d: ", i);
        for (int j = 0; j < numVizinhos; j++) {
            scanf("%d", &vizinhos[j]);
        }

        InsereAresta(g, numVizinhos, vizinhos);
        free(vizinhos);
    }

    char opcao[3]; // Opção agora é uma string com até 2 caracteres
    printf("Digite a opção (-d, -n, -k): ");
    scanf("%s", opcao);

    if (strcmp(opcao, "-d") == 0) {
        printf("%d\n", QuantidadeVertices(g));
        printf("%d\n", QuantidadeArestas(g));
        printf("%d\n", GrauMinimo(g));
        printf("%d\n", GrauMaximo(g));
    } else if (strcmp(opcao, "-n") == 0) {
        for (int i = 0; i < QuantidadeVertices(g); i++) {
            printf("%d: ", i);
            ImprimeVizinhos(g, i);
        }
    } else if (strcmp(opcao, "-k") == 0) {
        printf("%s\n", EhGrafoCompleto(g) ? "1" : "0");
    } else {
        printf("Opção inválida\n");
    }

    DeletaGrafo(g);

    return 0;
}

#include "../include/graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

Grafo* NovoGrafo() {
    Grafo* g = (Grafo*)malloc(sizeof(Grafo));
    g->num_vertices = 0;
    g->num_arestas = 0;
    g->lista_adjacencia = (Vertice**)malloc(sizeof(Vertice*) * MAX_NUM_VERTICES);
    for (int i = 0; i < MAX_NUM_VERTICES; i++) {
        g->lista_adjacencia[i] = NULL;
    }
    return g;
}

void DeletaGrafo(Grafo* g) {
    if (g) {
        for (int i = 0; i < g->num_vertices; i++) {
            Vertice* atual = g->lista_adjacencia[i];
            while (atual) {
                Vertice* proximo = atual->prox;
                free(atual);
                atual = proximo;
            }
        }
        free(g->lista_adjacencia);
        free(g);
    }
}

void InsereVertice(Grafo* g) {
    int tamanho = g->num_vertices + 1;
    g->lista_adjacencia = (Vertice**)realloc(g->lista_adjacencia, tamanho * sizeof(Vertice*));
    g->lista_adjacencia[g->num_vertices] = NULL;
    g->num_vertices++;
}

void InsereAresta(Grafo* g, int v, int w) {
    if (v >= 0 && v < g->num_vertices && w >= 0 && w < g->num_vertices) {
        Vertice* novo = (Vertice*)malloc(sizeof(Vertice));
        novo->valor = w;
        novo->prox = g->lista_adjacencia[v];
        g->lista_adjacencia[v] = novo;
        g->num_arestas++;
    }
    else {
        printf("Erro: vértice inválido\n");
    }
}

void InsereCores(Grafo* g, int* cores) {
    if (g == NULL || cores == NULL) {
        printf("Grafo ou vetor de cores não inicializado.\n");
        return;
    }

    for (int i = 0; i < g->num_vertices; i++) {
        // Se o vértice tem uma lista de adjacência (não é NULL), insere a cor.
        if (g->lista_adjacencia[i] != NULL) {
            g->lista_adjacencia[i]->cor = cores[i];
        } else {
            // Se o vértice não tem vizinhos, ainda precisa receber a cor.
            g->lista_adjacencia[i] = (Vertice*)malloc(sizeof(Vertice));
            g->lista_adjacencia[i]->cor = cores[i];
            g->lista_adjacencia[i]->prox = NULL;
        }
    }
}

bool VerificaColoracaoGulosa(Grafo* g) {

    for (int v = 0; v < g->num_vertices; v++) {
        
        Vertice* atual = g->lista_adjacencia[v];
        int cor_vertice = g->lista_adjacencia[v]->cor;
        
        if (cor_vertice >1 && atual != NULL) {

            int* vizinhos_cores = (int*)malloc(g->num_vertices * sizeof(int));
            int contador = 0;

            while (atual != NULL) {
                int cor_vizinho = g->lista_adjacencia[atual->valor]->cor;
                vizinhos_cores[contador] = cor_vizinho;
                contador++;
                atual = atual->prox;
            }

            for (int j = 1; j <= cor_vertice - 1; j++) {
                bool cor_encontrada = false;
                for (int k = 0; k < contador; k++) {
                    if (j == vizinhos_cores[k]) {
                        cor_encontrada = true;
                        break;
                    }
                }
                if (!cor_encontrada) {
                    //printf("A coloração não é gulosa.\n");
                    free(vizinhos_cores);
                    return false;
                }
            }

           free(vizinhos_cores);
        }

    }
    
    //printf("Coloração é gulosa.\n");
    return true;
}

void ImprimeVertices(VerticeCor* verticesOrdenados, int num_vertices) {
    if (verticesOrdenados != NULL) {
        printf("1 ");
        for (int i = 0; i < num_vertices; i++) {
            printf("%d ", verticesOrdenados[i].indice);
        }
        printf("\n");
    } else {
        printf("Erro: Array de vertices ordenados é nulo.\n");
    }
}


#include "../include/graph.h"

typedef struct s_vertice {
    int valor;
    struct s_vertice* prox; 
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

int QuantidadeVertices(Grafo* g) {
    return g->num_vertices;
}

int QuantidadeArestas(Grafo* g) {
    return g->num_arestas;
}

int GrauMinimo(Grafo* g){
    int min = g->num_vertices > 0 ? g->num_vertices - 1 : 0; // max vizinhos
    for (int i = 0; i < g->num_vertices; i++) {
        int grau = 0;
        Vertice* atual = g->lista_adjacencia[i];
        while (atual) {
            grau++;
            atual = atual->prox;
        }
        if (grau < min) {
            min = grau;
        }
    }
    return min;
}

int GrauMaximo(Grafo* g) {
    int max = 0; // min vizinhos
    for (int i = 0; i < g->num_vertices; i++) {
        int grau = 0;
        Vertice* atual = g->lista_adjacencia[i];
        while (atual) {
            grau++;
            atual = atual->prox;
        }
        if (grau > max) {
            max = grau;
        }
    }
    return max;
}

void ImprimeVizinhos(Grafo* g, int v) {
    if (v >= 0 && v < g->num_vertices) {
        Vertice* atual = g->lista_adjacencia[v];
        while (atual) {
            printf("%d ", atual->valor);
            atual = atual->prox;
        }
        printf("\n");
    }
    else {
        printf("Erro: vertice invalido\n");
    }
}

    int EhGrafoCompleto(Grafo* g) {
    int completo = 1;
    for (int i = 0; i < g->num_vertices; i++) {
        Vertice* atual = g->lista_adjacencia[i];
        int grau = 0;
        while (atual) {
            grau++;
            atual = atual->prox;
        }
        if (grau != g->num_vertices - 1) {
            completo = 0;
            break;
        }
    }
    return completo;
} 

/*int EhGrafoCompleto(Grafo* g) {
    int completo;
    if (g->num_arestas == g->num_vertices * (g->num_vertices - 1) / 2) {
        completo = 1;
    }
    else {
        completo = 0;
    }
    return completo;
}*/

#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

#define MAX_NUM_VERTICES 1000

/*  Você pode inserir os includes necessários para que sua classe funcione.
 * Nenhuma outra alteração neste arquivo é permitida
 */


/*  Você deve implementar struct s_grafo como um TAD que irá armazenar
 * os dados de um grafo. Lembrando que a estratégia utilizada deve ser uma
 * lista de adjacencia e deve ser implementada como uma lista encadeada.
 */
typedef struct s_grafo Grafo;
typedef struct s_vertice Vertice;
typedef struct s_verticecor VerticeCor;

Grafo* NovoGrafo();
void DeletaGrafo(Grafo* g);

void InsereVertice(Grafo* g);
void InsereAresta(Grafo* g, int v, int w);
void InsereCores(Grafo* g, int* cores);

bool VerificaColoracaoGulosa(Grafo* g);

void ImprimeVertices(VerticeCor* verticesOrdenados, int num_vertices);



#endif
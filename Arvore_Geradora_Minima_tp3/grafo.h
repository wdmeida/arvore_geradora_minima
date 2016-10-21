#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

#define MAX 100
#define NAOMEMBRO 0
#define MEMBRO 1
#define INFINITO 10000000
#include "Lista.h"

typedef int tipo_chave;
typedef unsigned int tipo_peso;

typedef struct{
	tipo_chave chave;
	/*demais componentes*/
}tipo_elemento;

typedef struct {
	Lista vertices[MAX];
	int nv; //Indica a quantidade de vértices.
}tipo_grafo;

typedef tipo_grafo *grafo;

grafo cria_grafo();
void termina_grafo(grafo g);
int pesquisa_vertice(grafo, char*);
int insere_vertice(grafo, tipo_elemento_lista);
int insere_aresta(grafo, char* ,char*,tipo_peso);
int remove_vertice(grafo,tipo_chave_lista*);
int remove_aresta(grafo,tipo_chave_lista*,tipo_chave_lista*);
void imprime_grafo(grafo);
int prim(grafo g);


#endif // GRAFO_H_INCLUDED

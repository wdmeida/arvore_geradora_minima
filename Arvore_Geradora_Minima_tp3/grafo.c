#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"

//Aloca espaço para o grafo.
grafo cria_grafo(){
	grafo g;
	g = (grafo)malloc(sizeof(tipo_grafo));
	if(g)g->nv = 0;
	return g;
}//cria_grafo()

//Libera a memória alocada para o grafo.
void termina_grafo(grafo g){
    int i;
    for(i = 0; i < g->nv; i++)
        free(g->vertices[i]);
    free(g);
}

/*Pesquisa um vértice no grafo, retorna a posição caso encontre ou -1 um caso não encontre.*/
int pesquisa_vertice(grafo g, char *ch){
	int i;
	for(i=0;i<g->nv;i++)
		if(strcmp(g->vertices[i]->first->elemento_lista.cidade, ch) == 0) return i;

	return -1;
}//pesquisa_vertice()

//Insere um vertice no grafo, caso este já não esteja inserido.
int insere_vertice(grafo g, tipo_elemento_lista e){
	if(g->nv == MAX) return 0; //Verifica se o grafo não está cheio.

	if(pesquisa_vertice(g,e.cidade) != -1) return 0; //Caso o vertice ja esteja inserido, aborta a inserção.

	g->vertices[g->nv] = cria_lista(); //Cria a lista na posição.
	insere_lista_inicio(g->vertices[g->nv], e); //Insere o elemento na lista.
	g->vertices[g->nv]->status = espera; //Marca o estatos do vértice.
	g->nv++; //Aumenta o valor de vértices cadastrados.
	return 1;
}//insere_vertice()

/*Insere aresta entre dois vértices.*/
int insere_aresta(grafo g, char* ch1 ,char* ch2, tipo_peso p){
	int posicao1, posicao2;

    //Verifica se o vertice está cadastrado, caso não esteja, não é possível inserir aresta.
	posicao1 = pesquisa_vertice(g,ch1);
	if(posicao1 == -1) return 0;

	posicao2 = pesquisa_vertice(g,ch2);
	if(posicao2 == -1) return 0;

    //Insere na lista que contém o vértice o outro vértice para sinalizar a ligação entre eles.
    tipo_elemento_lista e;
	strcpy(e.cidade, ch2);
	e.distancia = p;
	insere_lista_posicao(g->vertices[posicao1], e, g->vertices[posicao1]->tamanho+1);

	 //Insere na lista que contém o vértice o outro vértice para sinalizar a ligação entre eles.
	strcpy(e.cidade, ch1);
	e.distancia = p;
	insere_lista_posicao(g->vertices[posicao2], e, g->vertices[posicao2]->tamanho+1);

	return 1;
}//insere_aresta()

/*Algoritmo responsável por achar a árvore geradora miníma e a distância percorrida.*/
int prim(grafo g){
   /*Define as variáveis que serão usadas para a execução do algoritmo.*/
        int menor_peso, cidade_visitada = 0, i, j, k, num_vertices, distancia = 0, pos_vertice_menor_peso = 0;
        int pos_nodo[g->nv];
        tipo_nodo_lista *nodo;
        int visitados[g->nv];
        int menor_peso_vertices[g->nv];

        //Inicializa as variáveis responsáveis por fazer o controle dos dados.
        for(i = 0; i < g->nv; i++){ visitados[i] = 0; pos_nodo[i] = 0; menor_peso_vertices[i] = INFINITO;}

        //Atribui o peso inicial como infinito e o primeiro vertice como visitado.
        menor_peso = INFINITO;
        visitados[0] = 1;

        for(num_vertices = 1; num_vertices < g->nv; num_vertices++){
            /*Procura o menor peso de cada lista e atribui ao peso vetor auxiliar que grava
              os pesos.*/
            for(i = 0; i < g->nv; i++){
                if(visitados[i] == 1){
                    menor_peso = INFINITO;
                    nodo = g->vertices[i]->first->next;

                    for(j = 0; j < g->vertices[i]->tamanho-1; j++){
                        if(nodo->elemento_lista.distancia < menor_peso){
                            cidade_visitada = 0;

                            /*Verifica se o menor nodo encontrado ja está no vetor de pesos auxiliar.*/
                            for(k = 0; k < g->nv; k++){
                                if(visitados[k]){
                                    if(!strcmp(nodo->elemento_lista.cidade, g->vertices[k]->first->elemento_lista.cidade))
                                        cidade_visitada = 1;
                                    }
                            }
                            if(cidade_visitada == 0){
                                menor_peso_vertices[i] = nodo->elemento_lista.distancia;
                                menor_peso = nodo->elemento_lista.distancia;
                                pos_nodo[i] = j;
                            }
                        }//if(nodo->elemento_lista.distancia < menor_peso)
                        nodo = nodo->next;
                    }//for
            }//for
        }//for

        /*Procura o menor peso da aresta dentre os vértices, salva a posicao do mesmo.*/
        pos_vertice_menor_peso = 0;
        for(i = 1; i < g->nv; i++) if(menor_peso_vertices[pos_vertice_menor_peso] > menor_peso_vertices[i]) pos_vertice_menor_peso = i;

        //Procura o nodo com menor peso
        nodo = g->vertices[pos_vertice_menor_peso]->first;
        for(i =0; i <= pos_nodo[pos_vertice_menor_peso]; i++){
                nodo = nodo->next;
        }

        //Atribui um para no vetor auxiliar para sinalizar que as cidades foram visitadas.
        for(i = 0; i < g->nv; i++){
                if(strcmp(g->vertices[i]->first->elemento_lista.cidade, nodo->elemento_lista.cidade) == 0){
                        visitados[i] = 1;
                        break;
                }
        }
        //Imprime os vertices processados de cada interação.
        printf("%s", g->vertices[pos_vertice_menor_peso]->first->elemento_lista.cidade);
        printf("------>%s\n", nodo->elemento_lista.cidade);
        distancia += menor_peso_vertices[pos_vertice_menor_peso];
    }//fim for
    return distancia;
}

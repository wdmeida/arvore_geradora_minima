#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo.h"

//Aloca espa�o para o grafo.
grafo cria_grafo(){
	grafo g;
	g = (grafo)malloc(sizeof(tipo_grafo));
	if(g)g->nv = 0;
	return g;
}//cria_grafo()

//Libera a mem�ria alocada para o grafo.
void termina_grafo(grafo g){
    int i;
    for(i = 0; i < g->nv; i++)
        free(g->vertices[i]);
    free(g);
}

/*Pesquisa um v�rtice no grafo, retorna a posi��o caso encontre ou -1 um caso n�o encontre.*/
int pesquisa_vertice(grafo g, char *ch){
	int i;
	for(i=0;i<g->nv;i++)
		if(strcmp(g->vertices[i]->first->elemento_lista.cidade, ch) == 0) return i;

	return -1;
}//pesquisa_vertice()

//Insere um vertice no grafo, caso este j� n�o esteja inserido.
int insere_vertice(grafo g, tipo_elemento_lista e){
	if(g->nv == MAX) return 0; //Verifica se o grafo n�o est� cheio.

	if(pesquisa_vertice(g,e.cidade) != -1) return 0; //Caso o vertice ja esteja inserido, aborta a inser��o.

	g->vertices[g->nv] = cria_lista(); //Cria a lista na posi��o.
	insere_lista_inicio(g->vertices[g->nv], e); //Insere o elemento na lista.
	g->vertices[g->nv]->status = espera; //Marca o estatos do v�rtice.
	g->nv++; //Aumenta o valor de v�rtices cadastrados.
	return 1;
}//insere_vertice()

/*Insere aresta entre dois v�rtices.*/
int insere_aresta(grafo g, char* ch1 ,char* ch2, tipo_peso p){
	int posicao1, posicao2;

    //Verifica se o vertice est� cadastrado, caso n�o esteja, n�o � poss�vel inserir aresta.
	posicao1 = pesquisa_vertice(g,ch1);
	if(posicao1 == -1) return 0;

	posicao2 = pesquisa_vertice(g,ch2);
	if(posicao2 == -1) return 0;

    //Insere na lista que cont�m o v�rtice o outro v�rtice para sinalizar a liga��o entre eles.
    tipo_elemento_lista e;
	strcpy(e.cidade, ch2);
	e.distancia = p;
	insere_lista_posicao(g->vertices[posicao1], e, g->vertices[posicao1]->tamanho+1);

	 //Insere na lista que cont�m o v�rtice o outro v�rtice para sinalizar a liga��o entre eles.
	strcpy(e.cidade, ch1);
	e.distancia = p;
	insere_lista_posicao(g->vertices[posicao2], e, g->vertices[posicao2]->tamanho+1);

	return 1;
}//insere_aresta()

/*Algoritmo respons�vel por achar a �rvore geradora min�ma e a dist�ncia percorrida.*/
int prim(grafo g){
   /*Define as vari�veis que ser�o usadas para a execu��o do algoritmo.*/
        int menor_peso, cidade_visitada = 0, i, j, k, num_vertices, distancia = 0, pos_vertice_menor_peso = 0;
        int pos_nodo[g->nv];
        tipo_nodo_lista *nodo;
        int visitados[g->nv];
        int menor_peso_vertices[g->nv];

        //Inicializa as vari�veis respons�veis por fazer o controle dos dados.
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

                            /*Verifica se o menor nodo encontrado ja est� no vetor de pesos auxiliar.*/
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

        /*Procura o menor peso da aresta dentre os v�rtices, salva a posicao do mesmo.*/
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
        //Imprime os vertices processados de cada intera��o.
        printf("%s", g->vertices[pos_vertice_menor_peso]->first->elemento_lista.cidade);
        printf("------>%s\n", nodo->elemento_lista.cidade);
        distancia += menor_peso_vertices[pos_vertice_menor_peso];
    }//fim for
    return distancia;
}

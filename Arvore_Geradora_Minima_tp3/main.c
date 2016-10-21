#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"

int main(){
    //Cria um grafo para inserir os elementos.
    grafo g = cria_grafo();

	char origem[100], destino [100], token[100];

	int i =0;
	int dist = 0;

	FILE *arq;

	printf("Abrindo arquivo 'cidades.txt'...\n");

	arq = fopen("cidades.txt", "r");

	if(!arq) {printf("Erro na abertura do arquivo."); exit(1);}

    /*Na abertura do arquivo e leitura dos dados, foi verificado um erro que fazia
      com que ocorrece um erro na leitura. Este erro foi sanada com a adição da leitura
      de mais dois caracteres adicionais.*/
	getc(arq);
	getc(arq);
	getc(arq);
	token[i] = getc(arq);

    //Enquanto o arquivo não estiver vazio.
    while(token[i] != EOF){

        /*Copia letra a letra até chegar no caracter delimitador (#), quando chegar
          salva o buffer na origem e ja passa para a próxima.*/
        while(token[i] != '#' && token[i] != EOF){ i++; token[i] = getc(arq);}
        token[i] = '\0';
        strcpy(origem, token);

        /*Copia a segunda palavra repetindo o processo acima.*/
        i = 0;
        token[i]= getc(arq);
        while(token[i]!= '#' && token[i] != EOF){ i++; token[i] = getc(arq); }
        token[i]= '\0';
        strcpy(destino, token);

        /*Copia a distância para do arquivo.*/
        i = 0;
        token[i] = getc(arq);
        while(token[i] != '\n' && token[i] != EOF){ i++; token[i] = getc(arq); }
        token[i] = '\0';

        dist = atoi(token); //Converte a distância para um número inteiro.

        i = 0;
        token[i] = getc(arq);
        tipo_elemento_lista e;

        /*Insere as duas cidades, origem e destino no grafo. O campo distancia foi definido como zero,
          pois de inicio ele seria usado, mas depois no houve a necessidade, ja que o campo que possui
          a distância foi utilizado como aresta.*/
        e.distancia = 0;
        strcpy(e.cidade, origem);
        if(insere_vertice(g, e) == 1) printf("\nInserindo vertice '%s'", origem);

        strcpy(e.cidade, destino);
        e.distancia = 0;
        if(insere_vertice(g, e) == 1) printf("\nInserindo vertice '%s'.", destino);

        /*Insere aresta entre os dois vértices. Como a implementação foi realizada com lista de adjacência,
          insere o elemento da origem na lista de destino e destino na lista de origem, simulando a conexão
          entre os vértices.*/
        insere_aresta(g, origem, destino, dist);
	}//fimWhile

    //Imprime a quantidade de cidades cadastradas.
    printf("\n\nNumero de vertices (cidades) inseridas: %d\n\n",g->nv);

    //Chama a função de prim para calcular a menor distãncia e exibir a árvore geradora mínima.
	printf("\nDistancia percorrida (Arvore Geradora Minima (Prim)):  %d Km\n\n", prim(g));

    //Libera o espaço alocado para o grafo.
	termina_grafo(g);
	return 0;
}


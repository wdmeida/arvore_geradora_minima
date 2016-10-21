#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Lista.h"

//Inicializa a lista encadeada que será usada no grafo.
Lista cria_lista(){
    Lista l = (Lista) malloc(sizeof(tipo_lista));
    if(l != NULL){ l->first = NULL; l->tamanho = 0;}
    return l;
}//cria-Lista()

//Retorna o tamanho da lista.
int tamanho_lista(Lista l){ return l->tamanho;}

//Verifica se a lista é vazia
int lista_lazia(Lista l){if(l->tamanho == 0) return 1; return 0; }

//Insere um elemento no inicio da lista.
int insere_lista_inicio(Lista l, tipo_elemento_lista e){
    tipo_nodo_lista *p;
    p = (tipo_nodo_lista*)malloc(sizeof(tipo_nodo_lista));
    if(p==NULL)
        return 0;

    p->elemento_lista = e;
    if(l->first==NULL){
        p->prior = p;
        p->next = p;
    }
    else{
        p->next = l->first;
        p->prior = l->first->prior;
        l->first->prior->next = p;
        l->first->prior = p;
    }

    l->first = p;
    l->tamanho++;
    return 1;
}//insere_lista_inicio()

//Insere um elemento em uma posição deteerminada na lista.
int insere_lista_posicao(Lista l, tipo_elemento_lista e, int posicao){
    int i;
    tipo_nodo_lista *a,*p;

    if(posicao <= 0 || posicao > l->tamanho +1) return 0;

    if(l->first == NULL || posicao == 1 )
        return insere_lista_inicio(l,e);

    p = (tipo_nodo_lista*)malloc(sizeof(tipo_nodo_lista));
    if(!p)
        return 0;

    a = l->first;
    for(i = 1; i < posicao - 1; i++){
        a = a->next;
    }

    p->elemento_lista = e;

    p->next = a->next;
    p->prior = a;
    a->next->prior = p;
    a->next = p;
    l->tamanho++;
    return 1;
}//insere_lista_posicao()

//Remove um elemento da lista que contenha a chave idêntica a chave inserida por parâmetro.
int remove_lista_chave(Lista l, char *cidade){
	int i;
    tipo_nodo_lista *p, *a;

    p = l->first;
    for(i = 1; i <= l->tamanho; i++){
		if(strcmp(cidade, p->elemento_lista.cidade) == 0){
			if(l->tamanho != 1){
				p->prior->next = p->next;
				p->next->prior = p->prior;

				if(strcmp(cidade, l->first->elemento_lista.cidade) == 0) l->first = p->next;

				free(p);
			}
			l->tamanho--;
			return 1;
		}
		a = p;
        p = p->next;
    }
    return 0;
}//remove_lista_chave()

//Retorna um elemento que esteja na posição passada por parâmetro caso esta seja válida.
int get_elemento(Lista l,tipo_elemento_lista *e, int posicao){
    int i;
    tipo_nodo_lista *p;

    if(posicao < 0 || posicao > l->tamanho) return 0;

    p = l->first;
    if(posicao == 0){
		*e = p->elemento_lista;
		return 1;
    }

    for(i=1; i <= posicao; i++){
        p = p->next;
        *e = p->elemento_lista;
    }
    return 1;
}//get_elemento()

//Libera o espaço alocado para a lista.
void termina_lista(Lista l){
    tipo_nodo_lista *nodo;
    while(l->first != NULL){
        nodo = l->first;
        l->first = l->first->next;
        free(nodo);
    }
    free(l);
}//termina_lista()

//Imprime os elementos da lista.
void imprime_lista(Lista l){
    int i;
    tipo_nodo_lista *p;
    printf("\nTamanho da lista: %d", l->tamanho);
    p = l->first;
    for(i = 0; i < l->tamanho; i++){
        printf("\n%s %d", p->elemento_lista.cidade, p->elemento_lista.distancia);
        p = p->next;
    }
}//imprime_lista()


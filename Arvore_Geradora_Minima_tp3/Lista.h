#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "Lista.h"

typedef char tipo_chave_lista[60];
typedef enum {espera,pronto,processado} tipo_status;

typedef struct{
	tipo_chave_lista cidade;
	int distancia;
}tipo_elemento_lista;

typedef struct nodo{
    tipo_elemento_lista elemento_lista;
    struct nodo *next, *prior;
}tipo_nodo_lista;

typedef struct{
    tipo_nodo_lista *first;
    //char cidade[60];
    int tamanho;
    tipo_status status;
}tipo_lista;

typedef tipo_lista *Lista;

Lista cria_lista();
int tamanho_lista(Lista);
int lista_vazia(Lista);
int insere_lista_inicio(Lista l, tipo_elemento_lista e);
int insere_lista_posicao(Lista l, tipo_elemento_lista e, int posicao);
int remove_lista_chave(Lista l, char *chave);
int get_elemento(Lista l, tipo_elemento_lista *e, int posicao);
void termina_lista(Lista l);
void imprime_lista(Lista l);

#endif // LISTA_H_INCLUDED

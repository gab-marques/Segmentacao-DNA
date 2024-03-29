/*******************************************
 * Implementação simples de lista encadeada.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#ifndef _LISTA_
#define _LISTA_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _ERRO_MALLOC_ 1

// macros para cast de ponteiro de funcao:
#define void_f_obj void(*)(obj)
#define int_f_obj int(*)(obj)
#define str_f_obj char*(*)(obj)

typedef void *obj;
typedef struct t_no *no;
typedef struct t_lista *lista;

typedef struct t_no {
  no proximo;
  no anterior;
  obj conteudo;
} t_no;

typedef struct t_lista {
  no primeiro_no;
  no ultimo_no;
} t_lista;

//---------------------------------------------------------
// getters:

no proximo(no n);
no anterior(no n);
obj conteudo(no n);
no primeiro_no(lista l);
no ultimo_no(lista l);

//---------------------------------------------------------
// funcoes da lista:

// cria lista vazia e a retorna
lista cria_lista();

// devolve 1 se a lista estiver vazia e 0 c.c.
int vazio(lista l);

// devolve o conteudo do inicio da lista e o mantem na lista
obj topo(lista l);

// devolve o conteudo do inicio da lista e o remove da lista
obj desempilha(lista l);

// insere o objeto no inicio da lista
void empilha(obj c, lista l);

// devolve o conteudo do final da lista e o mantem na lista
obj final(lista l);

// devolve o conteudo do final da lista e o remove da lista
obj remove_ultimo(lista l);

// insere o objeto no final da lista
void enfila(obj c, lista l);

// função auxiliar para remover um nó da lista
void remove_no(no n, lista l);

// devolve o conteudo com a chave <chave> e o mantem na lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj busca_chave_int(int chave, lista l, int f_chave(obj c));

// devolve o conteudo com a chave <chave> e o remove da lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj remove_chave_int(int chave, lista l, int f_chave(obj c));

// devolve o conteudo com a chave <chave> e o mantem na lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj busca_chave_str(char *chave, lista l, char *f_chave(obj c));

// devolve o conteudo com a chave <chave> e o remove da lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj remove_chave_str(char *chave, lista l, char *f_chave(obj c));

// devolve o conteudo com a menor chave e o mantem na lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj busca_min(lista l, int f_chave(obj c));

// devolve o conteudo com a menor chave e o remove da lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj remove_min(lista l, int f_chave(obj c));

// imprime a lista
// [a funcao <imprime(c)> deve imprimir o objeto c]
void imprime_lista(lista l, void imprime_conteudo(obj c));

#endif

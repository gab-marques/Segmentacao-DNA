/*******************************************
 * Implementação simples de lista encadeada.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------------------------------------------------
// getters:

no proximo(no n) {
  return n->proximo;
}
no anterior(no n) {
  return n->anterior;
}
obj conteudo(no n) {
  return n->conteudo;
}
no primeiro_no(lista l) {
  return l->primeiro_no;
}
no ultimo_no(lista l) {
  return l->ultimo_no;
}

//---------------------------------------------------------
// funcoes da lista:

// cria lista vazia e a retorna
lista cria_lista() {
  lista l = (lista) malloc(sizeof(t_lista));
  if (!l)
    exit(_ERRO_MALLOC_);
  l->primeiro_no = l->ultimo_no = NULL;
  return l;
}

// devolve 1 se a lista estiver vazia e 0 c.c.
int vazio(lista l) {
  return primeiro_no(l) == NULL;
}

// devolve o conteudo do inicio da lista e o mantem na lista
obj topo(lista l) {
  if (!vazio(l))
    return conteudo(primeiro_no(l));
  return NULL;
}

// devolve o conteudo do inicio da lista e o remove da lista
obj desempilha(lista l) {
  obj c = topo(l);
  if (c) {
    no aux = proximo(primeiro_no(l));
    free(primeiro_no(l));
    l->primeiro_no = aux;
    if (aux)
      aux->anterior = NULL;
    else
      l->ultimo_no = NULL;
  }
  return c;
}

// insere o objeto no inicio da lista
void empilha(obj c, lista l) {
  no n = (no) malloc(sizeof(t_no));
  if (!n)
    exit(_ERRO_MALLOC_);
  no q = primeiro_no(l);
  n->conteudo = c;
  n->proximo = q;
  n->anterior = NULL;
  if (q)
    q->anterior = n;
  else
    l->ultimo_no = n;
  l->primeiro_no = n;
}

// devolve o conteudo do final da lista e o mantem na lista
obj final(lista l) {
  if (!vazio(l))
    return conteudo(ultimo_no(l));
  return NULL;
}

// devolve o conteudo do final da lista e o remove da lista
obj remove_ultimo(lista l) {
  obj c = final(l);
  if (c) {
    no aux = anterior(ultimo_no(l));
    free(ultimo_no(l));
    l->ultimo_no = aux;
    if (aux)
      aux->proximo = NULL;
    else
      l->primeiro_no = NULL;
  }
  return c;
}

// insere o objeto no final da lista
void enfila(obj c, lista l) {
  no n = (no) malloc(sizeof(t_no));
  if (!n)
    exit(_ERRO_MALLOC_);
  no q = ultimo_no(l);
  n->conteudo = c;
  n->anterior = q;
  n->proximo = NULL;
  if (q)
    q->proximo = n;
  else
    l->primeiro_no = n;
  l->ultimo_no = n;
}

// função auxiliar para remover um nó da lista
void remove_no(no n, lista l) {
  if (n) {
    no aux = proximo(n);
    if (aux)
      aux->anterior = anterior(n);
    else
      l->ultimo_no = anterior(n);
    aux = anterior(n);
    if (aux)
      aux->proximo = proximo(n);
    else
      l->primeiro_no = proximo(n);
    free(n);
  }
}

// devolve o conteudo com a chave <chave> e o mantem na lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj busca_chave_int(int chave, lista l, int f_chave(obj c)) {
  no n = primeiro_no(l);
  while (n && f_chave(conteudo(n)) != chave)
    n = proximo(n);
  if (n)
    return conteudo(n);
  return NULL;
}

// devolve o conteudo com a chave <chave> e o remove da lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj remove_chave_int(int chave, lista l, int f_chave(obj c)) {
  no n = primeiro_no(l);
  while (n && f_chave(conteudo(n)) != chave)
    n = proximo(n);
  if (!n)
    return NULL;
  obj c = conteudo(n);
  remove_no(n, l);
  return c;
}

// devolve o conteudo com a chave <chave> e o mantem na lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj busca_chave_str(char *chave, lista l, char *f_chave(obj c)) {
  no n = primeiro_no(l);
  while (n && strcmp(f_chave(conteudo(n)), chave))
    n = proximo(n);
  if (n)
    return conteudo(n);
  return NULL;
}

// devolve o conteudo com a chave <chave> e o remove da lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj remove_chave_str(char *chave, lista l, char *f_chave(obj c)) {
  no n = primeiro_no(l);
  while (n && strcmp(f_chave(conteudo(n)), chave))
    n = proximo(n);
  if (!n)
    return NULL;
  obj c = conteudo(n);
  remove_no(n, l);
  return c;
}

// devolve o conteudo com a menor chave e o mantem na lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj busca_min(lista l, int f_chave(obj c)) {
  if (vazio(l))
    return NULL;
  no n = primeiro_no(l);
  obj min = conteudo(n);
  while (n) {
    if (f_chave(conteudo(n)) < f_chave(min))
      min = conteudo(n);
    n = proximo(n);
  }
  return min;
}

// devolve o conteudo com a menor chave e o remove da lista
// [a funcao <f_chave(c)> deve devolver a chave do objeto c]
obj remove_min(lista l, int f_chave(obj c)) {
  if (vazio(l))
    return NULL;
  no n = primeiro_no(l);
  no min = n;
  while (n) {
    if (f_chave(conteudo(n)) < f_chave(conteudo(min)))
      min = n;
    n = proximo(n);
  }
  obj c = conteudo(min);
  remove_no(min, l);
  return c;
}

// imprime a lista
// [a funcao <imprime(c)> deve imprimir o objeto c]
void imprime_lista(lista l, void imprime_conteudo(obj c)) {
  for (no n = primeiro_no(l); n; n = proximo(n)) {
    imprime_conteudo(conteudo(n));
    printf(" ");
  }
}

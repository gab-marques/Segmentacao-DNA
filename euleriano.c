/*******************************************
 * Biblioteca para Trilha Euleriana em grafo
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "lista.h"
#include "grafo.h"
#include "euleriano.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Encontra uma trilha Euleriana fechada no grafo direcionado G e a devolve
// na forma de uma lista de vértices, com o primeiro e último vértices iguais.
// OBS: para cada par de vértices (u,v) incluído na lista, a aresta (u,v) é
// removida do grafo. Ao final, o conjunto de arestas de G será vazio.
// Funções auxiliares usadas: rotaciona(T), trilha_fechada(G,T,v) e
// concatena(T, TF).
// Função para encontrar uma trilha Euleriana fechada em um grafo direcionado
lista trilha_euleriana(grafo G) {
  // Verificar se todos os vértices têm grau par
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
    vertice atual = conteudo(n);
    if ((grau_saida(atual) + grau_entrada(atual)) % 2 != 0) {
    printf("Não é possível encontrar uma trilha euleriana fechada\n");
    exit(1);
    }
  }
  lista T = cria_lista();
  // Escolher um vértice de início para a trilha Euleriana
  vertice v = conteudo(primeiro_no(vertices(G)));
  empilha(v, T);
  // Enquanto houver arestas no grafo
  while (!vazio(arestas(G))) {
    // Encontrar uma trilha fechada a partir do vértice atual
    lista TF = trilha_fechada(G, v);     
    // Concatenar a trilha fechada com a trilha Euleriana atual
    concatena(T, TF);
    // Atualizar o vértice atual para o último vértice da trilha fechada
    v = conteudo(ultimo_no(TF));
    }
    return T;
}

// Encontra uma trilha fechada no grafo G a partir de v e
// a devolve na forma de uma lista de vértices.
// Para cada par de vértices (u,v) incluído na lista, remove
// do grafo G a aresta (u,v).
lista trilha_fechada(grafo G, vertice v) {
  printf("Trilha fechada a partir de %s\n", vertice_rotulo(v));
  lista trilha = cria_lista();
  vertice atual = v;
  do {
    if (atual->fronteira_saida != NULL && vazio(atual->fronteira_saida) != 1) {
       // Obtém o primeiro vértice na fronteira de saída
      printf("Fronteira de saída de %s: ", vertice_rotulo(atual));
      no n = primeiro_no(atual->fronteira_saida);
      aresta adj = conteudo(n);
      // Adiciona o vértice na trilha
      enfila(vertice_v(adj), trilha);
      // Remove a aresta (atual, w) do grafo
      remove_aresta(aresta_id(adj), G);
      // Atualiza o vértice atual
      atual = vertice_v(adj);
    } else {
        // Se não houver mais vértices na fronteira de saída, saímos do loop
        break;
        }
  } while (atual!= v);
  return trilha;
}

// Recebe uma lista T representando uma trilha fechada e
// um nó n dessa lista e rotaciona a trilha de modo a fazer
// de n o seu início.
void rotaciona(lista T, no n) {
  
  // se T possui um único vértice ou n é o primeiro nó de T,
  // já está rotacionado
  if (primeiro_no(T) == ultimo_no(T) || n == primeiro_no(T))
    return;
  
  desempilha(T);
  no pri = primeiro_no(T);
  no ult = ultimo_no(T);
  no ant = anterior(n);
  if (ant) {
    ult->proximo = pri;
    pri->anterior = ult;
    T->primeiro_no = n;
    n->anterior = NULL;
    T->ultimo_no = ant;
    ant->proximo = NULL;
  }
  enfila(conteudo(n), T);
}

// Considera que T e TF são duas trilhas fechadas com as
// mesmas pontas e concatena TF em T. Libera memória de TF.
void concatena(lista T, lista TF) {
  if (primeiro_no(T) == ultimo_no(T)) {
    T->primeiro_no = primeiro_no(TF);
    T->ultimo_no = ultimo_no(TF);
  }
  else if (primeiro_no(T) != ultimo_no(T)) {
    remove_ultimo(T);
    no m = ultimo_no(T);
    no n = primeiro_no(TF);
    m->proximo = n;
    n->anterior = m;
    T->ultimo_no = ultimo_no(TF);
  }
  free(TF);
}

// Funções para imprimir uma trilha
void imprime_vertice_rotulo(vertice v) {
  printf("%s ", vertice_rotulo(v));
}
void imprime_trilha(lista T) {
  printf("Trilha Euleriana: ( ");
  imprime_lista(T, (void_f_obj) imprime_vertice_rotulo);
  printf(")\n");
}

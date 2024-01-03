/*******************************************
 * Biblioteca para Trilha Euleriana em grafo
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#ifndef _EULERIANO_
#define _EULERIANO_

#include "lista.h"
#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Encontra uma trilha Euleriana fechada no grafo direcionado G e a devolve
// na forma de uma lista de vértices, com o primeiro e último vértices iguais.
// OBS: para cada par de vértices (u,v) incluído na lista, a aresta (u,v) é
// removida do grafo. Ao final, o conjunto de arestas de G será vazio.
// Funções auxiliares usadas: rotaciona(T), trilha_fechada(G,T,v) e
// concatena(T, TF).
lista trilha_euleriana(grafo G);

// Recebe uma lista T representando uma trilha fechada e
// um nó n dessa lista e rotaciona a trilha de modo a fazer
// de n o seu início.
void rotaciona(lista T, no n);

// Encontra uma trilha fechada no grafo G a partir de v e
// a devolve na forma de uma lista de vértices.
// Para cada par de vértices (u,v) incluído na lista, remove
// do grafo G a aresta (u,v).
lista trilha_fechada(grafo G, vertice v);

// Considera que T e TF são duas trilhas fechadas com as
// mesmas pontas e concatena TF em T. Libera memória de TF.
void concatena(lista T, lista TF);

// Funções para imprimir uma trilha
void imprime_vertice_rotulo(vertice v);
void imprime_trilha(lista T);

#endif

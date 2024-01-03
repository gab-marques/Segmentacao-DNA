/*******************************************
 * Biblioteca para manipulação de fragmentos
 * de DNA via spectrum.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#ifndef _SPECTRUM_
#define _SPECTRUM_

#include "lista.h"
#include "grafo.h"
#include "euleriano.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DNA 10000

// Devolve o spectrum (l-mers) do fragmento s
// em uma lista de strings, cada string é um l-mer
lista spectrum(char *s, int l);

// Embaralha o spectrum
void embaralha_spectrum(lista l_mers);

// Funções para impressão
void imprime_mer(char *mer);
void imprime_spectrum(lista l_mers);

// Constroi grafo direcionado a partir do spectrum.
// Vértices são (l-1) mers e arestas representam l-mers.
// É necessário balancear o grafo (adicionar aresta falsa);
// caso isso seja feito, devolve em ini_id e fim_id os ids dos
// vértices da aresta falsa adicionada.
grafo constroi_grafo_spectrum(lista l_mers, int l, int *ini_id, int *fim_id);

// Considera que existem no máximo 2 vértices semi-balanceados
// e adiciona aresta falsa com id IDA entre os vértices de ids
// ini_id e fim_id
int balanceia(grafo G, int IDA, int *ini_id, int *fim_id);

// Constrói um fragmento de DNA com base numa lista de vértices T
// que representa uma trilha Euleriana obtida no grafo do spectrum.
// O inteiro l indica o tamanho dos mers (cada vértice do grafo
// representa um (l-1)-mer) e os inteiros ini_id e fim_id são os
// ids dos vértices da aresta falsa incluída no balanceamento do
// grafo, caso tenho ocorrido (do contrário, devem estar zerados).
char *reconstroi_DNA(lista T, int l, int ini_id, int fim_id);

// Imprime a diferença entre dois fragmentos de DNA
// s e r.
void imprime_diferenca(char *s, char *r);
  
#endif

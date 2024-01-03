/*******************************************
 * Simulação de sequenciamento de DNA.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "lista.h"
#include "grafo.h"
#include "euleriano.h"
#include "spectrum.h"
#include <stdio.h>
#include <stdlib.h>

// ./seqDNA < <entrada.in>
int main() {
  
  // le fragmento do DNA e tamanho dos mers
  char *s = (char *) malloc(sizeof(char)*MAX_DNA);
  int *fim_id = (int *)malloc(sizeof(int));
  int *ini_id = (int *)malloc(sizeof(int));
  int tamanho = 0;
  int acertos = 0;
  if (fim_id == NULL || ini_id == NULL) {
    fprintf(stderr, "Falha na alocação de memória para ini_id ou fim_id.\n");
    return 1; // Código de erro
}
  int l;
  scanf("%s %d", s, &l);  
  // obtem spectrum
  lista l_mers = spectrum(s, l);
  if (!vazio(l_mers))
    printf("n ta vazia");
  //embaralha_spectrum(l_mers); // para simulação mais realista
  imprime_spectrum(l_mers);
  grafo G = constroi_grafo_spectrum(l_mers, l, ini_id, fim_id);
  imprime_grafo(G);
  aresta a = conteudo(primeiro_no(arestas(G)));  
  printf("aresta: %d %d\n", vertice_id(a->u), vertice_id(a->v));
  int ini = vertice_id(a->u);
  int fim = vertice_id(a->v);
  vertice v = conteudo(primeiro_no(vertices(G)));
  lista T = trilha_euleriana(G);
  printf("ini: %d fim: %d\n", ini, fim);
  char *fragmento = reconstroi_DNA(T, l,ini, fim);
   printf("Fragmento de DNA: %s\n", fragmento);
   imprime_diferenca(fragmento,s);
    //Calcular o tamanho do fragmento original
    while (s[tamanho] != '\0') {
        tamanho++;
    }
    //Comparar cada caractere e contar os acertos
    for (int i = 0; i < tamanho; i++) {
        if (s[i] == fragmento[i]) {
            acertos++;
        }
    }
    // Calcular a porcentagem de acerto
    float porcentagem = ((float)acertos / tamanho) * 100;
    printf("Porcentagem de acerto: %.f%%\n", porcentagem);
}

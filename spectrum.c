/*******************************************
 * Biblioteca para manipulação de fragmentos
 * de DNA via spectrum.
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
#include <string.h>
#include <time.h>

// Devolve o spectrum (l-mers) do fragmento s
// em uma lista de strings, cada string é um l-mer
lista spectrum(char *s, int l) {
    lista spectrum = cria_lista();
    int tamanho = strlen(s);
    obj mer;
    if (l <= 0 || l > tamanho) {
        fprintf(stderr, "Tamanho de substring inválido.\n");      
    }
    for (int i = 0; i <= tamanho - l; i++) {
        char *substring = (char *)malloc((l + 1) * sizeof(char));        
        strncpy(substring, &s[i], l);        
        substring[l] = '\0';
        mer = strdup(substring);
        empilha(mer, spectrum);
        free(substring);
    }
    return spectrum;
}

// Embaralha o spectrum
void embaralha_spectrum(lista l_mers) {
  srand(time(NULL));
  int N_SIZE = 5;
  lista L[N_SIZE];
  for (int i = 0; i < N_SIZE; ++i)
    L[i] = cria_lista();
  int i = ((int)rand()) % N_SIZE;
  while (!vazio(l_mers)) {
    enfila(desempilha(l_mers), L[i]);
    i = ((int)rand()) % N_SIZE;
  }
  for (int i = 0; i < N_SIZE; ++i)
    while (!vazio(L[i]))
      enfila(desempilha(L[i]), l_mers);
}

// Funções para impressão
void imprime_mer(char *mer) {
  printf("%s", mer);
}
void imprime_spectrum(lista l_mers) {
  printf("Spectrum: ");
  imprime_lista(l_mers, (void_f_obj) imprime_mer);
  printf("\n");
}

// Constroi grafo direcionado a partir do spectrum.
// Vértices são (l-1) mers e arestas representam l-mers.
// É necessário balancear o grafo (adicionar aresta falsa);
// caso isso seja feito, devolve em ini_id e fim_id os ids dos
// vértices da aresta falsa adicionada.
grafo constroi_grafo_spectrum(lista l_mers, int l, int *ini_id, int *fim_id) {
 grafo G = cria_grafo(1);
    int IDV = 1;
    int IDA = 1;
// Para cada l-mer, adiciona (se já não existe) um vértice com os l-1 primeiros caracteres
// e outro vértice com os l-1 últimos caracteres, e adiciona uma aresta direcionada entre esses vértices.
// Para cada l-mer, adiciona (se já não existe) um vértice com os l-1 primeiros caracteres
// e outro vértice com os l-1 últimos caracteres, e adiciona uma aresta direcionada entre esses vértices.
  for (no n = primeiro_no(l_mers); n; n = proximo(n)) {
      char *lmer = conteudo(n);
      int len = strlen(lmer);
      // Adiciona vértice para os l-1 primeiros caracteres
      char *prefix = strndup(lmer, len - 1);
      char *suffix = strndup(lmer + 1, len - 1);
      vertice v1 = busca_chave_str(prefix, vertices(G), (char *(*)(obj))vertice_rotulo);
      vertice v2 = busca_chave_str(suffix, vertices(G), (char *(*)(obj))vertice_rotulo);
      if (v1 == NULL) {
          adiciona_vertice(IDV, prefix, IDV, G);
          IDV++;
      }
      // Adiciona vértice para os l-1 últimos caracteres
      if (v2 == NULL) {
          adiciona_vertice(IDV, suffix, IDV, G);
          IDV++;
      }   
  }
// Adiciona arestas entre os vértices
  for (no n = primeiro_no(l_mers); n; n = proximo(n)) {
      char *lmer = conteudo(n);
      int len = strlen(lmer);
      char *prefix = strndup(lmer, len - 1);
      vertice v1 = busca_chave_str(prefix, vertices(G), (char *(*)(obj))vertice_rotulo);
      char *suffix = strndup(lmer + 1, len - 1);
      vertice v2 = busca_chave_str(suffix, vertices(G), (char *(*)(obj))vertice_rotulo);
      // Adiciona a aresta se v1 e v2 não são nulos
      if (v1 != NULL && v2 != NULL) {
          adiciona_aresta(IDA, vertice_id(v1), vertice_id(v2), G);
          IDA++;
      }
  }
  balanceia(G, IDA, ini_id, fim_id);
  return G;
}

// Considera que existem no máximo 2 vértices semi-balanceados
// e adiciona aresta falsa com id IDA entre os vértices de ids
// ini_id e fim_id
int balanceia(grafo G, int IDA, int *ini_id, int *fim_id) {
  printf("Balanceando o grafo...\n");
  int _DEBUG = 0;
  vertice semi_u = NULL, semi_v = NULL;
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
    vertice v = conteudo(n);
    int ge = grau_entrada(v);
    int gs = grau_saida(v);   
    if (ge == gs + 1) {
      semi_u = v;
      _DEBUG++;
    }
    else if (ge == gs - 1) {
      semi_v = v;
      _DEBUG++;
    }
    else if (ge != gs) {
      printf("[ERRO] Impossível balancear o grafo. Reporte este problema ao professor...\n");
      exit(1);
    }
  }
  if (_DEBUG != 0 && _DEBUG != 2) {
    printf("[ERRO] Impossível balancear o grafo. Reporte este problema ao professor...\n");
    exit(1);
  }
  if (semi_u && semi_v) {
    *ini_id = vertice_id(semi_u);
    *fim_id = vertice_id(semi_v);
    adiciona_aresta(IDA, *ini_id, *fim_id, G);
    printf("id da aresta falsa: %d\n", IDA);
    printf("ini_id: %d\n", *ini_id);
    printf("fim_id: %d\n", *fim_id);
    return 1;
  }
  return 0;
}

// Constrói um fragmento de DNA com base numa lista de vértices T
// que representa uma trilha Euleriana obtida no grafo do spectrum.
// O inteiro l indica o tamanho dos mers (cada vértice do grafo
// representa um (l-1)-mer) e os inteiros ini_id e fim_id são os
// ids dos vértices da aresta falsa incluída no balanceamento do
// grafo, caso tenho ocorrido (do contrário, devem estar zerados).
char *reconstroi_DNA(lista T, int l, int ini_id, int fim_id) {
  printf("ini_id: %d\n", ini_id);
  printf("fim_id: %d\n", fim_id);
 char *fragmento = (char *)malloc(sizeof(char));
     fragmento[0] = '\0';
          if (ini_id && fim_id) {
         no n = primeiro_no(T);
         while (((vertice)n->conteudo)->id != ini_id && ((vertice)n->proximo->conteudo)->id != fim_id)
           n = n->proximo;
        rotaciona(T, n->proximo);
     }
     else {
         printf("Não é euleriana");
     }
    no n = primeiro_no(T);
    while (n) {
        vertice v = (vertice)n->conteudo;
        strncat(fragmento, v->rotulo, (n == T->primeiro_no) ? strlen(v->rotulo) : strlen(v->rotulo) - 1);
        n = n->proximo;
    }
    return fragmento;
}

// Imprime a diferença entre dois fragmentos de DNA
// s e r.
void imprime_diferenca(char *s, char *r) {
  // Ponteiros para percorrer os fragmentos
  char *ptr_s = s;
  char *ptr_r = r;
  // Percorre ambos os fragmentos enquanto houver caracteres em ambos
  while (*ptr_s != '\0' && *ptr_r != '\0') {
    if (*ptr_s != *ptr_r) {
      printf("%c", *ptr_s);
      printf("%c\n", *ptr_r);
    }
    // Avança para o próximo caractere em ambos os fragmentos
    ptr_s++;
    ptr_r++;
  }
  // Se um dos fragmentos é mais longo que o outro, imprime o restante do fragmento mais longo
  while (*ptr_s != '\0') {
    printf("%c\n", *ptr_s);
    ptr_s++;
  }
  while (*ptr_r != '\0') {
    printf("%c\n", *ptr_r);
    ptr_r++;
  }
}
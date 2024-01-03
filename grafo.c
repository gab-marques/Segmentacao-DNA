/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
}
char* vertice_rotulo(vertice v) {
  return v->rotulo;
}
int vertice_particao(vertice v) {
  return v->particao;
}
int custo(vertice v) {
  return v->custo;
}
int estado(vertice v) {
  return v->estado;
}
vertice pai(vertice v) {
  return v->pai;
}
lista fronteira_entrada(vertice v) {
  return v->fronteira_entrada;
}
lista fronteira_saida(vertice v) {
  return v->fronteira_saida;
}
int aresta_id(aresta e) {
  return e->id;
}
vertice vertice_u(aresta e) {
  return e->u;
}
vertice vertice_v(aresta e) {
  return e->v;
}
int grafo_id(grafo G) {
  return G->id;
}
lista vertices(grafo G) {
  return G->vertices;
}
lista arestas(grafo G) {
  return G->arestas;
}

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo(int id) {
  grafo G = (grafo)malloc(sizeof(t_grafo)); 
  if (!G)
    exit(_ERRO_MALLOC_); 
  G->id = id;
  G->vertices = cria_lista();
  G->arestas = cria_lista();  
  return G;

}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G)
{
  lista vertices_list = vertices(G);
  lista aresta_list = arestas(G);
  while (!vazio(vertices_list))
  {
    desempilha(vertices_list);
  }
  while (!vazio(aresta_list))
  {
    desempilha(aresta_list);
  }
}


// cria novo vertice com id <id> rotulo <rotulo> e adiciona ao grafo G
void adiciona_vertice(int id, char *rotulo, int particao, grafo G) {
  vertice v = busca_chave_int(id, vertices(G), (int (*)(void *))vertice_id);
  if (v == NULL) {
    // Aloca memória para o novo vértice
    vertice v = (vertice)malloc(sizeof(t_vertice));
    if (!v)
      exit(_ERRO_MALLOC_);
    // Inicializa os campos do vértice com os valores passados como argumentos
    v->id = id;
    // Copia a string rotulo para o campo rotulo do vértice
    strncpy(v->rotulo, rotulo, sizeof(v->rotulo) - 1);
    v->rotulo[sizeof(v->rotulo) - 1] = '\0';
    v->particao = particao;
    v->custo = 0;  
    v->estado = 0; 
    v->pai = NULL;
    v->fronteira_entrada = cria_lista(); 
    v->fronteira_saida = cria_lista();  
    empilha(v, vertices(G));
  }
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
  {
  vertice v = busca_chave_int(id, vertices(G), (int (*)(void *))vertice_id);
  if (v)
  {
    // Remove and destroy incident edges
    lista fronteira_list_entrada = fronteira_entrada(v);
    lista fronteira_list_saida = fronteira_saida(v);
    while (!vazio(fronteira_list_saida))
    {
      aresta e = desempilha(fronteira_list_saida);
      remove_aresta(e->id, G);
      // Não é necessário liberar a memória da aresta aqui, pois isso será feito posteriormente
    }
    while (!vazio(fronteira_list_entrada))
    {
      aresta e = desempilha(fronteira_list_entrada);
      remove_aresta(e->id, G);
      // Não é necessário liberar a memória da aresta aqui, pois isso será feito posteriormente
    }
    free(fronteira_list_entrada); // Libere a memória da lista de fronteira
    free(fronteira_list_saida);
    // Remove the vertex from the graph
    remove_chave_int(id, vertices(G), (int (*)(void *))vertice_id);
    free(v); // Libere a memória do vértice
  }
}
}

// cria aresta com id <id>, rotulo <rotulo> e peso <peso>,
// incidente a vertices com ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {
  // Verificar se os vértices são diferentes
     if (u_id == v_id) {
         printf("Erro: Tentativa de adicionar uma aresta de um vértice para ele mesmo.\n");     
     }
    // Obter os vértices correspondentes
    vertice u = busca_chave_int(u_id, vertices(G), (int_f_obj)vertice_id);
    vertice v = busca_chave_int(v_id, vertices(G), (int_f_obj)vertice_id);
    // Verificar se os vértices foram encontrados
     if (!u || !v) {
         printf("Erro: Vértices com IDs %d ou %d não encontrados.\n", u_id, v_id);     
     }
    // Criar a aresta
     aresta a = (aresta)malloc(sizeof(t_aresta));
     if (!a) {
        printf("Erro: Falha ao alocar memória para a aresta.\n");
     }
    a->id = id;
    a->u = u;
    a->v = v;
    // Adicionar a aresta ao grafo
    empilha(a, arestas(G));
    empilha(a, fronteira_saida(u));
    empilha(a, fronteira_entrada(v));
}

// remove aresta com id <id> do grafo G e a destroi
// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
    aresta a = busca_chave_int(id, arestas(G), (int (*)(void *))aresta_id);

    if (a) {
        // Remove a aresta das listas de fronteira dos vértices
        remove_chave_int(id, fronteira_entrada(vertice_u(a)), (int (*)(void *))aresta_id);
        remove_chave_int(id, fronteira_saida(vertice_u(a)), (int (*)(void *))aresta_id);

        // Remove a aresta da lista de arestas do grafo
        remove_chave_int(id, arestas(G), (int (*)(void *))aresta_id);

        free(a);
    }
}


//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau_entrada(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira_entrada(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}
int grau_saida(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira_saida(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("%d\n", grafo_id(G));
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
  printf("\nEstrutura:\n");
  imprime_lista(arestas(G), (void_f_obj) imprime_estrutura_aresta);
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("(id:%d, rotulo:%s, grau_entrada:%d, fronteira_entrada:{ ", vertice_id(v), vertice_rotulo(v), grau_entrada(v));
  imprime_lista(fronteira_entrada(v), (void_f_obj) imprime_aresta);
  printf("}, grau_saida:%d, fronteira_saida:{ ", grau_saida(v));
  imprime_lista(fronteira_saida(v), (void_f_obj) imprime_aresta);
  printf("})");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("(id:%d {%d,%d})", aresta_id(e), u_id, v_id);
}

// imprime apenas a estrutura da aresta e
void imprime_estrutura_aresta(aresta e) {
  char *u_rot = vertice_rotulo(vertice_u(e));
  char *v_rot = vertice_rotulo(vertice_v(e));
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:%s > %d:%s\n", u_id, u_rot, v_id, v_rot);
}

// Verifica se existe uma aresta entre os vértices com ids u_id e v_id no grafo G
int existe_aresta_entre(int u_id, int v_id, grafo G) {
    for (no n = primeiro_no(arestas(G)); n; n = proximo(n)) {
        aresta a = conteudo(n);
        vertice u = vertice_u(a);
        vertice v = vertice_v(a);

        // Verifica se a aresta conecta os vértices u_id e v_id
        if ((vertice_id(u) == u_id && vertice_id(v) == v_id) ||
            (vertice_id(u) == v_id && vertice_id(v) == u_id)) {
            return 1; // Aresta encontrada
        }
    }

    return 0; // Aresta não encontrada
}

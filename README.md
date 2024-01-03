# LEIAME - Programa seqDNA

## Autores
- Gabriela 
- Ana Oporto 

## Informações Relevantes

### Detalhes de Implementação
O programa seqDNA simula o processo de hibridização de fragmentos de DNA, seguindo as etapas descritas no enunciado. Abaixo estão algumas informações relevantes sobre a implementação:

- *Bibiliotecas utilizadas*
- lista.h
# cria as listas eos objetos 
- grafos.h 
# cria o grafo a partir da estrutura lista

- *Funções Auxiliares Criadas:*

lista spectrum(char *s, int l)
#Devolve o spectrum (l-mers) do fragmento s em formato de uma lista de strings, cada string é um l-mer

void embaralha_spectrum(lista l_mers) 
#Embaralha o spectrum

void imprime_mer(char *mer)
#Funções para impressão dos mers criados

void imprime_spectrum(lista l_mers)
#imprime o spectrum

grafo constroi_grafo_spectrum(lista l_mers, int l, int *ini_id, int *fim_id)
#constrói um grafo direcionado onde os vértices representam (l-1)-mers, e as arestas representam l-mers. 

lista trilha_fechada(grafo G, vertice v)
#verifica se eh uma trilha fechada e caso seja 

lista trilha_euleriana(grafo G) 
#procura a trilha se existe uma trilha euleriana usando a funcao trilha fechada  

- *Funções ou Estruturas Modificadas:*
  - spectrum
  - trilha_euleriana
  - trilha_fechada



### Limitações de Funcionamento
- a função embaralha es

## Arquivos no Pacote .zip

1. *seqDNA.c.txt*: Código-fonte principal do programa.
2. *Makefile.txt*: Arquivo de script para facilitar a compilação do programa.
3. *LEIAME.txt*: Este arquivo LEIAME com informações sobre o programa.

## Compilação e Execução

### Compilação
Para compilar o programa, utilize o seguinte comando:
```bash
make

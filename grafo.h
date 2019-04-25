/******************************************************************************
 *
 * Nome do ficheiro: grafo.h
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao: definicao das funcoes e estruturas utilizadas em grafo.c
 *
 *****************************************************************************/

#ifndef grafo_h
#define grafo_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* definicao de estruturas */

typedef struct _node link;

typedef struct _vertex vertex;

typedef struct _graph graph;

/* definicao de funcoes */

link* NewNode(int v, int weight, link *next);

graph** AllocG(graph** G, int max);

graph* InitGraph(int V);

void CreateAdjList(graph* g, int prob,int done);

graph* InsertEdge(graph* g, int src, int dest, int weight);

int DifferentChar(char* s1, char* s2,int prob);

graph* InsertWordsG(graph *g, FILE* dic, int sz,int occur);

void FreeG(graph**G,int max,int* occur);

void RemoveE(graph* g, int problem);

char* getword (graph* g,int v);

int getw(link* aux);

int getv (link* aux);

link* gethead(graph* g,int v);

link* getnext(link* aux);

int getV(graph* g);

graph* SortAndSearch(graph* G,int occur,char* str1,char* str2,int* indexSG);

void quicksort(graph* g, int l, int r);

int partition(graph* g, int l, int r);

int SearchWord (graph* g, char* str);


#endif

/******************************************************************************
 *
 * Nome do ficheiro: heap.h
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao: definicao das funcoes e estruturas utilizadas em heap.c
 *
 *****************************************************************************/

#ifndef heap_h
#define heap_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "grafo.h"

#define INFINITY 10000

/* definicao de estruturas */

typedef struct _heap_node heap_node;

typedef struct _heap heap;

/* definicao de funcoes */

heap* CreateHeap(int size);

heap_node* NewHeapNode(int v, int dist);

void DecreaseKey(heap *h, int v, int dist);

heap_node* DeleteMinNode(heap *h);

void FreeHeap(heap *h);

int* Dijkstra(graph *g, int* indexSG,int* co);

void FixDown(heap * h, int k);


#endif

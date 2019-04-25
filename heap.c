/******************************************************************************
 *
 * Nome do ficheiro: heap.c
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao: implementa:
 *				- funcoes auxiliares para a heap
 *				- algoritmo Dijkstra
 *
 *****************************************************************************/

#include "heap.h"

/* estrutura para um no da heap (acervo) */
struct _heap_node
{
	int v;		/* vertice desse no */
	int dist;	/* distancia desse vertice 'a source (src) */
};

/* estrutura para representar a heap (acervo) */
struct _heap
{
	int n_elements;		/* numero de elementos da heap */
	int size;			/* tamanho (maximo) da heap */
	int *pos;			/* vetor com os indices dos vertices na heap (array); i = pos[v] (v->vertice, i->indice na heap (array) onde esta esse vertice v) */
	heap_node **array;	/* vetor com os nos da heap */
};


/******************************************************************************
 * Nome: CreateHeap()
 *
 * Argumentos:	size - tamanho que a heap vai ter
 *
 * Saida: heap*
 *
 * Descricao: Cria uma heap
 *
 *****************************************************************************/

heap* CreateHeap(int size)
{
	heap *new_h;	/* nova heap */
	int i = 0;		/* variavel auxiliar */

	/* aloca memoria para a heap */
	new_h = (heap* ) malloc(sizeof(heap));
	/* verificacao de erros */
	if(new_h == NULL)
		exit(0);

	/* aloca memoria para o vetor pos */
	new_h->pos = (int *) malloc((size) * sizeof(int ));
	/* verificacao de erros */
	if(new_h->pos == NULL)
		exit(0);

	/* aloca memoria para o vetor com os nos da heap */
	new_h->array = (heap_node** ) malloc((size) * sizeof(heap_node* ));
	/* verificacao de erros */
	if(new_h->array == NULL)
		exit(0);

	/* inicializa o vetor com os nos da heap */
	for(i = 0; i < size; i++)
		new_h->array[i] = NULL;

	/* inicializa as variaveis */
	new_h->n_elements = 0;	/* nr de elementos da heap */
	new_h->size = size;		/* tamanho maximo da heap */

	return new_h;
}


/******************************************************************************
 * Nome: NewHeapNode()
 *
 * Argumentos:	v - vertice do no
 *				dist - custo (entre a palavra origem e o vertice v)
 *
 * Saida: heap_node*
 *
 * Descricao: Cria um no na heap
 *
 *****************************************************************************/

heap_node* NewHeapNode(int v, int dist)
{
	heap_node *new_node;	/* novo no da heap */

	/* aloca memoria para o novo no */
	new_node = (heap_node* ) malloc(sizeof(heap_node ));
	/* verificacao de erros */
	if(new_node == NULL)
		exit(0);

	/* inicializa variaveis */
	new_node->v = v;		/* vertice do novo no */
	new_node->dist = dist;	/* custo do novo no */

	return new_node;
}


/******************************************************************************
 * Nome: DecreaseKey()
 *
 * Argumentos:	h - ponteiro para a estrutura que representa a heap (acervo)
 *				v - vertice do no
 *				dist - novo custo (entre a palavra origem e o vertice v)
 *
 * Saida: void
 *
 * Descricao:	- Encontra o vertice v no acervo h
 *				- Diminui o seu custo
 *				- Faz com que o acervo verifique a sua condicao
 *
 *****************************************************************************/

void DecreaseKey(heap *h, int v, int dist)
{
	int i = 0;		/* indice de v na heap */
	int v_aux = 0;	/* variavel auxiliar de vertices */
	heap_node* t;	/* variavel auxiliar de nos da heap */

	/* i = indice no acervo onde esta o vertice v */
	i = h->pos[v];

	/* diminui a distancia da src a esse vertice v */
	h->array[i]->dist = dist;

	/* faz com que o acervo verifique a sua condicao */
	while((i > 0) && (h->array[i]->dist < h->array[(i-1)/2]->dist))
	{
		/* troca as posicoes dos nos */
		v_aux = h->array[i]->v;
		h->pos[v_aux] = (i-1)/2;
		v_aux = h->array[(i-1)/2]->v;
		h->pos[v_aux] = i;

		/* troca os nos no acervo */
		t = h->array[i];
		h->array[i] = h->array[(i-1)/2];
		h->array[(i-1)/2] = t;

		/* atualiza o valor do indice atual */
		i = (i-1)/2;
	}
}


/******************************************************************************
 * Nome: DeleteMinNode()
 *
 * Argumentos:	h - ponteiro para a estrutura que representa a heap (acervo)
 *
 * Saida: heap_node*
 *
 * Descricao: Retira da heap o no com menor custo (distancia da palavra origem)
 *
 *****************************************************************************/

heap_node* DeleteMinNode(heap *h)
{
	heap_node *root_node;	/* root -> raiz do acervo */
	heap_node *last_node;	/* ultimo no do acervo */

	/* o no com menor distancia sera portanto a raiz do acervo -> indice 0 */
	root_node = h->array[0];

	/* obtem o ultimo no do acervo */
	last_node = h->array[h->n_elements - 1];

	/* o ultimo no passa a ser a raiz */
	/* troca as posicoes dos nos */
	h->pos[root_node->v] = h->n_elements - 1;
	h->pos[last_node->v] = 0;

	/* atualiza a raiz -> passa a ser o antigo ultimo no do acervo */
	h->array[0] = last_node;

	/* decrementa o numero de elementos do acervo */
	h->n_elements --;

	/* faz com que o acervo continue a verificar a sua condicao */
	FixDown(h, 0);	/* fix down a partir do vertice 0 */

	return root_node;
}


/******************************************************************************
 * Nome: FixDown()
 *
 * Argumentos:	h - ponteiro para a estrutura que representa a heap (acervo)
 *				k - vertice a partir do qual se faz fix down
 *
 * Saida: void
 *
 * Descricao: Faz com que o acervo continue a verificar a sua condicao (a partir de k)
 *
 *****************************************************************************/

void FixDown(heap * h, int k)
{
	int j;			/* variavel auxiliar */
  	int v_aux = 0;	/* variavel auxiliar de vertices */
  	heap_node *t;	/* variavel auxiliar de nos da heap */

	while ((2 * k + 1) < h->n_elements)
	{
	    j = 2 * k + 1;

	    if(((j + 1) < h->n_elements) && (h->array[j]->dist > h->array[j+1]->dist))
	    {
	    	/* o segundo filho é menor */
	      	j++;
	    }

	    if( h->array[k]->dist < h->array[j]->dist)
	    {
	     	/* ordem correta */
	     	break;
	    }

		/* troca as posicoes dos nos */
		v_aux = h->array[k]->v;
		h->pos[v_aux] = j;
		v_aux = h->array[j]->v;
		h->pos[v_aux] = k;

		/* troca os nos no acervo */
		t = h->array[k];
		h->array[k] = h->array[j];
		h->array[j] = t;

		/* atualiza o valor de k */
		k = j;
	}
}


/******************************************************************************
 * Nome: FreeHeap()
 *
 * Argumentos:	h - ponteiro para a estrutura que representa a heap (acervo)
 *
 * Saida: void
 *
 * Descricao: Liberta a memoria alocada para a heap
 *
 *****************************************************************************/

void FreeHeap(heap *h)
{
	int i;							/* variavel auxiliar */
	heap_node *aux_node = NULL;		/* variavel auxiliar para um no da heap */
	heap_node **aux_array = NULL;	/* variavel auxiliar para o array da heap */

	/* liberta a memoria alocada para cada no da heap */
	for(i = 0; i < h->n_elements; i++)
	{
		aux_node = h->array[i];
		if (aux_node != NULL)
			free(aux_node);
	}

	/* liberta a memoria alocada para o vetor com os nos da heap */
	aux_array = h->array;
	free(aux_array);
	/* liberta a memoria alocada para o vetor pos */
	free(h->pos);
	/* liberta a heap */
	free(h);
}


/******************************************************************************
 * Nome: Dijkstra()
 *
 * Argumentos:	g - ponteiro para o grafo
 *				indexSG - ponteiro para o vetor com os indices das palavras de origem e de destino
 *				cost - ponteiro para o vetor com os custos
 *
 * Saida: int*
 *
 * Descricao: Algoritmo Dijkstra:
 *				- escolhe o menor caminho entre duas palavras
 *
 *****************************************************************************/

int* Dijkstra(graph *g, int* indexSG, int* cost)
{
	int V = getV(g);	/* variavel com o tamanho do grafo/heap */
	int* dist;			/* vetor auxiliar para as distancias dos vertices a src */
	heap *h;			/* heap (acervo) */
	int i;				/* variavel auxiliar */
	int min = 0;		/* vertice com menor distancia */
	link *aux = NULL;	/* apontador auxiliar para listas de adjacencias */
	int v = 0;			/* variavel auxiliar */
	int new_dist = 0;	/* nova distancia */
	int src = 0, goal = 0;	/* vertices da origem e do destino */
	heap_node *min_node = NULL;	/* no com menor distancia */
	int* st;			/* vetor auxiliar para guardar o caminho de palavras */

	/* aloca memoria para o vetor dist */
	dist = (int*) malloc((V) * sizeof(int));
	/* verificacao de erros */
	if(dist == NULL)
		exit(0);

	/* aloca memoria para o vetor st */
	st = (int*) malloc((V) * sizeof(int));
	/* verificacao de erros */
	if(st == NULL)
		exit(0);

	/* atualiza o vertice da source e do destino */
	src = indexSG[0];
	goal = indexSG[1];

	/* aux fica a apontar para a cabeça da lista de adjacencias da origem */
	aux = gethead(g, src);

	/* cria uma heap com tamanho V */
	h = CreateHeap(V);

	/* inicializa para cada vertice */
	for(i = 0; i < V; i++)
	{
		st[i] = -1;
		/* dist (custo) de cada vertice: infinito */
		dist[i] = INFINITY;
		/* novo vertice com distancia infinita */
		h->array[i] = NewHeapNode(i, dist[i]);
		/* v = i (v->vertice, i->indice da heap (array) no qual o vertice v se encontra) */
		h->pos[i] = i;
	}

	/* a palavra do caminho que vem antes da src e ela mesma, visto ser a primeira */
	st[src] = src;
	/* dist (custo) da src a ela mesma: 0 */
	dist[src] = 0;
	/* diminui o custo da src */
	DecreaseKey(h, src, dist[src]);

	/* a heap encontra-se completamente preenchida */
	h->n_elements = V;

	/* a heap vai conter somente os nos para os quais ainda nao tiver
	 sido calculado o menor caminho */
	/* enquanto a heap nao ficar vazia */
	while(h->n_elements != 0)
	{
		/* retira o no com menor distancia e retorna-o */
		min_node = DeleteMinNode(h);

		/* se o vertice com menor distancia for o vertice de destino */
		if(min_node->v == goal)
		{
			/* liberta a memoria alocada para esse no e sai do loop */
			free(min_node);
			break;
		}

		/* min -> vertice com menor distancia */
		min = min_node->v;

		/* se a distancia (custo) do vertice min = infinita entao ja nao ha melhores caminhos */
		if(dist[min] != INFINITY)
		{
			/* apontador para a lista de adjacencias do vertice min que foi retirado */
			aux = gethead(g,min);
			/* percorre a lista de adjacencias */
			while(aux != NULL)
			{
				v = getv(aux);

				/* distancia de v (a src) a partir do vertice min */
				new_dist = dist[min] + getw(aux);	/* menor distancia de min (a src) + distancia entre min e v */

				/* se a distancia de v (ate a src) atraves de min for menor que a distancia de v ja calculada antes*/
				if(new_dist < dist[v])
				{
					/* atualiza a nova distancia (custo) de v (a src) */
					dist[v] = new_dist;
					/* atualiza a nova distancia (diminui) */
					DecreaseKey(h, v, dist[v]);
					/* a palavra do caminho que vem antes de v : min */
					st[v] = min;
				}
				aux = getnext(aux);
			}
		}
		/* liberta a memoria alocada para o min_node */
		free(min_node);
	}

	/* se o custo entre a origem e o destino for infinito, nao ha caminho */
	if(dist[goal] == INFINITY)
		*cost = -1; /* nao ha caminho */
	else
		*cost = dist[goal]; /* atualiza o custo */

	/* liberta a memoria alocada para a estrutura que representa a heap */
	FreeHeap(h);
	/* liberta a memoria alocada para o vetor dist */
	free(dist);

	return st;
}

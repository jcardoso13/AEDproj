/******************************************************************************
 *
 * Nome do ficheiro: grafo.c
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao: implementa funcoes auxiliares para o grafo
 *
 *****************************************************************************/

#include "grafo.h"

/* estrutura que representa cada no da lista de adjacencias - link */
struct _node
{
	int v;			/* indice do vertice em questao no vetor do grafo */
	int weight;		/* peso - custo */
	link *next;		/* ponteiro para o proximo elemento da lista */
};

/* estrutura que representa cada vertice do grafo - vetor do grafo */
struct _vertex
{
	char* word;		/* palavra que se encontra nesse vertice */
	link *head;		/* ponteiro para o inicio dessa lista de adjacencias */
};

/* estrutura que representa o grafo */
struct _graph
{
	int V;			/* quantidade de vertices - palavras desse grafo */
	int E;			/* quant de arestas */
	vertex *adj;	/* vetor com os vertices */
};


/******************************************************************************
 * Nome: NewNode()
 *
 * Argumentos:	v - vertice desse no
 *				weight - custo da origem a esse no
 *				next - no para o qual ele ficara a apontar
 *
 * Saida: link*
 *
 * Descricao: Cria um novo no na lista de adjacencias
 *
 *****************************************************************************/

link* NewNode(int v, int weight, link *next)
{
	link *new = NULL;

	/* aloca memoria para o novo no */
	new = (link *) malloc(sizeof(link));
	/* verificacao de erros */
	if(new == NULL)
		exit(0);

	/* inicializacao das variaveis que fazem parte do no */
	new->v = v;				/* vertice */
	new->weight = weight;	/* custo */
	new->next = next;		/* elemento seguinte */

	return new;
}


/******************************************************************************
 * Nome: AllocG()
 *
 * Argumentos:	G - ponteiro para o vetor de grafos
 *				max - tamanho maximo das palavras do dicionario
 *
 * Saida: graph*
 *
 * Descricao: Aloca um vetor de grafos
 *
 *****************************************************************************/

graph** AllocG(graph** G, int max)
{
	/* aloca o vetor de grafos */
	G = (graph**) malloc((max+1) * sizeof(graph*));
	/* verificacao de erros */
	if(G == NULL)
		exit(0);

	return G;
}


/******************************************************************************
 * Nome: InitGraph()
 *
 * Argumentos:	V - quantidade de vertices no grafo
 *
 * Saida: graph*
 *
 * Descricao: iniciacao do grafo
 *
 *****************************************************************************/

graph* InitGraph(int V)
{
	int i;
	graph *g = NULL;

	/* aloca memoria para o grafo */
	g = (graph*) malloc(sizeof(graph));
	/* verificacao de erros */
	if(g == NULL)
		exit(0);

	g->V = V;	/* quantidade de vertices do grafo */
	g->E = 0;	/* quantidade de arestas do grafo */

	/* aloca memoria para as listas de adjacencias do grafo */
	g->adj = (vertex *) malloc((V) * sizeof(vertex));
	/* verificacao de erros */
	if(g->adj == NULL)
		exit(0);

	/* inicializacao das listas de adjacencias */
	for(i = 0; i < V; i++)
	{
		g->adj[i].word= NULL;
		g->adj[i].head = NULL;
	}

 	return g;
}


/******************************************************************************
 * Nome: InsertWordsG()
 *
 * Argumentos:	g - ponteiro para o grafo
 *				dic - ponteiro para o ficheiro do dicionario
 *				sz - tamanho das palavras que queremos colocar no grafo
 *				occur - quantidade de palavras desse tamanho no dicionario
 *
 * Saida: graph*
 *
 * Descricao: insere as palavras (vertices) no grafo
 *
 *****************************************************************************/

graph* InsertWordsG(graph *g, FILE* dic, int sz, int occur)
{
	static char str[100];	/* variavel auxiliar */
	int s = 0;				/* tamanho da palavra em questao */
	int quant = occur;		/* quant -> quantidade de palavras que falta ler */
	int k = 0; 				/* variavel auxiliar */

	/* coloca o cursor de volta ao inicio do ficheiro */
	rewind(dic);

	/* verificacao de erros e le a primeira linha do ficheiro */
	if(fscanf(dic, "%s", str) != 1)
		exit(0);

	while(1)
	{
		/* guarda o tamanho da palavra */
		s = strlen(str);

		/* se a palavra presente for do tamanho que interessa */
		if(s == sz)
		{
			/* aloca uma nova palavra para o grafo */
			g->adj[k].word = (char*) malloc((sz+1) * sizeof(char));
			/* verificacao de erros */
			if(g->adj[k].word == NULL)
				exit(0);

			/* copia a palavra para o vertice */
			strcpy(g->adj[k].word, str);
			/* incrementa a posicao (de vertices) no grafo */
			k++;
			/* decrementa a quantidade de palavras que falta ler */
			quant--;
		}

		/* quando chega ao final do ficheiro ou se ja nao falta ler nenhuma palvavra, sai do loop */
		if(fscanf(dic, "%s", str) == EOF || quant == 0)
			break;
	}

	return g;
}


/******************************************************************************
 * Nome: DifferentChar()
 *
 * Argumentos:	s1 - palavra de origem
 *				s2 - palavra pertencente a um dos vertices do grafo
 *				max - numero maximo de caracteres que se pode alterar em 1 mutacao
 *
 * Saida: int
 *
 * Descricao: calcula a quantidade de caracteres diferentes nas palavras
 *
 *****************************************************************************/

int DifferentChar(char* s1, char* s2, int max)
{
	char *apt1;			/* apontador auxiliar para s1 */
	char *apt2;			/* apontador auxiliar para s2 */
	char letter1;		/* caracter auxiliar para s1 */
	char letter2;		/* caracter auxiliar para s2 */
	int diffc = 0;		/* quantidade de caracteres diferentes */

	/* desde o inicio ate ao fim das 2 palavras */
	for(apt1 = s1, apt2 = s2; *apt1 != '\0'; apt1++, apt2++)
	{
		letter1 = *apt1;
		letter2 = *apt2;
		/* se os caracteres forem diferentes */
		if(letter1 - letter2 != 0)
			diffc ++;	/* incrementa a quantidade de caracteres diferentes */

		/* se a quantidade de caracteres diferentes ja for maior que a quantidade maxima */
		if(diffc > max)
		{
			return diffc;
		}
	}

	return diffc;
}


/******************************************************************************
 * Nome: InsertEdge()
 *
 * Argumentos:	g - ponteiro para o grafo
 *				src - vertice com a palavra de origem da aresta
 *				dest - vertice com a palavra de destino da aresta
 *				weight - custo (peso) da aresta
 *
 * Saida: graph*
 *
 * Descricao: insere uma aresta no grafo caso esta ainda nao exista
 *
 *****************************************************************************/

graph* InsertEdge(graph* g, int src, int dest, int weight)
{
	link *new = NULL;

	/* guarda a aresta na lista correspondente ao vertice de origem (src) */
	new = NewNode(dest, weight, g->adj[src].head);
	g->adj[src].head = new;

	/* guarda a aresta na lista correspondente ao vertice de destino (dest) */
	new = NewNode(src, weight, g->adj[dest].head);
	g->adj[dest].head = new;

	/* incrementa o numero de arestas */
	g->E ++;

	return g;
}


/******************************************************************************
 * Nome: CreateAdjList()
 *
 * Argumentos:	g - ponteiro para o grafo
 *				prob - numero maximo de caracteres que se pode alterar em 1 mutacao
 *				done - guarda o ultimo "prob" do grafo em questao
 *
 * Saida: void
 *
 * Descricao: cria a lista de adjacencias de cada vertice
 *
 *****************************************************************************/

void CreateAdjList(graph* g, int prob, int done)
{
	int cost = 0;		/* custo da mutacao entre as duas palavras */
	int diff_char = 0;	/* quantidade de caracteres diferentes (em cada posicao) */
	int src = 0;		/* vertice de origem (source) */
	int dest = 0;		/* vertice de destino */
	int i = 0, j = 0;	/* variaveis auxiliares */

	/* para cada vertice do grafo */
	for(i = 0; i < g->V; i++)
	{
		for(j = (i+1); j < g->V; j++)
		{
			/* calcula quantos caracteres diferentes ha entre as palavras */
			diff_char = DifferentChar(g->adj[i].word, g->adj[j].word,prob);

			/* se respeita a condicao do problema */
			if(diff_char <= prob && diff_char > done)
			{
				/* calcula o custo da mutacao */
				cost = diff_char*diff_char;

				/* atualiza os valores dos vertices da origem e do destino da aresta */
				src = i;
				dest = j;
				/* insere a aresta na lista de adjacencias */
				g = InsertEdge(g, src, dest, cost);
			}
		}
	}
}


/******************************************************************************
 * Nome: RemoveE()
 *
 * Argumentos:	g - ponteiro para o grafo
 *				problem - numero maximo de caracteres que se pode alterar em 1 mutacao
 *
 * Saida: void
 *
 * Descricao: remove uma aresta do grafo
 *
 *****************************************************************************/

void RemoveE(graph* g, int problem)
{
	int i = 0;	/* variavel auxiliar */
	link* cur = NULL, *prev = NULL, *aux = NULL;	/* ponteiros auxiliares */
	problem = problem*problem;	/* custo maximo */

	/* para cada vertice */
	for(i = 0; i < g->V; i++)
	{
		/* cur fica a apontar para a cabeça da lista de adjacencias */
		cur = g->adj[i].head;
		prev = NULL;
		aux = NULL;

		/* enquanto nao se chegar ao fim da lista de adjacencias */
		while(cur != NULL)
		{
			/* se o custo da aresta for maior que o custo maximo */
			if(cur->weight > problem)
			{
				/* remove a aresta em questao */
				if(prev != NULL)
					prev->next = cur->next;
				else
				{
					g->adj[i].head = cur->next;
				}

				aux = cur;
				cur = cur->next;
				/* liberta a memoria alocada para a aresta removida */
				free(aux);
			}
			else
			{
				prev = cur;
				cur = cur->next;
			}
		}
	}
}


/******************************************************************************
 * Nome: FreeG()
 *
 * Argumentos:	G - ponteiro para o vetor de grafos
 *				max - tamanho de palavra máximo no dicionario
 *				occur - vetor com a quantidade de palavras de tamanho i no dicionario
 *
 * Saida: void
 *
 * Descricao: liberta a memoria alocada para os grafos
 *
 *****************************************************************************/

void FreeG(graph** G, int max, int* occur)
{
	/* declaracao de variaveis auxiliares */
	int i = 0, j = 0;
	graph* g = NULL;
	vertex* v = NULL;
	char* str = NULL;
	link *cur = NULL, *aux = NULL;

	/* para cada tamanho de palavras */
	for(i = 0; i <= max; i++)
	{
		/* fica a apontar para o grafo correspondente */
		g = G[i];

		if(g != NULL)
		{
			/* para cada palavra (vertice) desse grafo */
			for(j = 0; j < occur[i]; j++)
			{
				v = &(g->adj[j]);
				str = v->word;
				/* liberta a memoria alocada para a palavra */
				free(str);
				/* cur fica a apontar para a cabeça da lista de adjacencias */
				cur = v->head;
				while(cur != NULL)
				{
					aux = cur;
					cur = cur->next;
					/* liberta a memoria alocada para o no da lista de adjacencias */
					free(aux);
				}
			}
			v = g->adj;
			/* liberta a memoria alocada para o vertice */
			free(v);
			/* liberta a memoria alocada para o grafo */
			free(g);
		}
	}
	/* liberta a memoria alocada para o vetor de grafos */
	free(G);
}


/******************************************************************************
 * Nome: getword()
 *
 * Argumentos:	g - ponteiro para o grafo
 *				v - vertice do grafo
 *
 * Saida: char*
 *
 * Descricao: retorna a palavra correspondente ao vertice v
 *
 *****************************************************************************/

char* getword(graph* g, int v)
{
	return g->adj[v].word;
}


/******************************************************************************
 * Nome: gethead()
 *
 * Argumentos:	g - ponteiro para o grafo
 *				v - vertice do grafo
 *
 * Saida: link*
 *
 * Descricao: retorna a cabeça da lista de adjacencias correspondente ao vertice v
 *
 *****************************************************************************/

link* gethead(graph* g, int v)
{
	return g->adj[v].head;
}


/******************************************************************************
 * Nome: getv()
 *
 * Argumentos:	aux - ponteiro para um no da lista de adjacencias
 *
 * Saida: int
 *
 * Descricao: retorna o vertice desse no
 *
 *****************************************************************************/

int getv(link* aux)
{
	return aux->v;
}


/******************************************************************************
 * Nome: getw()
 *
 * Argumentos:	aux - ponteiro para um no da lista de adjacencias
 *
 * Saida: int
 *
 * Descricao: retorna o custo desse no (peso da aresta correspondente)
 *
 *****************************************************************************/

int getw(link* aux)
{
	return aux->weight;
}


/******************************************************************************
 * Nome: getnext()
 *
 * Argumentos:	cur - ponteiro para um no da lista de adjacencias
 *
 * Saida: link*
 *
 * Descricao: retorna o no seguinte (a cur) na lista de adjacencias
 *
 *****************************************************************************/

link* getnext(link* cur)
{
	return cur->next;
}
/******************************************************************************
 * Nome: getV()
 *
 * Argumentos:	g - ponteiro para o grafo
 *
 *
 * Saida: int
 *
 * Descricao:
 *
 *****************************************************************************/
 int getV(graph* g)
 {
	 return g->V;
 }

/******************************************************************************
 * Nome: SortAndSearch()
 *
 * Argumentos:	G - ponteiro o grafo
 *				occur - quantidade de palavras desse tamanho no dicionario
 *				str1 - palavra de origem
 *				str2 - palavra de destino
 *				indexSG - vetor com os indices das palavras de origem e de destino
 *
 * Saida: graph*
 *
 * Descricao: ordena os vertices do grafo e procura as palavras de origem e de destino
 *
 *****************************************************************************/

graph* SortAndSearch(graph* G, int occur, char* str1, char* str2, int* indexSG)
{
	/* ordena os vertices do grafo */
	quicksort(G, 0, occur-1);

	/* encontra a palavra de origem no grafo */
	indexSG[0] = SearchWord(G, str1);

	/* encontra a palavra de destino no grafo */
	indexSG[1] = SearchWord(G, str2);

	return G;
}


/******************************************************************************
 * Nome: quicksort()
 *
 * Argumentos:	g - ponteiro o grafo
 *				l - vertice inicial (left)
 *				r - vertice final (right)
 *
 * Saida: void
 *
 * Descricao: ordena os vertices do grafo (algoritmo Quicksort)
 *
 *****************************************************************************/

void quicksort(graph* g, int l, int r)
{
   int j;	/* variavel auxiliar */

   if(l < r)
   {
   		/* algoritmo de particao */
       j = partition(g, l, r);
       quicksort(g, l, j-1);
       quicksort(g, j+1, r);
   }

}


/******************************************************************************
 * Nome: partition()
 *
 * Argumentos:	g - ponteiro o grafo
 *				l - vertice inicial (left)
 *				r - vertice final (right)
 *
 * Saida: int
 *
 * Descricao: algoritmo de particao
 *
 *****************************************************************************/

int partition(graph* g, int l, int r)
{
	int i = 0, j = 0;	/* variaveis auxiliares */
	char* v, *temp;

    v = g->adj[l].word;
    i = l;
    j = r+1;

    do
    {
        do
        {
            i++;
		}while(i<=r && strcmp(g->adj[i].word,v)<0);

        do
            j--;
        while(j>=l && strcmp(v,g->adj[j].word)<0);

        if(i<j)
        {
            temp=g->adj[i].word;
            g->adj[i].word=g->adj[j].word;
            g->adj[j].word=temp;
        }

    }while(i<j);

    if (j<=r && j>=l)
    	g->adj[l].word=g->adj[j].word;

    g->adj[j].word=v;

    return(j);

}


/******************************************************************************
 * Nome: SearchWord()
 *
 * Argumentos:	g - ponteiro o grafo
 *				str - palavra que a funcao vai procurar no grafo
 *
 * Saida: int
 *
 * Descricao: encontra uma palavra no grafo
 *
 *****************************************************************************/

int SearchWord (graph* g, char* str)
{
	int m, s = 0;
	int aux = 0;
	int l = 0;
	int r = g->V;

	while(r >= 1)
	{
		m = (l + r)/2;
		s = strcmp(str, g->adj[m].word);
		/* se forem iguais */
		if(s == 0)
			return m;
		/* se s1 for menor que w[m] */
		if(s < 0)
			r = m - 1;
		else
			l = m + 1;
	}

	aux = strcmp(g->adj[r].word, str);
	if(aux != 0)
		exit(0);

	return 0;
}

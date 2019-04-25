/******************************************************************************
 *
 * Nome do ficheiro: pal.c
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao:	ficheiro onde se resolvem todos os problemas
 *
 *****************************************************************************/

#include "dic.h"
#include "pal.h"
#include "grafo.h"
#include "heap.h"
#include "ficheiro.h"


/******************************************************************************
 * Nome: ReadPal()
 *
 * Argumentos:	dic - ponteiro para o ficheiro com o dicionario
 *				pal - ponteiro para o ficheiro de problemas
 *				name_pal - ponteiro para o nome do ficheiro de problemas
 *
 * Saida: void
 *
 * Descricao: Resolve os problemas
 *
 *****************************************************************************/

void ReadPal(FILE* pal, FILE* dic, char* name_pal)
{
	char str1[100];			/* variavel auxiliar */
	char str2[100];			/* variavel auxiliar */
	int sz = 0;         	/* variavel auxiliar para tamanhos de palavras */
	int *occur = NULL;  	/* vetor com a quantidade de palavras de tamanho i no dicionario */
	char *namef = NULL; 	/* nome do ficheiro de output */
	int problem = 0;    	/* numero maximo de caracteres que se pode alterar em 1 mutacao */
	graph** G = NULL;   	/* vetor de grafos */
	graph* g = NULL;    	/* grafo */
	int max = 0;        	/* tamanho de palavra máximo no dicionario */
	int *done = NULL;   	/* guarda para cada grafo o ultimo "problem" */
	FILE* output = NULL;	/* ficheiro de saida */
	int indexSG[2]; 		/* vetor com os vertices da palavra de origem (Source) e de destino (Goal) */
	int* st = NULL;			/* vetor auxiliar para guardar o caminho de palavras */
	int co;					/* custo para o output */
	int i = 0;    	    	/* variavel auxiliar */

	sz = strlen(name_pal);
	/* alocacao do nome do ficheiro de saida */
	namef = (char*) malloc((strlen(name_pal)+2) * sizeof(char));
	/* verificacao de erros */
	if(namef == NULL)
		exit(0);

	/* copia o nome do ficheiro pal para namef */
	strcpy(namef, name_pal);
	/* retira a extensao .pal */
	namef[sz-4] = '\0';
	/* coloca a extensao */
	strcat(namef, ".path");
	/* abre um ficheiro para escrita */
	output = fopen(namef, "w");
	/* verificacao de erros */
	if(output == NULL)
		exit(0);

	/* retorna o tamanho da maior palavra do dicionario */
	max = ReadDicBiggestW(dic);

	/* alocacao do vetor de ocorrencias */
	occur = (int*) malloc((max+1) * sizeof(int));
	/* verificacao de erros */
	if(occur == NULL)
		exit(0);

	/* alocacao de memoria para o vetor */
	done = (int*) malloc((max+1) * sizeof(int));
	/* verificacao de erros */
	if(done == NULL)
		exit(0);

	/* inicializacao de ambos os vetores */
	for(i = 0; i <= max; i++)
	{
		done[i] = 0;
		occur[i] = 0;
	}

	/* guarda as ocorrencias de palavras cada tamanho do dicionario */
	ReadDicOccur(dic, occur);
	/* alloca um vetor de grafos */
	G = AllocG(G, max);

	/* inicializa o vetor de grafos */
	for(i = 0; i <= max; i++)
	{
		G[i] = NULL;
	}

	/* enquanto nao chegar ao final do ficheiro, resolve os problemas */
	while(fscanf(pal,"%s %s %d", str1, str2, &problem) != EOF)
	{
		/* guarda o tamanho da palavra */
		sz = strlen(str1);
		/* o grafo em questao sera colocado na posicao relativa ao tamanho dessas palavras */
		g = G[sz];

		if(g == NULL)
		{
			/* cria um grafo */
			g = InitGraph(occur[sz]);
			/* insere as palavras (vertices) no grafo */
			g = InsertWordsG(g, dic, sz, occur[sz]);

			/* ordena o grafo e encontra os vertices correspondentes a palavra de destino e a de origem */
			g = SortAndSearch(g, occur[sz], str1, str2, indexSG);
		}
		else
		{
			/* procura a palavra origem no grafo */
			indexSG[0] = SearchWord(g, str1);
			/* procura a palavra destino no grafo */
			indexSG[1] = SearchWord(g, str2);
		}
		/* se o grafo em questao esta feito para um problema com menor custo maximo */
		if(done[sz] < problem)
		{
			/* cria uma lista de adjacencias */
			CreateAdjList(g, problem, done[sz]);
			/* atualiza o valor do vetor done */
			done[sz] = problem;
		}
		/* se o grafo em questao esta feito para um problema com maior custo maximo */
		else if(done[sz] > problem)
		{
			/* remove as arestas do grafo que estao a mais */
			RemoveE(g, problem);
			/* atualiza o valor do vetor done */
			done[sz] = problem;
		}

		problem = problem*problem;

		/* faz o algoritmo de Dijkstra com o grafo presente */
		st = Dijkstra(g, indexSG, &co);
		if(co == -1)
		{
			st[indexSG[1]] = indexSG[0];
		}

		/* escreve o ficheiro de saida */
		foutput(st, g, output, indexSG[1], co);

		/* liberta a memoria alocada para o vetor st */
		free(st);
		G[sz] = g;
	}

	/* liberta memoria alocada */
	FreeG(G, max, occur);
	fclose(output); /* fecha o ficheiro de saida */
  	free(namef);	/* liberta a memoria alocada para o nome do ficheiro de saida */
  	free(occur);	/* liberta a memoria alocada para o vetor ocorrencias */
	free(done);		/* liberta a memoria alocada para o vetor done */
}

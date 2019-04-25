/******************************************************************************
 *
 * Nome do ficheiro: ficheiro.c
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao: implementa funcoes auxiliares para os ficheiros de entrada/saida
 *
 *****************************************************************************/

#include "ficheiro.h"

/******************************************************************************
 * Nome: checkArg()
 *
 * Argumentos:	dic - ponteiro para o nome do ficheiro com o dicionario
 *				pal - ponteiro para o nome do ficheiro de problemas
 *
 * Saida: void
 *
 * Descricao: verifica se as extensoes dos ficheiros de entrada estao corretas
 *
 *****************************************************************************/

void checkArg(char* dic, char* pal)
{
	char aux1[] = ".pal";
	char aux2[] = ".dic";
	int sz, i, j = 0;

	/* para verificar a extensao do ficheiro.pal */
	sz = strlen(pal);
	/* verificacao de erros */
	if(sz < 4)
		exit(0);

	for(i = 4; i >= 0; i--)
	{
		if(pal[sz-i] != aux1[j])
			exit(0);	/* Não é igual a pal logo não é do tipo .pal */
		j++;
	}

	/* para verificar a extensao do ficheiro.dic */
	j = 0;

	sz = strlen(dic);
	/* verificacao de erros */
	if(sz < 4)
		exit(0);

	for(i = 4; i >= 0; i--)
	{
		if(dic[sz-i] != aux2[j])
			exit(0); /* Não é igual a dic logo não é do tipo .dic */
		j++;
	}
}


/******************************************************************************
 * Nome: openFile()
 *
 * Argumentos:	str - ponteiro para o nome do ficheiro de leitura
 *
 * Saida: ponteiro para o ficheiro (FILE*)
 *
 * Descricao: abre um ficheiro em modo de leitura
 *
 *****************************************************************************/

FILE* openFile(char* str)
{
	FILE* fp;

	/* abre o ficheiro para leitura */
	fp = fopen(str, "r");
	/* verificacao de erros */
	if(fp == NULL)
		exit(0);

	return fp;
}


/******************************************************************************
 * Nome: foutput()
 *
 * Argumentos:	st - vetor com a informacao do caminho de palavras
 *				g - ponteiro para o grafo
 *				out - ponteiro para o ficheiro de saida
 *				dest - vertice com a palavra de destino
 *				co - custo do caminho
 *
 * Saida: void
 *
 * Descricao: escreve o ficheiro de saida
 *
 *****************************************************************************/

void foutput(int* st, graph* g, FILE* out, int dest, int co)
{
	/* imprime no ficheiro a resolucao de um problema */
	fprintf(out, "%s\n", STA(g, dest, st, out, co));
	fprintf(out, "\n");
}


/******************************************************************************
 * Nome: STA()
 *
 * Argumentos:	g - ponteiro para o grafo
 *				a - vertice com a palavra de destino
 *				st - vetor com a informacao do caminho de palavras
 *				out - ficheiro de saida
 *				cost - custo do caminho
 *
 * Saida: char* (palavra para fazer fprintf)
 *
 * Descricao: funcao auxiliar para a escrita do ficheiro de saida. Função
 * recursiva que chama fprintf com um arg STA ate chegar a source
 *
 *****************************************************************************/

char* STA(graph* g, int a, int* st, FILE* out, int cost)
{
	int v = 0, b = 0;

	v = st[a];
	b = st[v];

	if(b == v) /* o src é o unico que aponta para ele mesmo! */
	{
		/* escreve no ficheiro de saida */
		fprintf(out, "%s %d\n", getword(g,v), cost);
		return getword(g, a);
	}
	else
	{
		/* escreve no ficheiro de saida */
		fprintf(out, "%s\n", STA(g, v, st, out, cost));
		return getword(g, a);
	}
}

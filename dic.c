/******************************************************************************
 *
 * Nome do ficheiro: dic.c
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao: implementa funcoes auxiliares para o ficheiro do dicionario
 *
 *****************************************************************************/

#include "dic.h"


/******************************************************************************
 * Nome: ReadDicBiggestW()
 *
 * Argumentos:	dic - ponteiro para o ficheiro com o dicionario
 *
 * Saida: int
 *
 * Descricao: Verifica qual é o tamanho da maior palavra do dicionario
 *
 *****************************************************************************/

int ReadDicBiggestW(FILE* dic)
{
	char str[100];	/* variavel auxiliar */
	int max = 0;	/* tamanho maximo */
	int s = 0;		/* tamanho da palavra em questao */

	/* verificacao de erros e leitura da primeira linha do ficheiro */
	if(fscanf(dic, "%s", str) != 1)
		exit(1);

	/* enquanto nao chegar ao final do ficheiro, le cada linha */
	while(1)
	{
		/* guarda o tamanho da palavra */
		s = strlen(str);

		/* se o tamanho da palavra for maior que o tamanho maximo */
		if(s > max)
			max = s; /* o tamanho maximo passa a ser s */

		/* se chegar ao final do ficheiro, sai do loop */
		 if (fscanf(dic, "%s", str) == EOF)
		 	break;
	}

	return max;
}


/******************************************************************************
 * Nome: ReadDicOccur()
 *
 * Argumentos:	dic - ponteiro para o ficheiro com o dicionario
 *				occ - vetor com a quantidade de palavras de cada tamanho
 *
 * Saida: void
 *
 * Descricao: Verifica a quantidade de palavras de cada tamanho no dicionario
 *
 *****************************************************************************/

void ReadDicOccur(FILE* dic, int* occ)
{
	char str[100];	/* variavel auxiliar */
	int s = 0;		/* tamanho da palavra em questao */

	/* coloca o cursor de volta ao inicio do ficheiro */
	rewind(dic);

	/* verificacao de erros e leitura da primeira linha do ficheiro */
	if (fscanf(dic, "%s", str)!=1)
		exit(0);

	/* enquanto nao chegar ao final do ficheiro, le cada linha */
	while(1)
	{
		/* guarda o tamanho da palavra */
		s = strlen(str);

		/* incrementa as ocorrencias de palavras com esse tamanho */
		(occ[s])++;

		/* se chegar ao final do ficheiro, sai do loop */
		if (fscanf(dic, "%s", str)==EOF	)
		 	break;
	}
}

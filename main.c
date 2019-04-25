/******************************************************************************
 *
 * Nome do ficheiro: main.c
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao:	main do projeto:
 *				Projeto - Word Morph
 *
 * Data de entrega: 14-12-2016
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ficheiro.h"
#include "pal.h"
#include "dic.h"
#include "grafo.h"
#include "heap.h"


/******************************************************************************
 * Nome: main()
 *
 * Argumentos:	argc - numero de argumentos da linha de comandos
 *				argv - tabela de ponteiros para argumentos do tipo string
 *
 * Saida: int
 *
 * Descricao: main do programa 
 *
 *****************************************************************************/

int main(int argc, char* argv[])
{
	FILE *pal = NULL, *dic = NULL;

	if(argc != 3)
	{
		/* sai do programa se a linha de comandos nao apresentar 3 argumentos */
    	exit(0);
	}

	/* verifica se as extensoes dos ficheiros de entrada estao corretas */
	checkArg(argv[1], argv[2]);

	/* abre o ficheiro com o dicionario para leitura */
	dic = openFile(argv[1]);

	/* abre o ficheiro de problemas para leitura */
	pal = openFile(argv[2]);

	/* resolve o ficheiro de problemas */
	ReadPal(pal, dic, argv[2]);

	/* fecha os ficheiros abertos para leitura */
	fclose(dic);
	fclose(pal);

	return 0;
}

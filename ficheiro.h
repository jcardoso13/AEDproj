/******************************************************************************
 *
 * Nome do ficheiro: ficheiro.h
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao: definicao das funcoes utilizadas em ficheiro.c
 *
 *****************************************************************************/

#ifndef FICHEIRO_H
#define FICHEIRO_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pal.h"
#include "grafo.h"


void checkArg(char* dic, char* pal);

FILE* openFile (char* str);

void foutput(int* st,graph* g,FILE* out,int dest,int co);

char* STA(graph* g,int a,int* st,FILE* out,int cost);


#endif

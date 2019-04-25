/******************************************************************************
 *
 * Nome do ficheiro: dic.h
 *
 * Autores:		Sara Henriques 81261 MEEC
 *				Joao Cardoso 84096 MEEC
 *
 * Bibliotecas incluidas:
 *		#include <stdio.h>
 *		#include <stdlib.h>
 *		#include <string.h>
 *
 * Descricao: definicao das funcoes utilizadas em dic.c
 *
 *****************************************************************************/

#ifndef _DIC_H
#define _DIC_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int ReadDicBiggestW(FILE* dic);

void ReadDicOccur(FILE* dic, int* occ);


#endif

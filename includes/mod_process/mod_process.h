
#include <stdio.h>
#include <stdlib.h>
#include "mod_process.c"

/*
Aqui estarao as funcoes de processamento. Durante a fase 2, esta secao sera expandida e passara a conter
funcoes extremamente importantes para a execucao da simulacao e para o processamento do Log Final.
*/

int log_run(FILE* , C_list* , G_list* , I_list* , A_list* );


int print_lists(C_list** , G_list** , I_list** , A_list** );

int weave(void** , char ,
						C_list**,	//data referente às cidades (para poder fazer a busca)
						A_list**,	//data referente aos adaptadores (para poder fazer a busca)
						I_list**		//data referente às interconexões (para poder fazer a busca)
						);

int web_run (void** , char );
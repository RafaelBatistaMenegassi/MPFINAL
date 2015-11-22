#include <stdlib.h>
#include <stdio.h>
//#include <assert.h>

//#include "includes/mod_def/essential_defs.h"
//#include "includes/mod_def/errorcodes.h"

#include "includes/mod_construcao.h"

#define ENTRADA "includes/teste.txt"
#define SAIDA "log.txt"

int main(int argc, char const *argv[]){

	FILE *entrada, *saida;
	
	entrada = fopen(ENTRADA, "r");
	
	//assert(entrada!=NULL);

	//Criacao das Listas de Entidades
	C_list** c;
	(c)=(C_list**) malloc(sizeof(C_list));
	
	G_list** g;
	g=(G_list**) malloc(sizeof(G_list));

	I_list** i;
	i=(I_list**) malloc(sizeof(I_list));
		if ((*i) == NULL)
			printf ("\n\ntreta");

	A_list** a;
	a=(A_list**) malloc(sizeof(A_list));

	printf("Declarei\n");

	// Preenchimento das listas a partir da entrada .txt
	build_all(entrada,c,g,i,a);
	printf("Build all\n");
	fclose(entrada);


	print_lists(c,g,i,a); // Mostrando o conteudo das listas de entidades.
	//assert(out == FUNCTION_OK);
	printf("Printei Listas\n");

	destroy_all(c,g,a,i);
	printf("Destroy\n");

	saida = fopen(SAIDA, "w");
	fclose(saida);

	printf("End of Execution\n");
	return 0;
}
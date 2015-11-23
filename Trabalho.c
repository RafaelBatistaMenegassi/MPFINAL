#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//#include "includes/mod_def/essential_defs.h"
//#include "includes/mod_def/errorcodes.h"

#include "includes/mod_construcao.h"

#define ENTRADA "includes/teste.txt"
#define SAIDA "log.txt"

int main(int argc, char const *argv[]){

	FILE *entrada, *saida;
	
	entrada = fopen(ENTRADA, "r");
	
	assert(entrada != NULL);

	/*
	
		float **float_values;
		//allocate memory for rows
		float_values = (float**)malloc(4 *sizeof(float*));
		//for each row allocate memory for columns
		for(int i=0; i<4; i++)
			{
		   *(float_values+i) = (float*)malloc(3 *sizeof(float));
			}

	*/
	//Criacao das Listas de Entidades
	C_list** c;
	
	(c)=(C_list**) malloc(sizeof(C_list*));
	(*c)=(C_list*) malloc(sizeof(C_list));
	assert(c != NULL);
	(*c)->next=NULL;
	assert( ((*c)->next) == NULL );
	printf("Passei o assert.\n");

	G_list** g;
	g=(G_list**) malloc(sizeof(G_list*));
	(*g)=(G_list*) malloc(sizeof(G_list));
	assert(g != NULL);
	(*g)->next=NULL;
	assert( ((*g)->next) == NULL );

	I_list** i;
	i=(I_list**) malloc(sizeof(I_list*));
	(*i)=(I_list*) malloc(sizeof(I_list));
	assert(i != NULL);
	(*i)->next=NULL;
	assert( ((*i)->next) == NULL );

	A_list** a;
	a=(A_list**) malloc(sizeof(A_list*));
	(*a)=(A_list*) malloc(sizeof(A_list));
	assert(a != NULL);
	(*a)->next=NULL;
	assert( ((*a)->next) == NULL );

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
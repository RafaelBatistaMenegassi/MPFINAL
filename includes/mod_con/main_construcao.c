#include <stdio.h>
#include <stdlib.h>

#include "mod_construcao.h"


int main(int argc, char const *argv[]){

	
	FILE* ptr= fopen("teste.txt","r");
	
	G_list** g;
	g=(G_list**) malloc(sizeof(G_list));


	C_list** c;
	(c)=(C_list**) malloc(sizeof(C_list));
	//(*c)=(C_list*) malloc(sizeof(C_list));	// <-- Isso se chama desespero. Ignore.
	//(*c)->next=NULL;

	A_list** a;
	a=(A_list**) malloc(sizeof(A_list));

	I_list** i;
	i=(I_list**) malloc(sizeof(I_list));



	
	build_all(ptr,c,g,i,a);	// ESSA BUILD_ALL eh uma moça de coragem. Faz a porra toda e ao fim estas listas estarao preenchidinhas. Ai ai

	printf("Buildei tudo.\n");
	//Aqui imprimimos a lista inteira so pra ter certeza q tudo esta certo.

	print_lists(c,g,i,a);	// ATENCAO GRILÁO - - - Afuncao print_listas imprime as listas e libera a memoria conforme vai printando. Veja se esta certo p favor
	/*
	for(aux=i; (*aux)->next != NULL; (*aux)=(*aux)->next){
		printf("Interconexao: %s xstartpos: %d  ystartpos: %d  xfinalpos: %d  yfinalpos: %d maxcapacity: %d faultchance: %.2f timemain: %d costmain: %d \n", (*aux)->current->nome,(*aux)->current->x_start_pos, (*aux)->current->y_start_pos, (*aux)->current->x_final_pos, (*aux)->current->y_final_pos, (*aux)->current->max_capacity, (*aux)->current->fault_chance, (*aux)->current->time_main, (*aux)->current->cost_main);
		free((*aux)->current);
		free(*aux);

	}
	*/
	printf("Retorno da funcao: %s\n" , (*c)->current->nome );
	
	int grilao = destroy_all(c,g,a,i);

	printf("Retorno da funcao: %d\n" ,grilao );

	//if( ((*c) == NULL) && ((*g)== NULL) && ((*a)== NULL ) &&  ((*i)== NULL )  ){
	if( (*c) == NULL)
		printf(" LIBERA - Function OK\n");
	else printf("NOME: %s", (*c)->current->nome);
	

	fclose(ptr);

	printf("End of Execution\n");
	return 0;
}

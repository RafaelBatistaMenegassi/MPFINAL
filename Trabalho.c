#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

//#include "includes/mod_def/essential_defs.h"
//#include "includes/mod_def/errorcodes.h"

#include "includes/mod_con/mod_construcao.h"
#include "includes/mod_process/mod_process.h"

#define ENTRADA "includes/teste.txt"
#define SAIDA "log.txt"

int main(int argc, char const *argv[]){

	FILE *entrada, *saida;
	
	entrada = fopen(ENTRADA, "r");
	
	G_list* g;
	g=(G_list*) malloc(sizeof(G_list));
	g=NULL;

	C_list* c;
	c=(C_list*) malloc(sizeof(C_list));
	c = NULL;

	A_list* a;
	a=(A_list*) malloc(sizeof(A_list));
	a = NULL;

	I_list* i;
	i=(I_list*) malloc(sizeof(I_list));
	i = NULL;

	assert( (i == NULL)  && (g == NULL) && (c == NULL) &&(a == NULL) ); // Assertiva para verificar a inicializacao correta das listas de entidades.

	printf("Passei no assert - Declarei\n");
	

	build_all(entrada,&c,&g,&i,&a);	// ESSA BUILD_ALL eh uma moça de coragem. Faz a porra toda e ao fim estas listas estarao preenchidinhas. Ai ai
	printf("Build All ok\n");

	print_lists(&c,&g,&i,&a);
	

	fclose(entrada);

	

	//for (g_aux = g; g_aux->next != NULL; g_aux = g_aux->next)
		//weave ((void**) &g_aux, 'G', &c, &a, &i); //void g e G são os únicos termos variáveis na função. c, a e i poderiam muito bem ser variáveis globais para manter a data universal.


	saida = fopen(SAIDA, "w");
	
	printf("\n\n-------LOG DE ATIVIDADES-------\n\n");

	log_run(saida,&c,&g,&i,&a);

	/*

		Tempo total da simulação:  20 segundos 
		Custo total na simulação:  160000 
		Total de geradores: 5 
		Energia total  gerada: 15000 
		Total de cidades : 10 
		Energia total gasta pelas cidades: 10000 
		Tamanho total das interconexões: 100 km 
		Número de falhas nas interconexões: 3 
		Número de cidades que ficaram com menos recurso que o necessário: 3 
		Tempo que ficaram sem recurso: 60 segundos 
		Número de cidades que ficaram com menos de 30% dos recursos : 1  
		Tempo que ficaram com menos de 30% de recurso: 20 segundos   

	*/

	fclose(saida);


	destroy((void**) &g, 'G');
	destroy((void**) &c, 'C');
	destroy((void**) &a, 'A');
	destroy((void**) &i, 'I');



	printf("\nEntidades Destruidas\n");




	printf("End of Execution\n");
	return 0;
}
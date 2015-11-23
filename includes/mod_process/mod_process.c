#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef FUNCTION_OK
#include "../mod_def/errorcodes.h"
#endif

#ifndef NAMEMAX
#include "../mod_def/essential_defs.h"
#endif


int log_run(FILE* ptr, C_list** c, G_list** g, I_list** i, A_list** a){

	/*	Nesta etapa, Fase 1, so incluiremos no log os fatores que podem ser calculados 
		sem a necessidade de simulacao. Merci à tous.

		-Total de geradores
		-Energia total  gerada
		-Total de cidades 
		-Energia total gasta pelas cidades
		-Tamanho total das interconexões em km

	*/

	// Variaveis para Calculos
	G_list* auxG;
	int numG = 0;
	int energiaTotal=0;

	C_list* auxC;
	int numC = 0;
	int energiaGastaTotal = 0;

	I_list* auxI;
	int comprimento = 0;

	// Calculos e geracao do relatorio



	for(auxG= (*g); auxG != NULL; auxG=auxG->next){
		numG++;
		energiaTotal+=auxG->current->production;

	}
	printf("Total de Geradores: %d\nEnergia Total Gerada: %d\n", numG ,energiaTotal);
	fprintf(ptr,"-------RELATORIO DE ATIVIDADES-------\n\n\nTotal de Geradores: %d\nEnergia Total Gerada: %d\n", numG, energiaTotal );



	for(auxC= (*c); auxC != NULL; auxC=auxC->next){
		numC++;
		energiaGastaTotal+=auxC->current->cost;
	}
	printf("Total de Cidades: %d\nEnergia Total Gasta Pelas Cidades: %d\n", numC ,energiaGastaTotal);
	fprintf(ptr,"Total de Geradores: %d\nEnergia Total Gasta Pelas Cidades: %d\n", numC, energiaGastaTotal );



	for(auxI= (*i); auxI != NULL; auxI=auxI->next){
		comprimento+= sqrt( pow( (double) ((auxI->current->x_start_pos) - (auxI->current->x_final_pos)) , 2 ) + pow( (double)( (auxI->current->y_start_pos) - (auxI->current->y_final_pos) ) , 2 ) );
	}
	printf("Tamanho Total de Interconexoes: %d km\n", comprimento);
	fprintf(ptr, "Tamanho Total de Interconexoes: %d km\n", comprimento);

	printf("FIM DO RELATORIO\n");
	fprintf(ptr, "FIM DO RELATORIO\n");


	return FUNCTION_OK;

}


int print_lists(C_list** c, G_list** g, I_list** i, A_list** a){

	/* Imprime e libera as listas de uma só vez. */

	C_list* aux1;
	G_list* aux2;
	A_list* aux3;
	I_list* aux4;

	printf("\nLista de Entidades:\n\nCidades:\n");
	for ( aux1= (*c) ; aux1 != NULL ; aux1=aux1->next){
		printf("Cidade: %s xpos: %d  ypos: %d  resources: %d  \n", aux1->current->nome,aux1->current->x_pos, aux1->current->y_pos, aux1->current->cost);
		//free(aux1->current);
		//freeaux1);
	}
	printf("\nGeradores:\n");
	for ( (aux2)= (*g) ; aux2 != NULL ; aux2=aux2->next){
		printf("Gerador: %s xpos: %d  ypos: %d  Production: %d  Cost: %d\n", aux2->current->nome,aux2->current->x_pos, aux2->current->y_pos, aux2->current->production, aux2->current->cost);
		//free(aux2->current);
		//freeaux2);
	}
	printf("\nAdaptadores:\n");
	for ( (aux3) = (*a) ; aux3 != NULL ; aux3=aux3->next){
		printf("Adaptador: %s xpos: %d  ypos: %d  \n", aux3->current->nome,aux3->current->x_pos, aux3->current->y_pos);
		//free(aux3->current);
		//freeaux3);
	}
	printf("\nInterconexoes:\n");
	for ( (aux4)= (*i) ; aux4 != NULL ; aux4=aux4->next){
		printf("Interconexao: %s xstartpos: %d  ystartpos: %d  xfinalpos: %d  yfinalpos: %d maxcapacity: %d faultchance: %.2f timemain: %d costmain: %d \n", aux4->current->nome,aux4->current->x_start_pos, aux4->current->y_start_pos, aux4->current->x_final_pos, aux4->current->y_final_pos, aux4->current->max_capacity, aux4->current->fault_chance, aux4->current->time_main, aux4->current->cost_main);
		//free(aux4->current);
		//freeaux4);
	}

	return FUNCTION_OK;
}
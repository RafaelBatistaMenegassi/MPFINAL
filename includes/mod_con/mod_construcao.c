#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../mod_def/essential_defs.h"
#include "../mod_def/errorcodes.h"



//int push_list(C_list**,C_type*);

int c_build(char* linha, C_list** output ){

	char *field;
	C_list *aux_list;

	if (linha == NULL) /*Linha da entrada vazia, retorna-se erro*/
		return ERROR_STREAM;

	aux_list 			= (C_list*) malloc(sizeof(C_list));
	aux_list->current	= (C_type*) malloc(sizeof(C_type));
	aux_list->next 		= NULL;
	


		/*	NOTA IMPORTANTE: este else é basicamente o único lugar da função, a princípio, onde alterações
				mais 'drásticas' deverão ser feitas para adaptá-la para outros tipos de entidades. de resto,
				apenas mudança de uma letra ou outra para redefinição de tipo, não mais que isso.
		
			C  nome_cidade   pos_x  pos_y  recurso_necessario 

		*/


		field = strtok(linha, " ");
			/*	strcpy(aux->matric, field);
				Caractere que define o tipo de entidade: inútil para a base de dados, uma vez já
				utilizada para chamar a função
			*/
		
		field = strtok(NULL, " ");
			strcpy(aux_list->current->nome, field);
				//fills out name field

		field = strtok(NULL, " ");
			aux_list->current->x_pos = atoi (field);
				//Defines position in x axis

		field = strtok(NULL, " ");
			aux_list->current->y_pos = atoi (field);
				//Defines position in y axis

		field = strtok(NULL, " ");
			aux_list->current->cost = atoi (field);
				//Defines regular resource cost

		aux_list->next= (*output);
		(*output)=aux_list;

	/*
	if ((*output) == NULL){
		(*output) = aux_list;
	}
	else{
		(*output)->next = aux_list;
		(*output) = (*output)->next;
	}
	*/

	//printf("Cidade: %s xpos: %d  ypos: %d  resources: %d  \n", (*output)->current->nome,(*output)->current->x_pos, (*output)->current->y_pos, (*output)->current->cost);

	return FUNCTION_OK;
}

int g_build(char* linha, G_list** output){

	char *field;
	G_list *aux_list;


	aux_list 			= (G_list*) malloc(sizeof(G_list));
	aux_list->current	= (G_type*) malloc(sizeof(G_type));
	aux_list->next 		= NULL;



	if (linha == NULL) /*Linha da entrada vazia, retorna-se erro*/
		return ERROR_STREAM;
	else{

		/*	NOTA IMPORTANTE: este else é basicamente o único lugar da função, a princípio, onde alterações
				mais 'drásticas' deverão ser feitas para adaptá-la para outros tipos de entidades. de resto,
				apenas mudança de uma letra ou outra para redefinição de tipo, não mais que isso.
		
			G  nome_gerador   pos_x  pos_y  recurso_produzido custo_gerador 

		*/


		field = strtok(linha, " ");
			/*	strcpy(aux->matric, field);
				Caractere que define o tipo de entidade: inútil para a base de dados, uma vez já
				utilizada para chamar a função. Proximos tokkens conterao as informacoes necessarias.
			*/
		
		field = strtok(NULL, " ");
			strcpy(aux_list->current->nome, field);
				//fills out name field

		field = strtok(NULL, " ");
			aux_list->current->x_pos = atoi (field);
				//Defines position in x axis

		field = strtok(NULL, " ");
			aux_list->current->y_pos = atoi (field);
				//Defines position in y axis

		field = strtok(NULL, " ");
			aux_list->current->production = atoi (field);
				//Defines regular resource produced
	

		field = strtok(NULL, " ");
			aux_list->current->cost = atoi (field);
				//Defines regular generator cost
	}
	aux_list->current->out= NULL;

	aux_list->next= (*output);
	(*output)=aux_list;


	//printf("Gerador: %s xpos: %d  ypos: %d  Production: %d  Cost: %d\n", (*output)->current->nome,(*output)->current->x_pos, (*output)->current->y_pos, (*output)->current->production, (*output)->current->cost);
	
	return FUNCTION_OK;

}

int a_build(char* linha, A_list** output){

	char *field;
	
	A_list *aux_list;
		/*	aux_list será uma "lista" de entidades de geradores. Vamos manipula-la e inserir a entidade especificamente
			caracterizada na linha que usamos como entrada da funcao.
		*/
	
	

	//aux_list 		= (*output); 
	aux_list 		= (A_list*)malloc(sizeof(A_list));
	aux_list->current	= (A_type*)malloc(sizeof(A_type));
	/*//aux->next 	= NULL;   Por que teria membro next em aux? Griláo...  */
	
	if (linha == NULL) /*Linha da entrada vazia, retorna-se erro*/
		return ERROR_STREAM;
	else{

		/*	NOTA IMPORTANTE: este else é basicamente o único lugar da função, a princípio, onde alterações
				mais 'drásticas' deverão ser feitas para adaptá-la para outros tipos de entidades. de resto,
				apenas mudança de uma letra ou outra para redefinição de tipo, não mais que isso.
		
			A  nome_adaptador   pos_x  pos_y  
			A indica que é um adaptador na pos_x e pos_y são posições em quilômetros que também corresponde as posições onde o adaptador será mostrado na interface. 

		*/


		field = strtok(linha, " ");
			/*	strcpy(aux->matric, field);
				Caractere que define o tipo de entidade: inútil para a base de dados, uma vez já
				utilizada para chamar a função. Proximos tokkens conterao as informacoes necessarias.
			*/
		
		field = strtok(NULL, " ");
			strcpy(aux_list->current->nome, field);
				//fills out name field

		field = strtok(NULL, " ");
			aux_list->current->x_pos = atoi (field);
				//Defines position in x axis

		field = strtok(NULL, " ");
			aux_list->current->y_pos = atoi (field);
				//Defines position in y axis


	}

	aux_list->current->status = 0;

	aux_list->current->out = NULL;

	//A_list	*aux1 = NULL;
	//C_list	*aux2 = NULL;



	// Alocar o elemento a ser inserido no fim da lista...
	//	aux1 = (A_list*) malloc(sizeof(A_list));

	aux_list->next= (*output);
	(*output)=aux_list;

	//printf("Adaptador: %s xpos: %d  ypos: %d  \n", (*output)->current->nome,(*output)->current->x_pos, (*output)->current->y_pos);
	return FUNCTION_OK;

}

int i_build(char* linha, I_list** output){

	char *field;
	
	I_list *aux_list;
		/*	aux_list será uma "lista" de entidades de interconexões. Vamos manipula-la e inserir a entidade especificamente
			caracterizada na linha que usamos como entrada da funcao.
		*/


	//aux_list 		= (*output); 
	aux_list 		= (I_list*) malloc(sizeof(I_list));
	aux_list->current	= (I_type*) malloc(sizeof(I_type));
	/* aux->next 	= NULL;   Por que teria membro next em aux? Griláo...  */
	
	if (linha == NULL) /*Linha da entrada vazia, retorna-se erro*/
		return ERROR_STREAM;
	else{

		/*	NOTA IMPORTANTE: este else é basicamente o único lugar da função, a princípio, onde alterações
				mais 'drásticas' deverão ser feitas para adaptá-la para outros tipos de entidades. de resto,
				apenas mudança de uma letra ou outra para redefinição de tipo, não mais que isso.
		
			I nome_interconexao(char) pos_inic_x(int) pos_inic_y(int) pos_final_x(int) pos_final_y(int)
			capacidade_max(int) chance_falha(float) tempo_conserto(int) custo_do_conserto(int)

		*/

		/* Calculando aleatoriamente a chance de falha da interconexão */

		/*		
		float num;
		float chance_falha = 0.01;
		srand(1); // só é executado uma vez na simulacao
		
		num = ((float)rand())/RAND_MAX;
		if ( (chance_falha > 0) && (chance_falha >=num) ) 
			printf("Falha!!\n");;
		*/


		/* Fim de cálculo de chance de falha */
		
		/* Início de geração de entidade em ponteiro para struct */

		field = strtok(linha, " ");
			/*	
				Caractere que define o tipo de entidade: inútil para a base de dados, uma vez já
				utilizada para chamar a função. Proximos tokens conterao as informacoes necessarias.
			*/
		
		field = strtok(NULL, " ");
			strcpy(aux_list->current->nome, field);
				/* Fills out name field */

		field = strtok(NULL, " ");
			aux_list->current->x_start_pos = atoi (field);
				/* Defines initial position in x axis */

		field = strtok(NULL, " ");
			aux_list->current->y_start_pos = atoi (field);
				/* Defines initial position in y axis */
				
		field = strtok(NULL, " ");
			aux_list->current->x_final_pos = atoi (field);
				/* Defines final position in x axis */

		field = strtok(NULL, " ");
			aux_list->current->y_final_pos = atoi (field);
				/* Defines final position in y axis */

		field = strtok(NULL, " ");
			aux_list->current->max_capacity = atoi (field);
				/* Defines max capacity endured by the entity */
				
		field = strtok(NULL, " ");
			sscanf(field,"%f", &(aux_list->current->fault_chance));
			/* Defines the pre-defined chance of failing */
		
		field = strtok(NULL, " ");
			aux_list->current->time_main = atoi (field);
				/* Defines the fixing time */

		field = strtok(NULL, " ");
			aux_list->current->cost_main = atoi (field);
				/* Defines the fixing cost */
	}

	/*
	
	aux_list 			= (C_list*) malloc(sizeof(C_list));
	aux_list->current 	= aux;

	*/

	aux_list->current->adaptador = NULL;

	aux_list->current->cidade = NULL;
	
	//I_list	*aux1 = NULL;
	//C_list	*aux2 = NULL;

	// Alocar o elemento a ser inserido no fim da lista...
	/*aux1 = (I_list*) malloc(sizeof(I_list));

	if(counter[3]==0){	// Aqui indicamos que este eh o primeiro elemento. Logo o ultimo elemento da lista sera NULL de fato.
	(*output)->next=NULL;
	counter[3]=1;
	
	}



	aux1->current = aux_list->current;
	aux1->next = (*output);
	(*output)=aux1;
	*/

	aux_list->next = (*output);
	(*output) = aux_list;

	//printf("Interconexao: %s xstartpos: %d  ystartpos: %d  xfinalpos: %d  yfinalpos: %d maxcapacity: %d faultchance: %.2f timemain: %d costmain: %d \n", (*output)->current->nome,(*output)->current->x_start_pos, (*output)->current->y_start_pos, (*output)->current->x_final_pos, (*output)->current->y_final_pos, (*output)->current->max_capacity, (*output)->current->fault_chance, (*output)->current->time_main, (*output)->current->cost_main);
	
	return FUNCTION_OK;

}

int destroy(void** target, char mode){
	G_list* input_g = NULL;
	C_list* input_c = NULL;
	A_list* input_a = NULL;
	I_list* input_i = NULL;


	switch (mode){
		case 'G':

			input_g = * (G_list**) target;			//TYPECASTING TÁ ROLANDO!! não mexa nessa linha

			if (input_g == NULL)
				return ERROR_STREAM;				//Evita segfault por conta da chamada seguinte



			destroy ((void**) &(input_g->next), 'G');

			if (input_g->current == NULL)
				return ERROR_DATA;					
			

			free(input_g->current->nome);
			free(input_g->current);
			free(input_g);

		

			input_g = NULL;
			break;

			//Os casos abaixo foram apenas copiados do acima (que está funcionando plenamente), caso hajam erros, corrigir

			//caso C está problemático. o resto está bem
		case 'C':
			input_c = * (C_list**) target;			//TYPECASTING TÁ ROLANDO!! não mexa nessa linha

			if (input_c == NULL)
				return ERROR_STREAM;				//Evita segfault por conta da chamada seguinte
			
			
			//printf("free no C\n");
			destroy ((void**) &(input_c->next), 'C');

			if (input_c->current == NULL)
				return ERROR_DATA;					
			

			free(input_c->current->nome);
			free(input_c->current);
			free(input_c);
			input_c = NULL;

			
			break;


		case 'A':
			input_a = * (A_list**) target;			//TYPECASTING TÁ ROLANDO!! não mexa nessa linha

			if (input_a == NULL)
				return ERROR_STREAM;				//Evita segfault por conta da chamada seguinte

			destroy ((void**) &(input_a->next), 'A');

			if (input_a->current == NULL)
				return ERROR_DATA;					
			

			free(input_a->current->nome);
			free(input_a->current);
			free(input_a);
			input_a = NULL;

			//printf("free no A\n");
			break;

		case 'I':
			input_i = * (I_list**) target;			//TYPECASTING TÁ ROLANDO!! não mexa nessa linha

			if (input_i == NULL)
				return ERROR_STREAM;				//Evita segfault por conta da chamada seguinte

			destroy ((void**) &(input_i->next), 'I');

			if (input_i->current == NULL)
				return ERROR_DATA;					
			

			free(input_i->current->nome);
			free(input_i->current);
			free(input_i);
			input_i = NULL;

			//printf("free no I\n");
			break;

		default: return ERROR_FORMAT;
	}

	return FUNCTION_OK;
}

int build_all(FILE* stream, C_list** c, G_list** g, I_list** i, A_list** a ){
	
	char linha[120];
	
	/*
	C_list* c_aux = *c;
	C_list* c_aux2 = *c;

	G_list* g_aux = *g;
	A_list* a_aux = *a;
	I_list* i_aux = *i;
	*/
		
	while(( fgets(linha, 120, stream)) != NULL){

		
		//printf("%s\n", linha );
		
		switch (linha[0]) {

			case 'C':
				// Pegamos a linha e inserimos a entidade na lista
				c_build(linha,c);
				break;

			case 'G':
				// Pegamos a linha e inserimos a entidade na lista
				g_build (linha, g);
				
				break;
				
			case 'I':
				// Pegamos a linha e inserimos a entidade na lista
				i_build (linha, i);
				
				break;

			case 'A':
				// Pegamos a linha e inserimos a entidade na lista
				a_build (linha, a);
				
				break;

			default:
				return ERROR_STREAM;
		}

	}


	return FUNCTION_OK;
}

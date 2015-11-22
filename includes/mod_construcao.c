#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./mod_def/essential_defs.h"
#include "./mod_def/errorcodes.h"



//int push_list(C_list**,C_type*);

static int counter[] = {0,0,0,0};	// Variavel global para sabermos se estamos na primeira insercao na lista de cada respectiva entidade


int build_all(FILE* stream, C_list** c, G_list** g, I_list** i, A_list** a ){
	
	char linha[120];
	
	//C_list *c_aux1, *c_aux2;

	

		
	while(( fgets(linha, 120, stream)) != NULL){

		
		//printf("%s\n", linha );
		
		switch (linha[0]) {

			case 'C':
				// Pegamos a linha e inserimos a entidade na lista
				c_build (linha, c );
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

int c_build(char* linha, C_list** output ){

	char *field;
	/*C_type *aux;   <--- variable no longer used */
	C_list *aux_list;

		/* ----------------- TEMOS SERIAMENTE QUE MUDAR ESTE COMENTARIO AQUI EM BAIXO ---------------------------------*/

		/*	aux será uma struct do tipo _type, ao invés de list, pois assim a sintaxe de preenchimento
				da struct se torna mais simples e menos propensa a erros. dessa forma, se torna necessário
				alocar uma struct do tipo _list ao final da função, que seria necessário de qualquer forma
			aux_list será o valor que (*output) receberá
		*/
	
	

	//aux_list 		= (*output); 
	aux_list 		= (C_list*) malloc(sizeof(C_list));
	aux_list->current	= (C_type*) malloc(sizeof(C_type));
	/*  aux->next 	= NULL;   Por que teria membro next em aux? Griláo...  Acabamos abolindo essa variavel :( */
	
	if (linha == NULL) /*Linha da entrada vazia, retorna-se erro*/
		return ERROR_STREAM;
	else{

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
	}


	aux_list->next 		= NULL;

	//push_list(output, aux_list->current);  <--- se ainda houvesse funcao push_list ela ficaria aqui

		C_list	*aux1 = NULL;
		//C_list	*aux2 = NULL;



		// Alocar o elemento a ser inserido no fim da lista...   GRIALAO!!!!!!!!! Passei a funcionalidade de push_lista para esses codigos aqui embaixo...
		aux1 = (C_list*) malloc (sizeof(C_list));

			if(counter[0]==0){	// Aqui indicamos que este eh o primeiro elemento. Logo o ultimo elemento da lista sera NULL de fato.
				(*output)->next=NULL;
				counter[0]=1;
				}



			aux1->current = aux_list->current;
			aux1->next = (*output);
			(*output)=aux1;

					// Push_lista vinha ate aqui anteriormente.

	printf("Cidade: %s xpos: %d  ypos: %d  resources: %d  \n", (*output)->current->nome,(*output)->current->x_pos, (*output)->current->y_pos, (*output)->current->cost);

	return FUNCTION_OK;
}

int g_build(char* linha, G_list** output){

	char *field;
	
	G_list *aux_list;
		/*	aux_list será uma "lista" de entidades de geradores. Vamos manipula-la e inserir a entidade especificamente
			caracterizada na linha que usamos como entrada da funcao.
		*/
	
	

	aux_list 		= (*output); 
	aux_list 		= (G_list*) malloc(sizeof(G_list));
	aux_list->current	= (G_type*) malloc(sizeof(G_type));
	/*//aux->next 	= NULL;   Por que teria membro next em aux? Griláo...  */
	
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

	/*aux_list 			= (C_list*) malloc(sizeof(C_list));
	aux_list->current 	= aux;

	*/
	
	// Alocar o elemento a ser inserido no fim da lista...   GRIALAO!!!!!!!!! Passei a funcionalidade de push_lista para esses codigos aqui embaixo...
	G_list* aux1 = NULL;
	aux1 = (G_list*) malloc (sizeof(G_list));

		if(counter[1]==0){	// Aqui indicamos que este eh o primeiro elemento. Logo o ultimo elemento da lista sera NULL de fato.
			(*output)->next=NULL;
			counter[1]=1;
			}



		aux1->current = aux_list->current;
		aux1->next = (*output);
		(*output)=aux1;	



	printf("Gerador: %s xpos: %d  ypos: %d  Production: %d  Cost: %d\n", (*output)->current->nome,(*output)->current->x_pos, (*output)->current->y_pos, (*output)->current->production, (*output)->current->cost);
	return FUNCTION_OK;

}

int a_build(char* linha, A_list** output){

	char *field;
	
	A_list *aux_list;
		/*	aux_list será uma "lista" de entidades de geradores. Vamos manipula-la e inserir a entidade especificamente
			caracterizada na linha que usamos como entrada da funcao.
		*/
	
	

	aux_list 		= (*output); 
	aux_list 		= (A_list*) malloc(sizeof(A_list));
	aux_list->current	= (A_type*) malloc(sizeof(A_type));
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

	A_list	*aux1 = NULL;
		//C_list	*aux2 = NULL;



		// Alocar o elemento a ser inserido no fim da lista...   GRIALAO!!!!!!!!! Passei a funcionalidade de push_lista para esses codigos aqui embaixo...
		aux1 = (A_list*) malloc (sizeof(A_list));

			if(counter[2]==0){	// Aqui indicamos que este eh o primeiro elemento. Logo o ultimo elemento da lista sera NULL de fato.
				(*output)->next=NULL;
				counter[2]=1;
				}

			aux1->current = aux_list->current;
			aux1->next = (*output);
			(*output)=aux1;

	printf("Adaptador: %s xpos: %d  ypos: %d  \n", (*output)->current->nome,(*output)->current->x_pos, (*output)->current->y_pos);
	return FUNCTION_OK;

}

int i_build(char* linha, I_list** output){

	char *field;
	
	I_list *aux_list;
		/*	aux_list será uma "lista" de entidades de interconexões. Vamos manipula-la e inserir a entidade especificamente
			caracterizada na linha que usamos como entrada da funcao.
		*/


	aux_list 		= (*output); 
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
	
	I_list	*aux1 = NULL;
		//C_list	*aux2 = NULL;

		// Alocar o elemento a ser inserido no fim da lista...   GRIALAO!!!!!!!!! Passei a funcionalidade de push_lista para esses codigos aqui embaixo...
		aux1 = (I_list*) malloc (sizeof(I_list));

			if(counter[3]==0){	// Aqui indicamos que este eh o primeiro elemento. Logo o ultimo elemento da lista sera NULL de fato.
				(*output)->next=NULL;
				counter[3]=1;
				}

			aux1->current = aux_list->current;
			aux1->next = (*output);
			(*output)=aux1;

	printf("Interconexao: %s xstartpos: %d  ystartpos: %d  xfinalpos: %d  yfinalpos: %d maxcapacity: %d faultchance: %.2f timemain: %d costmain: %d \n", (*output)->current->nome,(*output)->current->x_start_pos, (*output)->current->y_start_pos, (*output)->current->x_final_pos, (*output)->current->y_final_pos, (*output)->current->max_capacity, (*output)->current->fault_chance, (*output)->current->time_main, (*output)->current->cost_main);
	
	return FUNCTION_OK;

}


int print_lists(C_list** c, G_list** g, I_list** i, A_list** a){

	/* Imprime e libera as listas de uma só vez. */

	C_list** aux1;
	G_list** aux2;
	A_list** aux3;
	I_list** aux4;

	printf("\nLista de Cidades\n");
	for ( aux1= (c) ; (*aux1)->next != NULL ; (*aux1)=(*aux1)->next){
		printf("Cidade: %s xpos: %d  ypos: %d  resources: %d  \n", (*aux1)->current->nome,(*aux1)->current->x_pos, (*aux1)->current->y_pos, (*aux1)->current->cost);
		free((*aux1)->current);
		free(*aux1);
	}
	printf("\nLista de Geradores\n");
	for ( (aux2)= (g) ; (*aux2)->next != NULL ; (*aux2)=(*aux2)->next){
		printf("Gerador: %s xpos: %d  ypos: %d  Production: %d  Cost: %d\n", (*aux2)->current->nome,(*aux2)->current->x_pos, (*aux2)->current->y_pos, (*aux2)->current->production, (*aux2)->current->cost);
		free((*aux2)->current);
		free(*aux2);
	}
	printf("\nLista de Adaptadores\n");
	for ( (aux3) = (a) ; (*aux3)->next != NULL ; (*aux3)=(*aux3)->next){
		printf("Adaptador: %s xpos: %d  ypos: %d  \n", (*aux3)->current->nome,(*aux3)->current->x_pos, (*aux3)->current->y_pos);
		free((*aux3)->current);
		free(*aux3);
	}
	printf("\nLista de Interconexoes\n");
	for ( (aux4)= (i) ; (*aux4)->next != NULL ; (*aux4)=(*aux4)->next){
		printf("Interconexao: %s xstartpos: %d  ystartpos: %d  xfinalpos: %d  yfinalpos: %d maxcapacity: %d faultchance: %.2f timemain: %d costmain: %d \n", (*aux4)->current->nome,(*aux4)->current->x_start_pos, (*aux4)->current->y_start_pos, (*aux4)->current->x_final_pos, (*aux4)->current->y_final_pos, (*aux4)->current->max_capacity, (*aux4)->current->fault_chance, (*aux4)->current->time_main, (*aux4)->current->cost_main);
		free((*aux4)->current);
		free(*aux4);
	}
}

//Main para testes dos arcabouços automatizados de teste...




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

	fclose(ptr);

	printf("End of Execution\n");
	return 0;
}


/*  GRILAO , comentei essa funcao pois ela ficou bem simples e agora esta sendo inserido em cada build individualmente. O que vc acha?*/

/*int push_list  (C_list ** target, 	//Entidade tipo _list, onde será inserido o elemento
		 C_type*  element)	{

		// push_list(*output, aux_list->current);
	
		C_list	*aux1 = NULL;
		C_list	*aux2 = NULL;



				//alocar o elemento a ser inserido
				aux1 = (C_list*) malloc (sizeof(C_list));

					if(counterC==0){
						printf("Counter era 0\n");
						(*target)->next=NULL;
						counterC=1;
						printf("%d\n", counterC );
					}



					aux1->current = element;
					aux1->next = (*target);
					(*target)=aux1;

					

					/*
					aux2 = (*target);


					
					printf("ta deliciosa essa suruba\n");

					while ( (aux2)->next != NULL){
					
						(aux2) = (aux2)->next;
					
					}
					printf("kbei a suruba\n");
					(aux2)->next = (aux1);
				


		return FUNCTION_OK;

}

*/

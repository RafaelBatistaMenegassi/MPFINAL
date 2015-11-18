/*

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./mod_def/essential_defs.h"
#include "./mod_def/errorcodes.h"

//#include "essential_defs.h"
//#include "errorcodes.h"

/*Veja se mudou MotherFucker!

*/


int build_all(FILE* stream, C_list** c, G_list** g, I_list** i, A_list** a ){
	
	char linha[120];
	
	printf("Comecei os trabalhos na build all\n");

	while(( fgets(linha, 120, stream)) != NULL){

		
		printf("%s\n", linha );
		
		switch (linha[0]) {

			case 'C':
				// Pegamos a linha e inserimos a entidade na lista
				c_build (linha, c);
				
				break;

			case 'G':
				// Pegamos a linha e inserimos a entidade na lista
				// g_build (linha, g);
				break;
				
			case 'I':
				// Pegamos a linha e inserimos a entidade na lista
				// i_build (linha, i);
				break;

			case 'A':
				// Pegamos a linha e inserimos a entidade na lista
				// a_build (linha, a);
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
		/*	aux será uma struct do tipo _type, ao invés de list, pois assim a sintaxe de preenchimento
				da struct se torna mais simples e menos propensa a erros. dessa forma, se torna necessário
				alocar uma struct do tipo _list ao final da função, que seria necessário de qualquer forma
			aux_list será o valor que (*output) receberá
		*/
	
	

	aux_list 		= (*output); 
	aux_list 		= (C_list*) malloc(sizeof(C_list));
	aux_list->current	= (C_type*) malloc(sizeof(C_type));
	/*//aux->next 	= NULL;   Por que teria membro next em aux? Griláo...  */
	
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

	/*aux_list 			= (C_list*) malloc(sizeof(C_list));
	aux_list->current 	= aux;

	*/

	aux_list->next 		= NULL;

	(*output) = aux_list;
	return FUNCTION_OK;
}

int g_build(char* linha, G_list** output){

	char *field;
	
	G_list *aux_list;
		/*	aux_list será uma "lista" de entidades de geradores. Vamos manipula-la e inserir a entidade especificamente
			caracterizada na linha que usamos como entrada da funcao.
		*/
	
	

	aux_list 		= (*output); 
	aux_list 		= (C_list*) malloc(sizeof(C_list));
	aux_list->current	= (C_type*) malloc(sizeof(C_type));
	/*//aux->next 	= NULL;   Por que teria membro next em aux? Griláo...  */
	
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

	/*aux_list 			= (C_list*) malloc(sizeof(C_list));
	aux_list->current 	= aux;

	*/
	
	aux_list->next 		= NULL;

	(*output) = aux_list;
	return FUNCTION_OK;

}
//Main para testes dos arcabouços automatizados de teste...

int main(int argc, char const *argv[])
{
	FILE* ptr= fopen("teste.txt","r");
	
	G_list** g;

	C_list** c;
	c=(C_list**) malloc(sizeof(C_list));
		

	A_list** a;

	I_list** i;



	printf("Entrei na build_all\n");
	build_all(ptr,c,g,i,a);
	printf("Sai na build_all\n");
	printf("Cidade: %s xpos: %d  ypos: %d  resources: %d  \n", (*c)->current->nome,(*c)->current->x_pos, (*c)->current->y_pos, (*c)->current->cost);

	fclose(ptr);
	free((*c)->current);
	free(c);

	return 0;
}

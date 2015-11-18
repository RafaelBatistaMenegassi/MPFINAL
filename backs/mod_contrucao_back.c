#include <stdio.h>
#include <stdlib.h>

#include "../mod_def/essential_defs.h"
#include "../mod_def/errorcodes.h"



int build_all(FILE* stream, C_list** c, G_list** g, I_list** i, A_list** a ){
	
	char* linha;

	while(!FEOF(p)){
		fgets(linha, 120, stream);

		switch (linha[0]) {

			case 'C':
				// Pegamos a linha e inserimos a entidade na lista
				// c_build (linha, c);
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
		/*
		int counter = 0;
		char* field;
		char op[3];
		char nome[LINEMAX];
		*/

		// stream no caso especifico nosso, na verdade se chama-se linha e não stream ou joãozinho...

		C_list *aux;
		
		aux = *output;
		aux = (registro*) malloc(sizeof(registro));
		aux->next = NULL;

		if (linha == NULL)
			return ERROR_STREAM;
		else{


			field = strtok(stream, " ");
				strcpy(aux->matric, field);
					//fills out matric field

			while(1){
				field = strtok(NULL, " ");
				if (counter == 0){
					counter++;
					strcpy(nome, field);
				}else if (!strcmp(op, field)){
					break;
				}else 
					strcat(nome,field);
			}
				strcpy(aux->nome, nome);
					//fills out name field

			//field = strtok(NULL, " ");
				aux->op = atoi (field);
					//fills out op field

			field = strtok(NULL, " ");
				strcpy(aux->curso, field);
					//fills out curso field

			field = strtok(NULL, " ");
				aux->turma = field[0];
					//fills out turma field
		}

		(*output) = aux;
		return FUNCTION_OK;
	}

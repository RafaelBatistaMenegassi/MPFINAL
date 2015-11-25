#include <stdio.h>
#include <stdlib.h>

//#include "mod_def/essential_defs.h"
//#include "mod_def/errorcodes.h"
#include "mod_con/mod_construcao.c"
#include "mod_process/mod_process.c"

#define ALLPRINT 	0

#define G_MATCH_I i_seeker->current->x_start_pos == input_g->current->x_pos && i_seeker->current->y_start_pos == input_g->current->y_pos
	/*Macro que significa que um gerador recebeu uma intercon de saída
		Condições para que isso aconteça:
			- X inicial da intercon = X do gerador
			- Y inicial da intercon = Y do gerador
	*/


#define A_MATCH_I i_seeker->current->x_start_pos == input_a->current->x_pos && i_seeker->current->y_start_pos == input_a->current->y_pos
	/*Macro que significa que um adaptador recebeu uma intercon de saída
		Condições para que isso aconteça:
			- X inicial da intercon = X do adaptador
			- Y inicial da intercon = Y do adaptador
	*/

#define I_MATCH_A a_seeker->current->x_pos == input_i->current->x_final_pos && a_seeker->current->y_pos == input_i->current->y_final_pos
	/*Macro que significa que uma intercon recebeu um adaptador de saída
		Condições para que isso aconteça:
			- X do adaptador = X final da intercon
			- Y do adaptador = Y final da intercon
	*/

#define I_MATCH_C c_seeker->current->x_pos == input_i->current->x_final_pos && c_seeker->current->y_pos == input_i->current->y_final_pos
	/*Macro que significa que uma intercon recebeu uma cidade de saída
		Condições para que isso aconteça:
			- X da cidade = X final da intercon
			- Y da cidade = Y final da intercon
	*/







int weave(void** input, char mode,
						C_list** data_c,	//data referente às cidades (para poder fazer a busca)
						A_list** data_a,	//data referente aos adaptadores (para poder fazer a busca)
						I_list** data_i		//data referente às interconexões (para poder fazer a busca)
						){

	G_list* input_g = NULL;
	C_list* input_c = NULL;
	A_list* input_a = NULL;
	I_list* input_i = NULL;
		//variáveis cujo único objetivo é receber o input

	C_list* c_seeker = NULL;
	A_list* a_seeker = NULL;
	I_list* i_seeker = NULL;
		//variáveis de busca

	short int collision = 0;
	short int counter	= 0;
		/*	Variável que verifica se alguma conexão já foi feita nos valores x, y correntes.
				Caso haja mais de uma conexão a ser feita para um mesmo ponto que não seja um
				adaptador, isso caracteriza uma conexão ilegal (a database está corrupta).
				A função retornará um valor de erro e terminará a execução caso isso aconteça.
		*/


	switch (mode){

			//Weave foi chamado sobre um gerador
		case 'G':
			input_g = * (G_list**) input;			//TYPECASTING TÁ ROLANDO!! não mexa nessa linha	

				//search I
			i_seeker = (*data_i);
			while(i_seeker != NULL){	
				//printf("Current Intercon: %s\n", i_seeker->current->nome);
				if (G_MATCH_I){		//if match

						//collision check
					if (collision == 1){
						printf("Colisão, encerrando");
						return ERROR_DATA;
					}else
						collision++;

						//printf opcional
					if (ALLPRINT)
						printf("Conexao estabelecida\n\t\tGerador: \t%s\t// x: \t%d\t y: \t%d\t\n\t\tIntercon: \t%s\t// x: \t%d\t y: \t%d\t\n\n",
							input_g->current->nome, input_g->current->x_pos, input_g->current->y_pos,
							i_seeker->current->nome, i_seeker->current->x_start_pos, i_seeker->current->y_start_pos);

					input_g->current->out = i_seeker->current;		// Estabelecimento da conexão (plug)
					//(*(G_list**) input)->current->out = i_seeker->current;

					//printf("%s => %s\n", (*(G_list**) input)->current->nome, (*(G_list**) input)->current->out->nome);
					/*						
						A linha acima estabelece a conexão necessária entre gerador e intercon.
						A linha abaixo é onde se chamaria recursivamente a função na intercon
							para conclusão do processo de conexão. (weave next)
							Todas as chamadas subsequentes seguem o mesmo raciocínio
					*/
					if (weave ((void**) &i_seeker, 'I', data_c, data_a, data_i) == ERROR_DATA){
						printf ("ERROR DATA CALLING I");
						return ERROR_DATA;
					}
				}
				i_seeker = i_seeker->next;
			}
			break;





			//Weave foi chamado sobre uma interconexão
		case 'I':
			input_i = * (I_list**) input;			//TYPECASTING TÁ ROLANDO!! não mexa nessa linha

				//search A
					//A chance de se terminar em um adaptador é muito maior que em uma cidade, por isso pesquisa-se em A antes.

			a_seeker = (*data_a);
			if (a_seeker == NULL)
				printf ("NÃO HA ADAPTADORES");

			while (a_seeker != NULL){
				/*
				printf("Current Intercon: \t%s\n", input_i->current->nome);
				printf("Current Adaptor: \t%s\n", a_seeker->current->nome);
				*/
				if (I_MATCH_A){		//se intercon estiver ligada a um adaptador
					

										//printf opcional
					if (ALLPRINT)
						printf("Conexao estabelecida\n\t\tIntercon: \t%s\t// x: \t%d\t y: \t%d\t\n\t\tAdaptador: \t%s\t// x: \t%d\t y: \t%d\t\n\n",
							input_i->current->nome, 	input_i->current->x_final_pos, 	input_i->current->y_final_pos,
							a_seeker->current->nome, 	a_seeker->current->x_pos, 		a_seeker->current->y_pos);

					input_i->current->adaptador = a_seeker->current;

						//houve erro na chamada abaixo: checar case 'A'
					if (weave ((void**) &a_seeker, 'A', data_c, data_a, data_i) == ERROR_DATA){
						printf ("ERROR DATA CALLING A");
						return ERROR_DATA;
					}

				}
			a_seeker = a_seeker->next;
			}



				//search C (solve A first)
			c_seeker = (*data_c);
			while (c_seeker != NULL){
				/*
				printf("Current Intercon: \t%s\n", input_i->current->nome);
				printf("Current City: \t%s\n", c_seeker->current->nome);
				*/
				if (I_MATCH_C){		//se intercon estiver ligada a uma cidade
					

										//printf opcional
					if (ALLPRINT)
						printf("Conexao estabelecida\n\t\tIntercon: \t%s\t// x: \t%d\t y: \t%d\t\n\t\tCidade: \t%s\t// x: \t%d\t y: \t%d\t\n\n",
							input_i->current->nome, input_i->current->x_final_pos, input_i->current->y_final_pos,
							c_seeker->current->nome, c_seeker->current->x_pos, c_seeker->current->y_pos);

					input_i->current->cidade = c_seeker->current;
				}
			c_seeker = c_seeker->next;
			}


			break;




			//Weave foi chamado sobre um Adaptador
				/*
					Deve-se procurar por todas as intercons que se ligam saindo dele, e assim, formar as
						devidas conexões. Essa é a parte mais propensa a erros no corpo da função
				*/
		case 'A':

			input_a = * (A_list**) input;			//TYPECASTING TÁ ROLANDO!! não mexa nessa linha

			//checagem de percorrimento :: evita loops infinitos // redundância nas definições de adaptadores
			if (input_a->current->status != 0)
				return FUNCTION_OK;
			else input_a->current->out_max = 0;	//inicialização

				/*Fase 1: contagem de outputs
					A função conta quantas saídas o adaptador possui, para poder, assim, alocar um array de saídas
					Loop
				*/
			input_a->current->out_max	= 0;
			i_seeker 					= (*data_i);
			while (i_seeker != NULL){
				if (A_MATCH_I)
					input_a->current->out_max++;
			i_seeker = i_seeker->next;
			}			

			if (input_a->current->out_max == 0){
				printf("Nao ha saidas\n");
				return ERROR_DATA;
			}
			else	//(I_type**)
				input_a->current->out = (I_type**) malloc(sizeof(void*) * (input_a->current->out_max));	//Alocação do Array de Ponteiros de Saída
																											//basicamente, I_type* out[out_max];



				/*Fase 2: Estabelecimento de Conexões
					A função já sabe quantas saídas serão necessárias para o adaptador, resta estabelecer, de fato,
						as conexões necessárias
					Loop
				*/
			counter = 0;
			i_seeker = (*data_i);
			while (i_seeker != NULL){
				/*
				printf("Current Adaptor: \t%s\n", input_a->current->nome);
				printf("Current Intercon: \t%s\n", i_seeker->current->nome);
				*/
				if (A_MATCH_I){		//se adaptador estiver ligado a uma intercon
					
					input_a->current->out[counter] =  i_seeker->current;
					// printf("nome da intercon: %s\n", (input_a->current->out[counter])->nome);

					


										//printf opcional
					if (ALLPRINT)
						printf("Conexao estabelecida\n\t\tAdaptador: \t%s\t// x: \t%d\t y: \t%d\t\n\t\tIntercon: \t%s\t// x: \t%d\t y: \t%d\t\n\n",
							input_a->current->nome, 	input_a->current->x_pos, 			input_a->current->y_pos,
							//input_a->current->out[counter]->nome, 	input_a->current->out[counter]->x_start_pos, 	input_a->current->out[counter]->y_start_pos);		//versão B
							i_seeker->current->nome, 	i_seeker->current->x_start_pos, 	i_seeker->current->y_start_pos);		//versão A

					

					if (weave ((void**) &i_seeker, 'I', data_c, data_a, data_i) == ERROR_DATA){
						printf ("ERROR DATA CALLING I");
						return ERROR_DATA;
					}

					counter++;
					if (counter > input_a->current->out_max)
						return -7;

				}
			i_seeker = i_seeker->next;
			}			


			break;

			/*
			Case 'C' não existe, pois parte-se do princípio de que as cidades, por serem os pontos de chegada de abastecimento, não
				passam energia para outros nós: isso é dever dos adaptadores
				de forma semelhante, não há nenhum caso que chame case 'G', pois os geradores não recebem energia de entrada
			*/

			default:

				return ERROR_FORMAT;
	}

	return FUNCTION_OK;
}




// -------------------------------------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------------------------------




int web_run (void** target, char mode){

	// Note que essa função, ao contrário da weave, é pensada em _type, não havendo o termo "->current->" intermediário

	G_type* target_g = NULL;
	C_type* target_c = NULL;
	A_type* target_a = NULL;
	I_type* target_i = NULL;
		//variáveis cujo único objetivo é receber o input

	int counter;
	int code = 0;

		//Verificação de input
	if (*target == NULL)
		return ERROR_STREAM;

	switch (mode){
			//run foi chamada sobre um gerador
		case 'G':

				//Leitura e printing
			target_g = (* (G_list**) target)->current;
			if (target_g == NULL)
				return ERROR_DATA;

			printf("NODE START:\n");
			printf("(%c) %s ===> ", mode, target_g->nome);

				//Chamada de recursão, com perpetuação do valor de retornO
			// printf("intercon seguinte: %s\n", target_g->out->nome);
			return web_run((void**) &(target_g->out), 'I');
				/*
					Parece estranho, mas funciona: a ideia é que seja qual for
						o valor retornado por web_run(), este valor será retornado
						para a chamada principal. Dessa forma, apenas se a rede
						chegar em uma cidade, haverá retorno FUNCTION_OK
							- Se em qualquer ponto da função, houver acesso de um
								ponteiro NULL, o retorno final será ERROR_DATA
							- Se target for NULL (entrada não inicializada), a
								função retorna ERROR_STREAM
					Detalhe para o caso A, em que há um loop.
				*/
			break;





			//run foi chamada sobre uma intercon
		case 'I':
				//Leitura e printing
			target_i = (* (I_type**) target);
/*			printf("Current Intercon: %s\n", target_i->nome);
			printf("Current Intercon: %s\n", (* (I_type**) target)->nome);*/

			if (target_i == NULL)
				return ERROR_DATA;
			printf("(%c) %s ===> ", mode, target_i->nome);

			if (target_i->adaptador != NULL)
				return web_run((void**) &(target_i->adaptador), 'A');

			if (target_i->cidade != NULL)
				return web_run((void**) &(target_i->cidade), 	'C');

			break;



			//run foi chamada sobre um adaptador
		case 'A':
				//Leitura e printing
			target_a = (* (A_type**) target);
/*			printf("Current Intercon: %s\n", target_i->nome);
			printf("Current Intercon: %s\n", (* (I_type**) target)->nome);*/

			if (target_a == NULL)
				return ERROR_DATA;
			printf("(%c) %s\n", mode, target_a->nome);
			printf("\t Adaptador %s:", target_a->nome);

				//Loop de percorrimento de saídas
			for (counter = 0; counter < target_a->out_max; counter++){
				printf("\n\t\t Saída %d: ", counter+1);
				web_run((void**) &(target_a->out[counter]), 'I');
			}
			printf("\n\t\t\t(fim do adaptador %s)\n\n", target_a->nome);

			break;

			//run foi chamada sobre uma cidade (caso final, não há mais chamadas recursivas)
		case 'C':
				//Leitura e printing
			target_c = (* (C_type**) target);
			if (target_c == NULL)
				return ERROR_DATA;

			printf("(%c) %s", mode, target_c->nome);
			break;

		default:
			return ERROR_FORMAT;
	}	


	return FUNCTION_OK;
}









int main(int argc, char const *argv[]){
	FILE* ptr= fopen("teste.txt","r");
	
	G_list* g = NULL;
	C_list* c = NULL;
	A_list* a = NULL;
	I_list* i = NULL;

	G_list* g_aux;
	int retorno;

	build_all(ptr,&c,&g,&i,&a);
	//print_lists(&c,&g,&i,&a);

	//printf("Buildei tudo.\n");
	fclose(ptr);

	

		//weaving loop
	g_aux = g;
	while (g_aux != NULL){
		//printf("FIRST Intercon: \t%s\n", i->current->nome);
		//printf("Current Generator: \t%s\n", g_aux->current->nome);
		if ((retorno = weave ((void**) &g_aux, 'G', &c, &a, &i)) == ERROR_DATA){ 	//void g e G são os únicos termos variáveis na função. c, a e i poderiam muito bem ser variáveis globais para manter a data universal.
			printf ("COLISÃO, ENCERRANDO");									//esta condicional é uma assertiva de que a função não detectou erros na database
			return ERROR_DATA;
		}
		g_aux = g_aux->next;
	}


	printf("weave return value: %d\n", retorno);

		//running test
	printf("Now Testing web_run()\n");
	g_aux = g;
	while (g_aux != NULL){
		printf("\nweb_run return value: %d\n", 
			web_run((void**) &g_aux, 'G'));
		g_aux = g_aux->next;
		printf("\n");
	}	

	if (ALLPRINT)
	print_lists(&c, &g, &i, &a);


		//memory resetting
	destroy((void**) &g, 'G');
	destroy((void**) &c, 'C');
	destroy((void**) &a, 'A');
	destroy((void**) &i, 'I');



	printf("End of Execution\n");
	//system("PAUSE");
	return 0;
}







/*
	TODO:

*/

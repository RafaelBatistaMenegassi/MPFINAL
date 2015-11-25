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


#define ALLPRINT   0

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





int log_run(FILE* ptr, C_list* c, G_list* g, I_list* i, A_list* a){
 
    /*  Nesta etapa, Fase 1, so incluiremos no log os fatores que podem ser calculados 
        sem a necessidade de simulacao.
 
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
 
 
    auxG = g;
    while(auxG != NULL){
        numG++;
        energiaTotal += auxG->current->production;
        auxG = auxG->next;
 
    }
    printf("Total de Geradores: %d\nEnergia Total Gerada: %d\n", numG ,energiaTotal);
    fprintf(ptr,"-------RELATORIO DE ATIVIDADES-------\n\n\nTotal de Geradores: %d\nEnergia Total Gerada: %d\n", numG, energiaTotal );
 
 
    auxC = c;
    while(auxC != NULL){
        numC++;
        energiaGastaTotal+=auxC->current->cost;
        auxC = auxC->next;
    }
    printf("Total de Cidades: %d\nEnergia Total Gasta Pelas Cidades: %d\n", numC ,energiaGastaTotal);
    fprintf(ptr,"Total de Geradores: %d\nEnergia Total Gasta Pelas Cidades: %d\n", numC, energiaGastaTotal );
 
 
    auxI = i;
    while( auxI != NULL){
        comprimento+= sqrt( pow( (double) ((auxI->current->x_start_pos) - (auxI->current->x_final_pos)) , 2 ) + pow( (double)( (auxI->current->y_start_pos) - (auxI->current->y_final_pos) ) , 2 ) );
        auxI = auxI->next;
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

int weave(void** input, char mode,
                        C_list** data_c,    //data referente às cidades (para poder fazer a busca)
                        A_list** data_a,    //data referente aos adaptadores (para poder fazer a busca)
                        I_list** data_i     //data referente às interconexões (para poder fazer a busca)
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
    short int counter   = 0;
        /*  Variável que verifica se alguma conexão já foi feita nos valores x, y correntes.
                Caso haja mais de uma conexão a ser feita para um mesmo ponto que não seja um
                adaptador, isso caracteriza uma conexão ilegal (a database está corrupta).
                A função retornará um valor de erro e terminará a execução caso isso aconteça.
        */


    switch (mode){

            //Weave foi chamado sobre um gerador
        case 'G':
            input_g = * (G_list**) input;           //TYPECASTING TÁ ROLANDO!! não mexa nessa linha 

                //search I
            i_seeker = (*data_i);
            while(i_seeker != NULL){    
                //printf("Current Intercon: %s\n", i_seeker->current->nome);
                if (G_MATCH_I){     //if match

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

                    input_g->current->out = i_seeker->current;      // Estabelecimento da conexão (plug)
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
            input_i = * (I_list**) input;           //TYPECASTING TÁ ROLANDO!! não mexa nessa linha

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
                if (I_MATCH_A){     //se intercon estiver ligada a um adaptador
                    

                                        //printf opcional
                    if (ALLPRINT)
                        printf("Conexao estabelecida\n\t\tIntercon: \t%s\t// x: \t%d\t y: \t%d\t\n\t\tAdaptador: \t%s\t// x: \t%d\t y: \t%d\t\n\n",
                            input_i->current->nome,     input_i->current->x_final_pos,  input_i->current->y_final_pos,
                            a_seeker->current->nome,    a_seeker->current->x_pos,       a_seeker->current->y_pos);

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
                if (I_MATCH_C){     //se intercon estiver ligada a uma cidade
                    

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

            input_a = * (A_list**) input;           //TYPECASTING TÁ ROLANDO!! não mexa nessa linha

            //checagem de percorrimento :: evita loops infinitos // redundância nas definições de adaptadores
            if (input_a->current->status != 0)
                return FUNCTION_OK;
            else input_a->current->out_max = 0; //inicialização

                /*Fase 1: contagem de outputs
                    A função conta quantas saídas o adaptador possui, para poder, assim, alocar um array de saídas
                    Loop
                */
            input_a->current->out_max   = 0;
            i_seeker                    = (*data_i);
            while (i_seeker != NULL){
                if (A_MATCH_I)
                    input_a->current->out_max++;
            i_seeker = i_seeker->next;
            }           

            if (input_a->current->out_max == 0){
                printf("Nao ha saidas\n");
                return ERROR_DATA;
            }
            else    //(I_type**)
                input_a->current->out = (I_type**) malloc(sizeof(void*) * (input_a->current->out_max)); //Alocação do Array de Ponteiros de Saída
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
                if (A_MATCH_I){     //se adaptador estiver ligado a uma intercon
                    
                    input_a->current->out[counter] =  i_seeker->current;
                    // printf("nome da intercon: %s\n", (input_a->current->out[counter])->nome);

                    


                                        //printf opcional
                    if (ALLPRINT)
                        printf("Conexao estabelecida\n\t\tAdaptador: \t%s\t// x: \t%d\t y: \t%d\t\n\t\tIntercon: \t%s\t// x: \t%d\t y: \t%d\t\n\n",
                            input_a->current->nome,     input_a->current->x_pos,            input_a->current->y_pos,
                            //input_a->current->out[counter]->nome,     input_a->current->out[counter]->x_start_pos,    input_a->current->out[counter]->y_start_pos);       //versão B
                            i_seeker->current->nome,    i_seeker->current->x_start_pos,     i_seeker->current->y_start_pos);        //versão A

                    

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
/*          printf("Current Intercon: %s\n", target_i->nome);
            printf("Current Intercon: %s\n", (* (I_type**) target)->nome);*/

            if (target_i == NULL)
                return ERROR_DATA;
            printf("(%c) %s ===> ", mode, target_i->nome);

            if (target_i->adaptador != NULL)
                return web_run((void**) &(target_i->adaptador), 'A');

            if (target_i->cidade != NULL)
                return web_run((void**) &(target_i->cidade),    'C');

            break;



            //run foi chamada sobre um adaptador
        case 'A':
                //Leitura e printing
            target_a = (* (A_type**) target);
/*          printf("Current Intercon: %s\n", target_i->nome);
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




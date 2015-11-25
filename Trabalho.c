#include <stdlib.h>
#include <stdio.h>
#include <assert.h>


#include "includes/mod_con/mod_construcao.h"
#include "includes/mod_process/mod_process.h"

#define ENTRADA "includes/teste.txt"
#define SAIDA "log.txt"



/*
	TRABALHO DE METODOS DE PROGRAMACAO - FASE 1

	14/0139907   -   Gabriel Benevides
	14/0159355	 -	 Rafael Batista
	14/0163603	 -	 Thales Grilo

	Nesta primeira fase do trabalho foram implementadas as estruturas de dados para fins de leitura 
	do documento txt contendo as informações do mapa. Temos listas de entidades, cidades, geradores, interconexcoes
	e adaptadores e processamos as listas para obter as infromacoes necessarias do relatorio parcial da fase 1.

	A execucao do arquivo "trabalho.c" gerará as listas de entidades, e mostrará na tela o log com as informações
	além de gerar um txt chamado "log.txt" . Foram implementadas funcoes para a liberacao da memoria alocada para as listas
	e para a impressao do conteudo das listas caso o usuario queira.
	
	Temos modulos de construcao de estruturas e de processamento além de módulos de definições de macros fundamentais e structs
	para as TAD's. Estes estão localizados em suas respectivas localizações nas pastas de mod_process, mod_con ou mod_def.

	A maioria das funcoes tem como argumentos de entrada ponteiros para ponteiros das listas de entidades, por isso na maior parte 
	das vezes temos que passar os nomes das listas com um '&' na frente, para indicar o local da memoria onde elas se encontram.

	Obs: No sistema operacional Unix, e necessario a inclusao da flag "-lm" no momento da compilacao para que seja possivel a 
	inclusao da biblioteca "math.h" que e usada para calcular algumas variaveis ao longo do processo.

	Merci à Tous.
	

*/


int main(int argc, char const *argv[]){

	

	FILE *entrada, *saida;

	// Variavel que indicara a preferencia do usuario em imprimir ou nao a lista na tela.
	int op;
	
	entrada = fopen(ENTRADA, "r");
	assert(entrada != NULL);	// Assertiva para checar a abertura correta do arquivo.

	printf("Inicio da execucao\n");

	// Declaracao e Alocacao das Listas de Entidades.
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

	assert( (i == NULL)  && (g == NULL) && (c == NULL) &&(a == NULL) ); // Verificamos a inicializacao correta das listas de entidades.
	printf("Listas de Entidades Declaradas e Memoria Alocada.\n");

	build_all(entrada,&c,&g,&i,&a);	// Como os parametros sao ponteiros para ponteiros temos que passar o endereço de memoria de nossas listas de entidades.
	assert( (i != NULL)  && (g != NULL) && (c != NULL) && (a != NULL) ); // Assertiva para garantir o preenchimento correto das listas.

	// Impressao do conteudo
	printf("\nListas de entidades preenchidas devidamente.\nDeseja imprimi-las?\n\n(1)Sim\n(2)Nao\n");
	scanf("%d",&op);
	assert( (op==1) || (op==2) ); // Assertiva para garantir uma escolha plausivel do usuario.

	if(op==1)
		print_lists(&c,&g,&i,&a);
	

	// Fechamento do arquivo e assertiva para verificacao.
	int close = fclose(entrada);
	assert(close == FUNCTION_OK);

	//Abertura do arquivo de saida e verificacao.
	saida = fopen(SAIDA, "w");
	assert(saida != NULL); // Testamos se o arquivo abriu corretamente.


	G_list* g_aux;
	int retorno;


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


	/*
	Entramos na fase de processamento. Durante a fase 2, aqui ficará o laço de simulação. 
	Por enquanto, so processamos as informacoes necessárias para a fase 1.  

	*/

	printf("\n\n--------------------------LOG DE ATIVIDADES--------------------------\n");

	log_run(saida,c,g,i,a);

	// Agora fechamos o arquivo de saida.
	close = fclose(saida);
	assert(close == FUNCTION_OK);	// Arquivo foi fechado corretamente.


	// Variaveis para guardar os retornos das funcoes de liberacao de memoria.
	int saidas[4];	
	saidas[0]=destroy((void**) &g, 'G');
	saidas[1]=destroy((void**) &c, 'C');
	saidas[2]=destroy((void**) &a, 'A');
	saidas[3]=destroy((void**) &i, 'I');
	// Assertiva para garantir o funcionamento saudavel da funcao de desalocacao de memoria.
	assert( (saidas[0] == FUNCTION_OK) && ( saidas[1] == FUNCTION_OK ) &&  ( saidas[2] == FUNCTION_OK ) && ( saidas[3] == FUNCTION_OK ) );
	printf("\nEntidades Destruidas --- Memoria Desalocada\n");


	printf("Fim de Execucao\n");
	return 0;
}
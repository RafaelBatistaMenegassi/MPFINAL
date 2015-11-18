#include <stdio.h>
#include <stdlib.h>

	//Essential Definitions
#define NAMEMAX 50

	//Essential Typedefs

typedef struct Cidade{
	
	char nome[NAMEMAX]
	int x_pos;
	int y_pos;
	int cost;

	}	C_type;


typedef struct Gerador{

	char nome[NAMEMAX]
	int x_pos;
	int y_pos;
	int production;
	int cost;

	I_type* next;

	}	G_type;


typedef struct Interconexao{
	char nome[NAMEMAX]
	int x_start_pos;
	int y_start_pos;
		//pode ser obtido através do ponto de origem
	int x_final_pos;
	int y_final_pos;
		//pode ser obtido através do ponto de chegada

	int max_capacity;
	float fault_chance;
	int time_main;
	int cost_main;

	A_type* adaptador;
	C_type* cidade;


	}	I_type;

typedef struct Adaptador{

	char nome[NAMEMAX]
	int x_pos;
	int y_pos;

	I_type** out;

	}	A_type;

	// Listas para Construção:


typedef struct Cidade_lista{
	C_type* current;

	struct Cidade_lista *next;
	} C_list;


typedef struct Gerador_lista{
	
	G_type* current;
	struct Gerador_lista *next;

	
	} G_list;



typedef struct Interconexao_lista{
	I_type* current;

	struct Interconexao_lista *next;
	} I_list;


typedef struct Adaptador_lista{
	A_type* current;

	struct Adaptador_lista *next;
	} A_list;
	
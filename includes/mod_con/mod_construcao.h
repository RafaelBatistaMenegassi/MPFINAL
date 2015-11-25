
#include <stdio.h>
#include <stdlib.h>
#include "mod_construcao.c"


//#include "../mod_def/essential_defs.h"
//#include "../mod_def/errorcodes.h"


	// Funcoes para o preenchimento e destruicao das listas de entidades a partir do arquivo .txt fornecido.


int build_all(FILE* , C_list** , G_list** , I_list** , A_list**  );

int c_build(char* , C_list**);

int g_build(char* , G_list**);

int a_build(char* , A_list**);

int i_build(char* , I_list**);

int destroy(void**, char);
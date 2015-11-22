
#include <stdio.h>
#include <stdlib.h>
#include "mod_construcao.c"

#include "../mod_def/essential_defs.h"
#include "../mod_def/errorcodes.h"


	// Functions


int build_all(FILE* , C_list** , G_list** , I_list** , A_list**  );

int c_build(char* , C_list**);

int g_build(char* , G_list**);

int a_build(char* , A_list**);

int i_build(char* , I_list**);

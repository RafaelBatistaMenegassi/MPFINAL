#include <stdio.h>
#include <stdlib.h>

#define ERROR_DATA -7

c_destroy(c_list** target){

	//c_type* current;
	c_list* subtarget;


	if (target == NULL)
		return ERROR_INPUT;
	else if ((*target) == NULL)
		return ERROR_DATA;
	else{

		subtarget = (*target);

		if(subtarget->next != NULL{
			c_destroy(&(subtarget->next));
		}else{
			//liberar campos

			free(subtarget->current->nome);
			free(subtarget->current);
			free(subtarget);
		}

		return FUNCTION_OK;
	}
}


-----------------------------------------------

int c_plug(c_type** target, c_type*){

}

-----------------------------------------------


int weave(){

	


}


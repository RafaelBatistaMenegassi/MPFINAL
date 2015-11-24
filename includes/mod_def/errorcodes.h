/*Este arquivo contém os valores de retorno para as funções,
	explicando o que significam
*/

#define FUNCTION_OK 	 0
	// Valor de retorno padrão, indica funcionamento saudável da função


#define ERROR_STREAM 	-1
	/* Indica que houve erro no input recebido, portanto a função não
		pode processar a informação
	*/	

#define ERROR_FORMAT 	-2
	/* Retorno deste valor indica, a princípio, que a função foi chamada
		de forma incorreta, exigindo que ela processe as informações dadas
		de maneira incondizente.
		Exemplo:
			destroy() recebe um caractere como parâmetro que indica o
			modo de desalocação de memória a ser feito. corrupção deste
			caractere durante o input faz com que a função retorne
			este valor.
	*/
		

#define ERROR_DATA 		-3
	/* Uma função retornará este valor caso a data adquirida, por mais
		que se apresente como informação saudável, seja nula. O motivo
		para a utilização deste código de erro é, principalmente a função
		destroy(), que retornará ERROR_DATA caso a lista de elementos
		recebida esteja estruturada de forma saudável, porém algum
		elemento não contenha informação.
	*/
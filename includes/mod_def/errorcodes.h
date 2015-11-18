/*Este arquivo contém os valores de retorno para as funções,
	explicando o que significam
*/

#define FUNCTION_OK 	 0
	// Valor de retorno padrão, indica funcionamento saudável da função


#define ERROR_STREAM 	-1
	/* Indica que houve erro no input recebido, portanto a função não
		pode processar a informação
	*/	

#define ERROR_OVERFLOW 	-2
	/* Caso particular: houve erro no processo de contagem de linhas.
		Este valor de retorno é chamado para conter o movimento dos
		ponteiros de leitura/escrita.
		Caso isso ocorra, é possível que esteja-se tentando escrever
		no arquivo informações fora de controle, o que geraria uns
		erros bizarros
	*/

#define ERROR_TARGET	-3
	/* Valor retornado por reg_seek(), caso o valor da linha procurada
		seja negativo. A ausência deste retorno não causaria problemas,
		mas serve como detecção de erro, indicando que houve falha no
		processo de contagem de linhas.
		Também retornado por seek_primario(), caso a chave buscada não
		corresponda a nenhum registro conhecido.
	*/



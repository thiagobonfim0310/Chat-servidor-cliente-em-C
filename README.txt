servidor:

compilação: gcc -o serve serverTCP.c -lpthread

execução : ./serve 22000 batepapo 

cliente:

complilação: gcc -o client clientTCP.c -lpthread

execução : ./client 22000 127.0.0.1 thiago

o servidor somente suporta 10 clientes. a inicialização deve ser da seguinte forma, primeiro se inicia o servidor aguarda 5 segundos e logo depois se inicia o cliente.

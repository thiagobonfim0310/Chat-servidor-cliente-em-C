#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

char *usuario ;
char msgcompl[100];

void * recebe(void * param){
	int client_fd = (int) param;	
		while (1){
		char recv_msg[100]="";

		read(client_fd, recv_msg, 100); // le do servidor string para exibir para o usuario

		printf(" %s\n", recv_msg); // exibe o recebido na tela
			
		}
}
void escreve(void *param){
	int client_fd = (int)param;
		
	while(1) {
		char send_msg[100];
		bzero( send_msg, 100);
	
		//read(client_fd, recv_msg, 100); // le do servidor string para exibir para o usuario
		
		printf("Digite algo : \n");
		fgets(send_msg, 100, stdin); //le do usuario string para enviar ao servidor
		send_msg[strcspn(send_msg,"\n")] = "\0";
		strcat(msgcompl, usuario);
		strcat(msgcompl,send_msg);
		
		send(client_fd,msgcompl,strlen(msgcompl)+1,0);
		bzero(msgcompl,sizeof(msgcompl));
	}
}

int main(int argc, char *argv[] ) {

	char *nomes = argv[3];
	/*	printf("digite seu nome\n");
		fgets(usuario,sizeof(usuario),stdin);
		usuario[strcspn(usuario,"\n")] = "\0";*/
		strcat(nomes, ": ");
	int client_fd; // file descriptor do socket do cliente
	usuario = nomes;
	int port = atoi(argv[1]);

	char *host = argv[2];//"127.0.0.1"; 
	pthread_t threads[2];
	char send_msg[100]; // string com mensagem a enviar
	 // string com mensagem a receber

	struct sockaddr_in server_addr; // struct com informacoes do servidor a conectar

	client_fd = socket(AF_INET, SOCK_STREAM, 0); //criacao do socket cliente

	bzero(&server_addr, sizeof(server_addr)); // inicializacao da struct que armazenara endereco do servidor
	
	server_addr.sin_family = AF_INET; 
	server_addr.sin_port = htons(port); // associa porta do servidor a struct
	inet_aton(host, &server_addr.sin_addr); // associa endereco do servidor (armazenado na string host) a struct

	printf("Conectando-se a porta %d do servidor %s\n", port, host);
	
	while (1){
	 int ct = connect(client_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)); // funcao bloqueante, conecta ao servidor
			printf("%d",ct);
			
			if (ct>=0)
			{
				break;
			}
			
	}

		pthread_create(&threads[0],NULL, (void*)escreve, (void*) client_fd);
		pthread_create(&threads[1], NULL, (void*)recebe, (void*) client_fd);
	
	while (1);
		

	return 0;
}

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
int conectados[10];
sem_t mutex;

void arquivo(char *string){
	sem_wait(&mutex);
	FILE *arq;
	arq =fopen("conversa.txt","a");
	fprintf(arq,"%s\n",string);
	fclose(arq);
	sem_post(&mutex);
}
void* responde_cliente(void* param) {

	int client_fd = (int) param;

	char msg[100];
	
	while(1) {
		bzero(msg, 100); // inicializa a mensagem com 0
              int re = read(client_fd, msg, 100); // le mensagem do socket cliente associado
                arquivo(msg);
				printf("%s\n",msg); // exibe o que recebeu do cliente
               
		if(re>0){	
			for(int i = 0; i < 10; i++){
				if(conectados[i] != 0){
					//printf("to enviando para %d a mensagem %s", conectados[i],msg);
					send(conectados[i],msg,strlen(msg)+1,0);
					//printf("enviei");
				}	
			}
		}
	
	}

}


/* Um servidor de eco. Tudo que este servidor receber de um cliente, ele enviara de volta */

int main(int argc, char *argv[]) {

		if (argc!=3)
		{
			printf("paramentros errados");
			exit(1);
		}
		
	char msg[100];
	char msg2[100]= "Voce entrou em ";
	char *batepap = argv[2];
	int server_port = atoi(argv[1]);
	 sem_init(&mutex,0,1);
	int listen_fd, client_fd; // dois file descriptors, 1 para ouvir solicitacoes, outro para o cliente

	struct sockaddr_in server_addr; // struct com informacoes para o server socket
	struct sockaddr_in client_addr; // struct que armazenara informacoes do cliente conectado

	pthread_t threads[10]; // array que armazenara 10 threads (MAXIMO DE CLIENTES)
 
	int thread_count = 0; // contador de threads (de clientes)

	printf("Loading...\n");
	
	strcat(msg2,batepap);
	listen_fd = socket(AF_INET, SOCK_STREAM, 0); // listen_fd representa o socket que aguardara requisicoes

	bzero(&server_addr, sizeof(server_addr)); // Inicializa a estrutura do servidor sockaddr_in com 0
	bzero(&client_addr, sizeof(client_addr)); // Inicializa a estrutura do cliente sockaddr_in com 0

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY; // Constante sinaliza que o socket sera um servidor
	server_addr.sin_port = htons(server_port); // Porta a ser associada ao socket servidor criado

	bind(listen_fd, (struct sockaddr*) &server_addr, sizeof(server_addr)); // associa parametros definidos

	listen(listen_fd, 10); // sinaliza que aguardara conexoes na porta associada

	printf("Aguardando conexoes na porta %d\n",server_port);
	bzero(conectados,sizeof(conectados));
	while (1) {
		client_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL); // funcao bloqueante, gera novo socket 
	
		send(client_fd,msg2,strlen(msg2)+1,0);
		pthread_create(&threads[thread_count++], NULL, (void*) responde_cliente, (void*) client_fd);
	
		for (int i = 0; i < 10; i++)
		{
			if(conectados[i]==0){
				conectados[i]= client_fd;
				break;
			}
		}
		
	}

	return 0;
}

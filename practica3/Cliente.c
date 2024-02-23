#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// https://www.geeksforgeeks.org/socket-programming-cc/

int main(int argc, char const *argv[])
{
    int puerto = 12345, longitud_cliente;
    char buffer[50] = {0};
    char mensajeEnviar[50]= {0};
	struct sockaddr_in servaddr = {0};
	
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd == -1){
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(puerto);
	inet_pton(AF_INET, "127.0.0.1" , &(servaddr.sin_addr));

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr)) == -1){
        perror("Error en connect");
        exit(-1);
    }

	while(1){
        gets(mensajeEnviar);
        write(sockfd, mensajeEnviar, strlen(mensajeEnviar)+1);
    }
	close(sockfd);
    return 0;
}
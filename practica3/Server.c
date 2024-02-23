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
    int puerto = 12345, longitud_cliente, fieldDescriptor2;
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
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int rc = bind(sockfd, (const struct sockaddr *)&servaddr, 
				  sizeof(servaddr));
	printf("%d",2);
	if(rc == -1){
		perror("failed to bind");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	// if (listen(sockfd, 5) == -1){
    //     perror("Error en listen");
    //     exit(-1);
    // }

	while(1){
        longitud_cliente = sizeof(struct sockaddr_in);
        // aceptar conexiones
        if ((fieldDescriptor2 = accept(sockfd, (struct sockaddr *) NULL, &longitud_cliente)) == -1){
            perror("Error en accept");
            exit(-1);
        }
			read(fieldDescriptor2, buffer, 100);
			printf("%s", buffer);
			gets(mensajeEnviar);
            //send(fieldDescriptor2, "Bienvenido a mi servidor :D", 26, 0);
			write(fieldDescriptor2, "Bienvenido a mi servidor :D", 26);		
    }
	close(sockfd);
	close(fieldDescriptor2); // cerrar el socket del lado del cliente
    return 0;
}
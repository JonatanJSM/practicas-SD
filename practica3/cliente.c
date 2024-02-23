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
    int puerto = 12345;
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

    socklen_t len = 0;
	
	int n = recvfrom(sockfd, (char *)buffer, 50, MSG_WAITALL, 0, &len);
	buffer[n] = '\n';
	printf("%s", buffer);
	close(sockfd);
    // listen(sockFieldDescriptor, 10);
    // int comm_fd = accept(sockFieldDescriptor, (struct servidorCliente *) NULL, NULL);
    
//     while (1)
//     {
//         socklen_t len = 0;
//         read(comm_fd, cadena, 100);
//         printf("%s",cadena);
// 	    // int n = recvfrom(sockFieldDescriptor, (char *)buffer, 50, MSG_WAITALL, 0, &len);
// 	    // buffer[n] = '\n';
// 	    // printf("%s", buffer);
// 	    // close(sockFieldDescriptor);


//         gets(sendline);
//         write(comm_fd, sendline, 100);

//     }
    
// close(sockFieldDescriptor);
    return 0;
}
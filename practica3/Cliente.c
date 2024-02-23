#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 12345
#define SERVER_IP "127.0.0.1"

// https://www.geeksforgeeks.org/socket-programming-cc/

int main(int argc, char const *argv[]){
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[20];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    printf("Cliente conectado al servidor\n");
    while (1) {
        printf("Mensaje: ");
        fgets(buffer, 20, stdin);
        
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        // Enviar mensaje al servidor
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

        ssize_t bytes_received = recvfrom(sockfd, buffer, 20, 0, NULL, NULL);
        if (bytes_received == -1) {
            perror("Error al recibir respuesta");
            exit(EXIT_FAILURE);
        } else {
            buffer[bytes_received] = '\0';
            printf("Respuesta del servidor: %s\n", buffer);
        }
    }

    close(sockfd);
    return 0;
}
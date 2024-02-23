#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 12345

// https://www.geeksforgeeks.org/socket-programming-cc/
// https://stackoverflow.com/questions/66554581/difference-between-send-and-sendto-in-c-for-a-udp-network-implementation
// hilos de ejecucion para que se pueda hacer en un solo archivo

int main(int argc, char const *argv[]){
	int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[20];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Enlazar socket al puerto
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al enlazar");
        exit(EXIT_FAILURE);
    }

    printf("Servidor esperando mensajes en el puerto %d...\n", PORT);

    while (1) {
        socklen_t client_addr_size = sizeof(client_addr);

        // Recibir mensaje del cliente
        ssize_t bytes_received = recvfrom(sockfd, buffer, 20, 0, (struct sockaddr*)&client_addr, &client_addr_size);
        if (bytes_received == -1) {
            perror("Error al recibir mensaje");
            exit(EXIT_FAILURE);
        } else {
            buffer[bytes_received] = '\0';
            printf("Mensaje recibido de %s:%d: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

            // Enviar respuesta al cliente
            printf("Respuesta: ");
            fgets(buffer, 20, stdin);
            sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, client_addr_size);
        }
    }

    close(sockfd);
    return 0;
}
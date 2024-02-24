#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8888
#define BUFFER_SIZE 20

void *server_thread(void *arg) {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Error al enlazar");
        exit(EXIT_FAILURE);
    }

    printf("Servidor esperando mensajes en el puerto %d...\n", PORT);

    while (1) {
        socklen_t client_addr_size = sizeof(client_addr);

        ssize_t bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr, &client_addr_size);
        if (bytes_received == -1) {
            perror("Error al recibir mensaje");
            exit(EXIT_FAILURE);
        } else {
            buffer[bytes_received] = '\0';
            printf("Mensaje recibido de %s:%d: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);
            printf("Respuesta: ");
            fgets(buffer, BUFFER_SIZE, stdin);
            sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&client_addr, client_addr_size);
        }
    }

    close(sockfd);
    return NULL;
}

void *client_thread(void *arg) {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Cliente conectado al servidor\n");

    while (1) {
        printf("Mensaje: ");
        fgets(buffer, BUFFER_SIZE, stdin);
    
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));

        ssize_t bytes_received = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, NULL, NULL);
        if (bytes_received == -1) {
            perror("Error al recibir respuesta");
            exit(EXIT_FAILURE);
        } else {
            buffer[bytes_received] = '\0';
            printf("Respuesta del servidor: %s\n", buffer);
        }
    }

    close(sockfd);
    return NULL;
}

int main() {
    pthread_t server_tid, client_tid;
    
    if (pthread_create(&server_tid, NULL, server_thread, NULL) != 0) {
        perror("Error al crear hilo del servidor");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&client_tid, NULL, client_thread, NULL) != 0) {
        perror("Error al crear hilo del cliente");
        exit(EXIT_FAILURE);
    }

    pthread_join(server_tid, NULL);
    pthread_join(client_tid, NULL);

    return 0;
}

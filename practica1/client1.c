#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <netdb.h>

int main(int argc, char **argv){
    if(argc > 2){
        char *ip;
        int fieldDescriptor, numberBytes, puerto;
        char buffer[100];
        puerto = atoi(argv[2]);
        ip = argv[1];

        struct hostent *he;
            struct sockaddr_in server;

        if((he = gethostbyname(ip)) == NULL){
            perror("Error en gethostbyname");
            exit(-1);
        }

        if((fieldDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1){
            perror("Error al crear el socket");
            exit(-1);
        }

        server.sin_family = AF_INET;
        server.sin_port = htons(puerto);
        server.sin_addr.s_addr = *((unsigned long *)he->h_addr_list[0]);
        bzero(&(server.sin_zero), 8);

        if(connect(fieldDescriptor, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1){
            perror("Error en connect");
            exit(-1);
        }

        if((numberBytes = recv(fieldDescriptor, buffer, 100, 0)) == -1){
            perror("Error en recv");
            exit(-1);
        }

        buffer[numberBytes] = '\0';
        printf("Mensaje del servidor: %s\n", buffer);
        close(fieldDescriptor);

    }else{
        printf("No se ingreso el puerto por parametro\n");
    }
    return 0;
}
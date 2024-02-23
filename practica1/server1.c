#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>

int main(int argc, char **argv){
    if(argc > 1){

        int fieldDescriptor, fieldDescriptor2, longitud_cliente, puerto;
        puerto = atoi(argv[1]);

        struct sockaddr_in server;
        struct sockaddr_in client;

        server.sin_family = AF_INET; //TCP/IP
        server.sin_port = htons(puerto);
        server.sin_addr.s_addr = INADDR_ANY; // cualquier cliente se puede conectar
        bzero(server.sin_zero, 8); 

        // definir socket
        if ((fieldDescriptor = socket(AF_INET, SOCK_STREAM, 0)) < 0){
            perror("Error al crear el socket");
            exit(-1);
        }

        // unir socket a un puerto
        if (bind(fieldDescriptor, (struct sockaddr *)&server, sizeof(struct sockaddr)) < 0){
            perror("Error en bind");
            exit(-1);
        }

        // iniciar el servicio, el socket esta en modo escucha
        if (listen(fieldDescriptor, 5) == -1){
            perror("Error en listen");
            exit(-1);
        }

        while(1){
            longitud_cliente = sizeof(struct sockaddr_in);
            // aceptar conexiones
            if ((fieldDescriptor2 = accept(fieldDescriptor, (struct sockaddr *)&client, &longitud_cliente)) == -1){
                perror("Error en accept");
                exit(-1);
            }

            send(fieldDescriptor2, "Bienvenido a mi servidor :D", 26, 0);
            close(fieldDescriptor2); // cerrar el socket del lado del cliente
        }
        close(fieldDescriptor);
    }else{
        printf("No se ingreso el puerto por parametro\n");
    }
    return 0;
}
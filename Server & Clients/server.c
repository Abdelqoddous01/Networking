#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <pthread.h>
#include <netinet/in.h>

void initializeSocketAddress(struct sockaddr_in *address, int port) {
    address->sin_family = AF_INET;
    address->sin_port = htons(port);
    address->sin_addr.s_addr = INADDR_ANY;
}


int main() {
    char server_message[256];
    char client_message[256];

    // create the socket of the server
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // associate the socket with a specific address and port
    struct sockaddr_in server_address;
    initializeSocketAddress(&server_address, 9000);
    

    // bind the socket to our IP and port
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // listen to the socket
    listen(server_socket, 10);
    printf("Server waiting for incoming connections...\n");

    int client_socket;

    while (1) {
        client_socket = accept(server_socket, NULL, NULL);

        while (1) {
            // receive data from the client
             ssize_t bytes_received = recv(client_socket, client_message, sizeof(client_message), 0); 

            if (bytes_received <= 0) {
                perror("Error receiving data");
                break;
            }

            printf("Received from client: %s\n", client_message);

            // send a response to the client
            if (strcmp(client_message, "exit") == 0) {
                close(client_socket);
                break;
            }
            else{
                strcpy(server_message, client_message);
                send(client_socket, server_message, sizeof(server_message), 0);
            }

        }
        // close the socket if the client sends "exit"
        printf("Client disconnected\n");
        break;
    }

    close(server_socket);
    // close the server socket

    return 0;
}

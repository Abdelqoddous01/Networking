#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main() {
    // create a socket
    int network_socket;
    network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Checking for the failure of the creation of the socket
    if (network_socket == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Associate the socket with a specific address and port
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9000);
    server_address.sin_addr.s_addr = INADDR_ANY; // htonl(INADDR_ANY);

    // Connecting to the socket
    int connection = connect(network_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    // Checking for an error with the connection
    if (connection == -1) {
        perror("The Server IS Down\n");
        close(network_socket);
        exit(EXIT_FAILURE);
    }

    // Send data to the server
    char client_request[256];
    while (1) {
        printf("Enter your message (type exit)\n>>");
        fgets(client_request, 256, stdin);

        // Remove the newline character
        int len = strlen(client_request);
        if (len > 0 && client_request[len - 1] == '\n') {
            client_request[len - 1] = '\0';
        }

        send(network_socket, client_request, sizeof(client_request), 0);

        if (strcmp(client_request, "exit") == 0) {
            close(network_socket);
            break;
        }

        // Receiving data from the server
        char server_response[256];
        recv(network_socket, &server_response, sizeof(server_response), 0);

        // Print out the response from the server
        printf("The data sent from the server: %s\n", server_response);
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>




int main(){
    
    //create a socket
    int network_socket;
    network_socket=socket(AF_INET,SOCK_STREAM,0);

    //Cheking of the failure of the creation of socket 
    if(network_socket == -1){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    //associate The socket with a specific address and port
    struct sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(9002);
    server_address.sin_addr.s_addr=INADDR_ANY;//htonl(INADDR_ANY);

    //connecting to the socket
    int connection_statues=connect(network_socket,(struct sockaddr *)&server_address,sizeof(server_address));

    //checking for error with connexion 
    if (connection_statues == -1)
    {
        perror("The Server IS Down\n");
        close(network_socket);
        exit(EXIT_FAILURE);
    }

    //send data to the server
    char client_request[256];
    printf("Enter your message: ");
    fgets(client_request,256,stdin);
    send(network_socket, client_request, sizeof(client_request), 0);

    //receiving data from the server
    char server_response[256];
    recv(network_socket,&server_response,sizeof(server_response),0);
    
    // print out the response_server 
    printf("The data sent from the server : %s\n",server_response);

    //finally closing the socket
    close(network_socket);
    return 0;
}
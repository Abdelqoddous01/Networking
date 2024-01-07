#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>



int main(int argc,char *argv[]){
    if (argc != 2)
    {
        printf("\nThe '%s' exit with failure",argv[0]);
        return EXIT_FAILURE;
    }

    //Take the domain name from the lign command
    char *hostname=argv[1];

    struct addrinfo hint;
    struct addrinfo *result;

    memset(&hint,0,sizeof(hint));
    hint.ai_family=AF_UNSPEC;
    hint.ai_socktype=SOCK_STREAM;
    
    int statues=getaddrinfo(hostname,NULL,&hint,&result);
    
    if (statues!=0)
    {
        printf("The getaddrinfo failed");
        return EXIT_FAILURE;
    }

    struct addrinfo *temp=result;
    while (temp!=NULL)
    {
        char address_string[INET6_ADDRSTRLEN];
        void *addr;
        if(temp->ai_family == AF_INET){
            addr=&((struct sockaddr_in*)temp->ai_addr)->sin_addr;
        }
        else{
            addr=&((struct sockaddr_in6*)temp->ai_addr)->sin6_addr;
        }
        inet_ntop(temp->ai_family,addr,address_string,sizeof(address_string));
        printf("\nAdrress string : %s\n",address_string);
        temp=temp->ai_next;
    }
    
    
    freeaddrinfo(result);
    return EXIT_SUCCESS;
}
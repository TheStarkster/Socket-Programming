#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include <unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

#define ERROR -1
#define MAX_CLIENTS 2
#define MAX_DATA 1024

int main(int argc, char **argv){
    int SOCKET,new,sent;
    unsigned int len;
    struct sockaddr_in SERVER, CLIENT;
    int sockaddr_len = sizeof(struct sockaddr_in);
    int data_len;
    char data[MAX_DATA];
    char msg[] = "READY TO GO!\n";
    if ((SOCKET = socket(AF_INET,SOCK_STREAM,0)) == ERROR)
    {
        perror("SOCKET: ");
        exit(-1);
    }
    
    SERVER.sin_family = AF_INET;
    SERVER.sin_port = htons(atoi(argv[1]));
    SERVER.sin_addr.s_addr = INADDR_ANY;
    bzero(&SERVER.sin_zero,8);

    len = sizeof(struct sockaddr_in);

    if((bind(SOCKET, (struct sockaddr* )&SERVER, len)) == -1){
        perror("BIND");
        exit(-1);
    }
    if((listen(SOCKET, MAX_CLIENTS)) == ERROR){
        perror("LISTEN");
        exit(-1);
    }

    while (1)
    {
        if((new = accept(SOCKET, (struct sockaddr*)&CLIENT, &len)) == ERROR){
            perror("ACCEPT");
            exit(-1);
        }
        
        // sent = 

        printf("New Client Connected From Port: %d; IP: %s\n", ntohs(CLIENT.sin_port), inet_ntoa(CLIENT.sin_addr));
        data_len = 1;
        while (data_len)
        {
            data_len = recv(new, data, MAX_DATA, 0);
            if(data_len){
                send(new, data, data_len, 0);
                data[data_len] = '\0';
                printf("Sent Message: %s", data);
            }
        }
        printf("Client Disconnected\n");
        close(new);
    }
    close(SOCKET);
}
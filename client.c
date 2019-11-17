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
#define BUFFER 1024

int main(int argc, char **argv){
    int SOCKET;
    struct sockaddr_in REMOTE_SERVER;
    int sockaddr_len = sizeof(struct sockaddr_in);
    unsigned int len;
    char OUT[BUFFER];
    char IN[BUFFER];
    
    if ((SOCKET = socket(AF_INET,SOCK_STREAM,0)) == ERROR)
    {
        perror("SOCKET: ");
        exit(-1);
    }
    
    REMOTE_SERVER.sin_family = AF_INET;
    REMOTE_SERVER.sin_port = htons(atoi(argv[2]));
    REMOTE_SERVER.sin_addr.s_addr = inet_addr(argv[1]);
    bzero(&REMOTE_SERVER.sin_zero,8);


    if((connect(SOCKET, (struct sockaddr* )&REMOTE_SERVER, sizeof(struct sockaddr_in))) == ERROR){
        perror("CONNECT");
        exit(-1);
    }
    while (1)
    {
        fgets(IN, BUFFER, stdin);
        send(SOCKET, IN, strlen(IN),0);

        len = recv(SOCKET, OUT, BUFFER, 0);
        OUT[len] = '\0';
        printf("%s\n", OUT);
    }
    close(SOCKET);
}
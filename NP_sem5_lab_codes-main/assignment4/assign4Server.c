#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <argp.h>
#include <sys/errno.h>
#include<string.h>
#include<stdio.h>

int main()
{
    int listen_fd, comm_fd;
    char sendMessage[100];
    char receiveMessage[100];
    struct sockaddr_in serverAddress;
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(listen_fd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(listen_fd, 10);
    comm_fd = accept(listen_fd, (struct sockaddr *)NULL, NULL);
    while (1)
    {
        recv(comm_fd, receiveMessage, sizeof(receiveMessage), 0);
        printf("Received Message: %s",receiveMessage);
        
        
        if (strcmp(receiveMessage,"exit\n")==0)
        {   printf("Exited Successfully!!\n");
            break;
            
        }
        printf("Enter Message: \n");
        fgets(sendMessage,100,stdin);
        send(comm_fd, sendMessage, sizeof(sendMessage), 0);
    }

    return 0;
}

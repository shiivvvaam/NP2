#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <argp.h>
#include <sys/errno.h>
#include<stdio.h>
#include<string.h>

int main()
{
    int socketID, n;
    char sendMessage[100];
    char receiveMessage[100];
    struct sockaddr_in serverAddress;
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    connect(socketID, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    while (1)
    {
        printf("Enter Message: \n");
        fgets(sendMessage,100,stdin);
        send(socketID, sendMessage, sizeof(sendMessage), 0);
        
        if(strcmp(sendMessage,"exit\n")==0)
        {
           printf("Exited Successfully!!\n");
            break;
        }
          
           recv(socketID, receiveMessage, sizeof(receiveMessage), 0);
           printf("Received Message: %s",receiveMessage);
    }
    return 0;
}
      

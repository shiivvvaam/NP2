#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>

int main(){
   char receiveMessage[100],sendMessage[100];
   int socketfd,clientfd;
   struct sockaddr_in serveraddr,clientaddr;
   bzero(&serveraddr,sizeof(serveraddr));
   bzero(receiveMessage,100);
   bzero(sendMessage,100);
   socketfd=socket(AF_INET,SOCK_DGRAM,0);
   serveraddr.sin_family=AF_INET;
   serveraddr.sin_addr.s_addr=INADDR_ANY;
   serveraddr.sin_port=htons(43454);
   bind(socketfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
   clientfd=sizeof(clientaddr);
   while(1){
        recvfrom(socketfd, receiveMessage, sizeof(receiveMessage), 0,(struct sockaddr*)&clientaddr,&clientfd);
        printf("Received Message: %s",receiveMessage);
        
        
        if (strcmp(receiveMessage,"exit\n")==0)
        {   printf("Exited Successfully!!\n");
            break;
            
        }
        printf("Enter Message: \n");
        fgets(sendMessage,100,stdin);
        sendto(socketfd, sendMessage, sizeof(sendMessage), 0,(struct sockaddr*)&clientaddr,clientfd);
   }
}

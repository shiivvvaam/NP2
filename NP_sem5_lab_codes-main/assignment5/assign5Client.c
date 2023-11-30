#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
  int socketfd,slength,c1,c2;
  char receiveMessage[100],sendMessage[100];
  struct sockaddr_in serveraddr;
  bzero(&serveraddr,sizeof(serveraddr));
  bzero(receiveMessage,100);
  bzero(sendMessage,100);
  socketfd=socket(AF_INET,SOCK_DGRAM,0);
  serveraddr.sin_family=AF_INET;
  serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  serveraddr.sin_port=htons(43454);
  slength=sizeof(serveraddr);
  while(1){
    printf("Enter Message: \n");
    fgets(sendMessage,100,stdin);
    sendto(socketfd, sendMessage, sizeof(sendMessage), 0,(struct sockaddr*)&serveraddr,slength);
    
        
        if(strcmp(sendMessage,"exit\n")==0)
        {
           printf("Exited Successfully!!\n");
            break;
        }
          
           recvfrom(socketfd, receiveMessage, sizeof(receiveMessage), 0,(struct sockaddr*)&serveraddr,&slength);
           printf("Received Message: %s",receiveMessage);
  }
}

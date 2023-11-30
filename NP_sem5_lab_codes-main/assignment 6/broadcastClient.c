#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
int main(){
  char recvMessage[100];
  struct sockaddr_in servaddr,clientaddr;
  int sock,cli;
  int enable=1;
  bzero(&servaddr,sizeof(servaddr));
  bzero(recvMessage,100);
  sock=socket(AF_INET,SOCK_DGRAM,0);
  setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&enable,sizeof(enable));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=inet_addr("192.168.64.255");
  servaddr.sin_port=htons(12345);
  bind(sock,(struct sockaddr*)&servaddr,sizeof(servaddr));
  cli=sizeof(servaddr);
  while(1){
   recvfrom(sock,recvMessage,sizeof(recvMessage),0,(struct sockaddr*)&clientaddr,&cli);
   printf("Received Message is : %s",recvMessage);
  }
  
}

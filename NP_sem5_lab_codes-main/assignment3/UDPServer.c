#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>

int main(){
  char str[100];
  int Socketfd,clientfd;
  struct sockaddr_in serveraddr,clientaddr;
  bzero(&serveraddr,sizeof(serveraddr));
  bzero(str,100);
  Socketfd=socket(AF_INET,SOCK_DGRAM,0); //sock_dgram is used for connectionless program which is UDP, sock_stream is used for connection oriented which is TCP
  //learn about port numbers
  serveraddr.sin_family=AF_INET;
  serveraddr.sin_addr.s_addr=INADDR_ANY;
  serveraddr.sin_port=htons(43450);
  bind(Socketfd,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
  clientfd=sizeof(clientaddr);
  recvfrom(Socketfd,str,sizeof(str),0,(struct sockaddr*)&clientaddr,&clientfd);
  
  char *ipclient=inet_ntoa(clientaddr.sin_addr);
  
  printf("The IP address of the client is %s",ipclient);
  
  printf("\n The received data is %s",str);
  
  sendto(Socketfd,str,strlen(str),0,(struct sockaddr*)&clientaddr,clientfd);

}

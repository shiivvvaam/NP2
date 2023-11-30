bcc.c
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

Bcs.c
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
int main(){
  char str[100];
  struct sockaddr_in servaddr,clientaddr;
  int broad=1,sock,s;
  sock=socket(AF_INET,SOCK_DGRAM,0);
  bzero(&servaddr,sizeof(servaddr));
  bzero(str,100);
  setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&broad,sizeof(broad));
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=inet_addr("192.168.64.255");
  servaddr.sin_port=htons(12345);
  s=sizeof(servaddr);
  while(1){
   printf("Enter the message to broadcast: \n");
   fgets(str,100,stdin);
   sendto(sock,str,sizeof(str),0,(struct sockaddr*)&servaddr,s);
  }
}

Multic.c
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
 int sockfd=socket(AF_INET,SOCK_DGRAM,0);
 struct sockaddr_in localSock;
 bzero(&localSock,sizeof(localSock));
 localSock.sin_family=AF_INET;
 localSock.sin_addr.s_addr=htonl(INADDR_ANY);
 localSock.sin_port=htons(5555);
 
 int reuse=1;
 setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
 bind(sockfd,(struct sockaddr*)&localSock,sizeof(localSock));
 
 struct ip_mreq group;
 group.imr_multiaddr.s_addr=inet_addr("226.1.1.1");
 group.imr_interface.s_addr=inet_addr("192.168.64.3");
 
 setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&group,sizeof(group));
 setsockopt(sockfd,IPPROTO_IP,IP_MULTICAST_IF,&group.imr_interface,sizeof(struct in_addr));
 printf("Multicast client is waiting...\n");
 char buffer[100];
 while(1){
  bzero(buffer,100);
  recv(sockfd,buffer,sizeof(buffer),0);
  printf("Received: %s\n",buffer);
 }
}

Multis.c
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
  int sockfd=socket(AF_INET,SOCK_DGRAM,0);
  struct sockaddr_in multicastAddr;
  multicastAddr.sin_family=AF_INET;
  multicastAddr.sin_addr.s_addr=inet_addr("226.1.1.1");
  multicastAddr.sin_port=htons(5555);
  
  int reuse=1;
  setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
  bind(sockfd,(struct sockaddr*)&multicastAddr,sizeof(multicastAddr));
  
  struct ip_mreq group;
  group.imr_multiaddr.s_addr=inet_addr("226.1.1.1");
  group.imr_interface.s_addr=inet_addr("192.168.64.3");
  
  setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,(char*)&group,sizeof(group));
  setsockopt(sockfd,IPPROTO_IP,IP_MULTICAST_IF,&group.imr_interface,sizeof(struct in_addr));
  
  printf("Multicast server is running...\n");
  
  char Message[100];
  while(1){
    bzero(Message,100);
    fgets(Message,100,stdin);
    sendto(sockfd,Message,sizeof(Message),0,(struct sockaddr*)&multicastAddr,sizeof(multicastAddr));
    sleep(2);
  }
  close(sockfd);
  return 0;
}

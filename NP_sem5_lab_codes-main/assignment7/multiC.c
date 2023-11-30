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

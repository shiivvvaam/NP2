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

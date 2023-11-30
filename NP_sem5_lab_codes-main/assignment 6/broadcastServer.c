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

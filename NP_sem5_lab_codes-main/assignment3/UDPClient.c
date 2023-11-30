#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(){
  int Socketfd,Slength,c1,c2;
  char str1[100],str2[100];
  char st[]="BYE";
  struct sockaddr_in serveraddr;
  bzero(&serveraddr,sizeof(serveraddr));
  bzero(str1,100);
  bzero(str2,100);
  Socketfd=socket(AF_INET,SOCK_DGRAM,0);
  
  serveraddr.sin_family=AF_INET;
  serveraddr.sin_port=htons(43450);
  serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  
  Slength=sizeof(serveraddr);
  fgets(str1,100,stdin);
  c1=sendto(Socketfd,str1,strlen(str1),0,(struct sockaddr*)&serveraddr,Slength);
  c2=recvfrom(Socketfd,str2,sizeof(str2),0,(struct sockaddr*)&serveraddr,&Slength);
  printf("c1 is %d",c1);
  printf("c2 is %d",c2);
  printf("Received data is %s",str2);
 
}

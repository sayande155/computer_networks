#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() 
{
  int sd;
  struct sockaddr_in sad;
  char str[50] = {'\0'};
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(1234);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(sd, (struct sockaddr *)&sad, sizeof(sad));
  do {
    printf("\nEnter message : ");
    gets(str);
    send(sd, str, sizeof(str), 0);
    recv(sd, str, sizeof(str), 0);
    printf("\nServer Says : %s", str);
  }while(strcmp(str, "bye"));
  close(sd);
}
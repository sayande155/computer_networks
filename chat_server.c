#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() 
{
  int sd, cd, cadl;
  struct sockaddr_in sad, cad;
  char str[50] = {'\0'};
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(1234);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  bind(sd, (struct sockaddr *)&sad, sizeof(sad));
  listen(sd, 10);
  cadl = sizeof(cad);
  cd = accept(sd, (struct sockaddr *)&cad, &cadl);
  do {
    recv(cd, str, sizeof(str), 0);
    printf("\nClient Says : %s", str);
    if(strcmp(str, "bye") == 0)
    {
      send(cd, str, sizeof(str), 0);
      break;
    }
    printf("\nEnter msg : ");
    gets(str);
    send(cd, str, sizeof(str), 0);
  }while(strcmp(str, "bye"));
  close(cd);
  close(sd);
}
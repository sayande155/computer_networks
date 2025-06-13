#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int count_ones(char *str) 
{
  int count = 0;
  for (int i = 0; i < strlen(str); i++) 
  {
    if (str[i] == '1')
      count++;
  }
  return count;
}

int main()
{
  int sd, cd, cadl;
  struct sockaddr_in sad, cad;
  char str[50] = {'\0'}, cw[50] = {'\0'};
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(9990);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  bind(sd, (struct sockaddr*)&sad, sizeof(sad));
  listen(sd, 10);
  cadl = sizeof(cad);
  cd = accept(sd, (struct sockaddr*)&cad, &cadl);
  recv(cd, str, sizeof(str), 0);
  printf("Received Codeword : %s\n",str);
  printf("Enter Codeword : ");
  gets(cw);
  int count = count_ones(cw);
  if(count % 2 == 0)
    printf("Accepted\n");
  else
    printf("Rejected\n");
  printf("*Even Parity Scheme*\n");
  close(cd);
  close(sd);
}
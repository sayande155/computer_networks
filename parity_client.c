#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
  int sd;
  struct sockaddr_in sad;
  char dw[50] = {'\0'}, opcw[50] = {'\0'}, epcw[50] = {'\0'}, op, ep;
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(9990);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(sd, (struct sockaddr *)&sad, sizeof(sad));
  printf("Enter dataword : ");
  gets(dw);
  int len = strlen(dw);
  int count = count_ones(dw);
  if (count % 2 == 0) 
  {
    op = '1';
    ep = '0';
  } 
  else 
  {
    op = '0';
    ep = '1';
  }
  strcpy(opcw, dw);
  strcpy(epcw, dw);
  printf("Odd Parity bit  : %c\n", op);
  printf("Even Parity bit : %c\n", ep);
  opcw[len] = op;
  epcw[len] = ep;
  printf("Odd Parity Codeword : %s\n", opcw);
  printf("Even Parity Codeword : %s\n", epcw);
  send(sd, epcw, sizeof(epcw), 0);
  close(sd);
}
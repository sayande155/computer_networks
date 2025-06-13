#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
  int sd;
  struct sockaddr_in sad;
  char dw[50] = {'\0'}, divisor[50] = {'\0'}, zeros[50] = {'\0'}, cpy_dw[50] = {'\0'};
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(1234);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(sd, (struct sockaddr*)&sad, sizeof(sad));
  printf("Enter dataword : ");
  gets(dw);
  strcpy(cpy_dw, dw);
  printf("Enter divisior : ");
  gets(divisor);
  int dw_len = strlen(dw);
  int div_len = strlen(divisor);
  for(int i = 0; i < div_len - 1; i++)
  {
    zeros[i] = '0';
  }
  strcat(cpy_dw, zeros);
  for(int i = 0; i < dw_len; i++)
  {
    if(cpy_dw[i] == '1')
    {
      for(int j = 0; j < div_len; j++)
      {
        cpy_dw[i+j] = (cpy_dw[i+j] == divisor[j]) ? '0' : '1';
      }
    }
  }
  for(int i = dw_len; i < dw_len + div_len - 1; i++)
  {
    dw[i] = cpy_dw[i]; 
  }
  printf("CRC codeword : %s\n", dw);
  send(sd, dw, sizeof(dw), 0);
  close(sd);
}
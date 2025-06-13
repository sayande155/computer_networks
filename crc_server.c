#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main()
{
  int sd, cd, cadl, cw_len, div_len;
  struct sockaddr_in sad, cad;
  char str[50] = {'\0'}, cw[50]  = {'\0'}, cpy_cw[50] = {'\0'}, divisor[50] = {'\0'};
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(1234);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  bind(sd, (struct sockaddr *)&sad, sizeof(sad));
  listen(sd, 10);
  cadl = sizeof(cad);
  cd = accept(sd, (struct sockaddr *)&cad, &cadl);
  recv(cd, str, sizeof(str), 0);
  printf("Received Codeword : %s\n", str);
  printf("Enter codeword : ");
  gets(cw);
  strcpy(cpy_cw, cw);
  printf("Enter divisor : ");
  gets(divisor);
  cw_len = strlen(cpy_cw);
  div_len = strlen(divisor);
  for(int i = 0; i <= cw_len - div_len; i++)
  {
    if(cpy_cw[i] == '1')
    {
      for(int j = 0; j < div_len; j++)
      {
        cpy_cw[i+j] = (cpy_cw[i+j] == divisor[j]) ? '0' : '1';
      }
    }
  }
  puts(cpy_cw);
  printf("CRC = ");
  int flag = 0;
  for(int i = cw_len - div_len + 1; i < cw_len; i++)
  {
    printf("%c", cpy_cw[i]);
    if(cpy_cw[i] == '1')
      flag = 1;
  }

  printf((flag == 0) ? "\nAccepted\n" : "\nRejected\n");


  close(cd);
  close(sd);
}
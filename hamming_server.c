#include<stdio.h> 
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>

void strRev(char *str)
{
  int i = 0;
  int j = strlen(str) - 1;
  while(i <= j)
  {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}

int b2d(char *bin)
{
  int dec = 0;
  int len = strlen(bin);
  for(int i = 0; i < len; i++)
  {
    dec += pow(2,i) * (bin[i] - 48);
  }
  return dec;
}

int main()
{
  int sd, cd, cadl;
  struct sockaddr_in sad, cad;
  char str[50] = {'\0'}, cw[50] = {'\0'}, parity[50] = {'\0'};
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(1234);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  bind(sd, (struct sockaddr*)&sad, sizeof(sad));
  listen(sd, 10);
  cadl = sizeof(cad);
  cd = accept(sd, (struct sockaddr*)&cad, &cadl);
  recv(cd, str, sizeof(str), 0);
  printf("Received Codeword : %s\n", str);
  printf("Enter codeword : ");
  gets(cw);
  int len = strlen(cw);
  int r = 0;
  for(int i = 0; i < len; i++)
  {
    if(pow(2, i) > len)
    {
      r = i;
      break;
    }
  }
  strRev(cw);
  puts(cw);
  for(int i = 0; i < r; i++)
  {
    parity[i] = 0;
  }

  int x = 0;
  for(int i = 0; i < r; i++)
  {
    int position = pow(2, i) - 1;
    int p = 0;
    for(int j = position; j < len; j += 2 * (position + 1))
    {
      for(int k = 0; k < position + 1 && (j + k) < len; k++)
      {
        p ^= cw[j+k] - 48;
      }
    }
    parity[x++] = p + 48;
  }
  int decimal = b2d(parity);
  strRev(parity);
  printf("\nParity bits : %s\n", parity);
  printf("\nError Position : %d\n", decimal);
  cw[decimal - 1] = (cw[decimal - 1] == '0') ? '1' : '0';
  strRev(cw);
  printf("\nCorrected Data : %s\n", cw);
  close(cd);
  close(sd);
}
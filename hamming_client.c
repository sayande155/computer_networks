#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<math.h>
void strRev(char *str)
{
  int len = strlen(str);
  int i = 0;
  int j = len - 1;
  while(i <= j)
  {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
    i++;
    j--;
  }
}

int isPowerOfTwo(int i)
{
  return (i & (i-1)) == 0;
}

int main()
{
  int sd;
  struct sockaddr_in sad;
  char dw[50] = {'\0'}, rev_dw[50] = {'\0'}, cw[50] = {'\0'};
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(1234);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(sd, (struct sockaddr*)&sad, sizeof(sad));

  printf("Enter dataword : ");
  gets(dw);
  int m = strlen(dw);
  int r = 0;
  for(int i = 0; i < m; i++)
  {
    if(pow(2,i) > m + i)
    {
      r = i;
      break;
    }
  }

  strcpy(rev_dw, dw);
  strRev(rev_dw);
  
  int len = m + r;
  int j = 0;
  for(int i = 0; i < len; i++)
  {
    if(isPowerOfTwo(i+1))
    {
      cw[i] = '9';
    }
    else
    {
      cw[i] = rev_dw[j++];
    }
  }

  for(int i = 0; i < r; i++)
  {
    int position = pow(2, i) - 1;
    int p = 0;
    for(int j = position; j < len; j += (2 * (position + 1)))
    {
      for(int k = 0; k < position+1 && (j+k) < len; k++)
      {
        if(cw[j+k] != '9')
          p ^= cw[j+k] - 48;
      }
    }
    cw[position] = p + 48;
  }
  strRev(cw);
  puts(cw);
  send(sd, cw, sizeof(cw), 0);
  close(sd);
}
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() 
{
  int sd, cd, cadl, seg_len, dw_len, sum[100]= {0}, carry = 0;
  struct sockaddr_in sad, cad;
  char str[100] = {'\0'}, dw[100] = {'\0'}, checksum[100] = {'\0'};
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(9989);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  bind(sd, (struct sockaddr *)&sad, sizeof(sad));
  listen(sd, 10);
  cadl = sizeof(cad);
  cd = accept(sd, (struct sockaddr *)&cad, &cadl);
  recv(cd, str, sizeof(str), 0);
  printf("Received dataword : %s\n", str);
  printf("Enter dataword : ");
  gets(dw);
  printf("Enter segment length : ");
  scanf("%d", &seg_len);
  dw_len = strlen(dw);
  for(int i = 0; i < dw_len; i += seg_len)
  {
    int temp = seg_len - 1;
    for(int j = i + seg_len - 1; j >= i; j--)
    {
      int temp_sum = (sum[temp]) + (dw[j] - 48) + carry;
      sum[temp] = temp_sum % 2;
      carry = temp_sum / 2;
      temp--;
    }
    if(carry != 0)
    {
      for(int j = seg_len - 1; j >= i; j--)
      {
        int temp_sum = (sum[temp]) + carry;
        sum[temp] = temp_sum % 2;
        carry = temp_sum / 2;
        temp--;
      }
    }
  }

  int flag = 0;
  for(int i = 0; i < seg_len; i++)
  {
    sum[i] = ((sum[i] == 0) ? 1 : 0);
    checksum[i] = sum[i] + 48;
    if(sum[i] != 0)
      flag = 1;
  }
  printf("Checksum : ");
  printf("%s\n", checksum);
  if(flag == 0)
  {
    printf("Accepted\n");  
  }
  else
  {
    printf("Rejected\n");
  }
  close(cd);
  close(sd);
}
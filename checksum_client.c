#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() 
{
  int sd, seg_len, dw_len, checksum[100] = {0};
  struct sockaddr_in sad;
  char dw[100] = {'\0'}, temp_str[100] = {'\0'};
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  sad.sin_family = AF_INET;
  sad.sin_port = htons(9989);
  sad.sin_addr.s_addr = inet_addr("127.0.0.1");
  connect(sd, (struct sockaddr *)&sad, sizeof(sad));
  printf("Enter dataword : ");
  gets(dw);
  printf("Enter segment length : ");
  scanf("%d", &seg_len);
  dw_len = strlen(dw);
  int temp = dw_len % seg_len;
  if (temp != 0) 
  {
    for (int i = 0; i < (seg_len - temp); i++)
    {
      temp_str[i] = '0';
    }
    strcat(temp_str, dw);
    strcpy(dw, temp_str);
  }
  int carry = 0;
  for(int i = 0; i < dw_len; i += seg_len)
  {
    int temp = seg_len - 1;
    for(int j = i + seg_len - 1; j >= i; j--)
    {
      int sum = (checksum[temp]) + (dw[j] - 48) + carry;
      checksum[temp] = sum % 2;
      carry= sum / 2;
      temp--;
    }
    if(carry != 0)
    {
      for(int j = seg_len - 1;  j >= 0; j--)
      {
        int sum = (checksum[j]) + carry;
        checksum[j] = sum % 2;
        carry = sum / 2;
      }
    }
  }
  for(int i = 0; i < seg_len; i++) 
  {
    checksum[i] = (checksum[i] == 0) ? 1 : 0;
    temp_str[i] = checksum[i] + 48;
  }
  printf("Checksum : ");
  printf("%s",temp_str);
  strcat(dw, temp_str);
  send(sd, dw, sizeof(dw), 0);
  close(sd);
}
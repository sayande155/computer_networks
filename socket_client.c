#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int sd, cadl;
    struct sockaddr_in sad;
    char str[50];
    sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sad.sin_family = AF_INET;
    sad.sin_port = htons(9989);
    sad.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(sd, (struct sockaddr*)&sad, sizeof(sad));
    printf("Enter string : ");
    gets(str);
    send(sd, str, sizeof(str), 0);
    close(sd);
}
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERV_IP "192.168.0.109"
#define SERV_PORT 2809

int main()
{
    int cli_fd, ret;
    struct sockaddr_in serv_addr;
    char msg[512];
   
    cli_fd = socket(AF_INET, SOCK_STREAM, 0);
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr.sin_port = htons(SERV_PORT);
    ret = connect(cli_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    do
    {
        
        printf("client> ");
        fgets(msg, sizeof(msg), stdin);
        
        write(cli_fd, msg, strlen(msg) + 1);
        
        read(cli_fd, msg, sizeof(msg));
        
        printf("server> %s", msg);
    } while (strcmp(msg, "bye\n") != 0);
   
    close(cli_fd);
    return 0;
}

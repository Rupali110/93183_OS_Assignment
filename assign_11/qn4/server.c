

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
    int serv_fd, cli_fd, ret;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clisock_len = sizeof(cli_addr);
    char msg[512];

    
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
  
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr.sin_port = htons(SERV_PORT);
    ret = bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
   
    listen(serv_fd, 5);
   
    memset(&cli_addr, 0, sizeof(cli_addr));
    cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &clisock_len);
    do
    {
       
        read(cli_fd, msg, sizeof(msg));
     
        printf("client> %s", msg);
      
        printf("server> ");
        fgets(msg, sizeof(msg), stdin);
      
        write(cli_fd, msg, strlen(msg) + 1);
    } while (strcmp(msg, "bye\n") != 0);
   

  
    close(cli_fd);
   
    shutdown(serv_fd, SHUT_RDWR);
    return 0;
}

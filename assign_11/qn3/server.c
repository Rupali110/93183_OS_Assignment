#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 2809

int main() {
    int serv_fd, cli_fd;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);

    serv_fd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr.sin_port = htons(SERV_PORT);

    bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(serv_fd, 5);

    printf("Server listening on %s:%d...\n", SERV_IP, SERV_PORT);

    cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &cli_len);

    int a, b, result;
    char op;

    while (1) {
       
        read(cli_fd, &a, sizeof(int));
        read(cli_fd, &b, sizeof(int));
        read(cli_fd, &op, sizeof(char));

        if (op == 'q') break;

      
        switch (op) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': result = (b != 0) ? a / b : 0; break;
            default: result = 0;
        }

     
        write(cli_fd, &result, sizeof(int));
    }

    close(cli_fd);
    close(serv_fd);
    return 0;
}


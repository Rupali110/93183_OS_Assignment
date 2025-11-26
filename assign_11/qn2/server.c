#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/calc_socket"

int main() {
    int serv_fd, cli_fd;
    struct sockaddr_un addr;
    socklen_t addr_len;

    
    serv_fd = socket(AF_UNIX, SOCK_STREAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);
    unlink(SOCKET_PATH); 

    bind(serv_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(serv_fd, 5);

    printf("Server listening...\n");

    cli_fd = accept(serv_fd, NULL, NULL);

    int a, b, result;
    char op;

    while (1) {
        read(cli_fd, &a, sizeof(int));
        read(cli_fd, &b, sizeof(int));
        read(cli_fd, &op, sizeof(char));

        if (op == 'q') break; 

        switch(op) {
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
    unlink(SOCKET_PATH);
    return 0;
}


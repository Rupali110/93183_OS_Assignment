#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/calc_socket"

int main() {
    int sock;
    struct sockaddr_un addr;

    sock = socket(AF_UNIX, SOCK_STREAM, 0);

    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, SOCKET_PATH);

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));

    int a, b, result;
    char op;

    while (1) {
        printf("Enter two numbers: ");
        scanf("%d %d", &a, &b);
        printf("Enter operation (+, -, *, /) or q to quit: ");
        scanf(" %c", &op);

        write(sock, &a, sizeof(int));
        write(sock, &b, sizeof(int));
        write(sock, &op, sizeof(char));

        if (op == 'q') break;

        read(sock, &result, sizeof(int));
        printf("Result = %d\n", result);
    }

    close(sock);
    return 0;
}


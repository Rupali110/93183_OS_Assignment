#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 2809

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    int a, b, result;
    char op;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_addr.sin_port = htons(SERV_PORT);

    connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    while (1) {
        printf("Enter two numbers: ");
        scanf("%d %d", &a, &b);
        printf("Enter operation (+, -, *, /) or q to quit: ");
        scanf(" %c", &op);

        write(sock, &a, sizeof(int));
        write(sock, &b, sizeof(int));
        write(sock, &op, sizeof(char));

        if (op == 'q')
            break;

        read(sock, &result, sizeof(int));
        printf("Result = %d\n", result);
    }

    close(sock);
    return 0;
}


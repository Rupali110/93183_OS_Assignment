#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define MQ_KEY 1234
#define BUF_SIZE 512

struct msgbuf {
    long mtype;
    char fifo_name[100];
    char file_name[100];
};

int main() {
    int mqid;
    struct msgbuf msg;
    char buffer[BUF_SIZE];

    mqid = msgget(MQ_KEY, 0666);
    if (mqid < 0) {
        perror("msgget");
        exit(1);
    }

    
    printf("Enter FIFO name (e.g., /tmp/myfifo): ");
    scanf("%s", msg.fifo_name);
    printf("Enter file name to request: ");
    scanf("%s", msg.file_name);

   
    mkfifo(msg.fifo_name, 0666);

   
    msg.mtype = 1;
    msgsnd(mqid, &msg, sizeof(msg) - sizeof(long), 0);

    
    int fdr = open(msg.fifo_name, O_RDONLY);
    if (fdr < 0) {
        perror("open fifo");
        exit(1);
    }

    
    int fdw = open("received_file.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fdw < 0) {
        perror("open output");
        exit(1);
    }

    
    int n;
    while ((n = read(fdr, buffer, BUF_SIZE)) > 0)
        write(fdw, buffer, n);

    printf("File received successfully and saved as received_file.txt\n");

    close(fdr);
    close(fdw);
    unlink(msg.fifo_name); 
    return 0;
}


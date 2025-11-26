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

  
    mqid = msgget(MQ_KEY, IPC_CREAT | 0666);
    if (mqid < 0) {
        perror("msgget");
        exit(1);
    }

    printf("Server ready...\n");

  
    msgrcv(mqid, &msg, sizeof(msg) - sizeof(long), 1, 0);
    printf("Received request:\nFIFO: %s\nFile: %s\n", msg.fifo_name, msg.file_name);

  
    int fdr = open(msg.file_name, O_RDONLY);
    if (fdr < 0) {
        perror("open file");
        exit(1);
    }

 
    int fdw = open(msg.fifo_name, O_WRONLY);
    if (fdw < 0) {
        perror("open fifo");
        exit(1);
    }

   
    int n;
    while ((n = read(fdr, buffer, BUF_SIZE)) > 0)
        write(fdw, buffer, n);

    close(fdr);
    close(fdw);
    printf("File sent successfully.\n");

    
    return 0;
}


#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/wait.h>
#include<sys/msg.h>
#include<stdlib.h>
#define msgkey 0x1234
struct msgbuf
{
	long type;
	char text[20];
}m1,m2;

void main(void)
{
	char *msg;
	int num[10];
	int i,msgid,ret,ret2,ret3,sum=0;
	msgid=msgget(msgkey,IPC_CREAT|0600);
	if(msgid==-1)
	{
		perror("message queue failed !!!...\n");
		_exit(-1);
	}


	ret=fork();
	if(ret==-1)
	{
		perror("fork failed !!...\n");
		_exit(-1);
	}
	else if(ret==0)
	{
		m1.type=11;
		printf("Child : Enter message> ");
		scanf("%[^\n]s",m1.text);
		printf("\n");
        ret2=msgsnd(msgid,&m1,sizeof(m1.text),0);
		if(ret2==-1)
		{
			perror("child :msgsnd failed !!...\n");
			_exit(-1);
		}
		printf("child :Message sended\n");

		printf("child waiting for message \n");
		ret2=msgrcv(msgid,&m1,sizeof(m1.text),22,0);
		if(ret2==-1)
		{
			perror("child :msgrcv failed !!!\n");
			_exit(-1);
		}

		printf("child :Message received : %s\n",m1.text);
		_exit(0);
	}
	else
	{
		printf("Parent waiting for message \n");
		ret3=msgrcv(msgid,&m2,sizeof(m2.text),11,0);
		if(ret3==-1)
		{
			perror("parent :msgrcv failed !!!\n");
			_exit(-1);
		}

		printf("parent :Message received : %s\n",m2.text);
		i=0;
		msg=strtok(m2.text," ");
		do
		{
			num[i]=atoi(msg);
			msg=strtok(NULL," ");
			i++;
		}while(msg!=NULL);
		for(int j=0;j<i;j++)
		{
			sum+=num[j];
		}

		m2.type=22;
		sprintf(m2.text,"Sum is :%d",sum);
        ret3=msgsnd(msgid,&m2,sizeof(m2.text),0);
		if(ret3==-1)
		{
			perror("child :msgsnd failed !!...\n");
			_exit(-1);
		}
		printf("parent :Message sended\n");
		msgctl(msgid,IPC_RMID,NULL);
     	int s;
    	wait(&s);
    	printf("exit status : %d\n",s);
	}
}

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
void main(void)
{
	printf("Program started\n");
	int s,sum=0,i,num[10],arr1[2],arr2[2],ret1,ret2;
	char msg[20];
	ret1=pipe(arr1);
	if(ret1==-1)
	{
		printf("pipe failed !!....\n");
		_exit(-1);
	}

	ret2=pipe(arr2);
	if(ret2==-1)
	{
		printf("pipe failed !!....\n");
		_exit(-1);
	}


	int pid =fork();
	if(pid==0)
	{
		close(arr1[0]);
		close(arr2[1]);
		printf("child :writing two numbers \n");
		printf("Enter message> ");
		scanf("%[^\n]s",msg);
		write(arr1[1],msg,strlen(msg));
		printf("child :sended\n");
		close(arr1[1]);

		printf("child :Waiting for the message\n");
		read(arr2[0],msg,sizeof(msg));
		printf("child :Message received :%s\n",msg);
		close(arr1[1]);
		close(arr2[0]);
	}
	else
	{
		close(arr1[1]);
		close(arr2[0]);
		printf("parent :Waiting for the message\n");
		read(arr1[0],msg,sizeof(msg));
		printf("parent :Message received :%s\n",msg);
		char *m=strtok(msg," ");
		do
		{
			sum+=atoi(m);
			m=strtok(NULL," ");
		}while(m!=NULL);
		printf("parent :writing result \n");
		sprintf(msg,"Sum :%d",sum);
		write(arr2[1],msg,strlen(msg));
		printf("parent :sended\n");
	
		close(arr1[0]);
		close(arr2[1]);
		wait(&s);
		printf("EXIT status :%d\n",s);
	}
}




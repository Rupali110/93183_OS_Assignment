#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void main(void)
{
	int ret1,ret2,ret3,ret4,ret5,ret6,status;
	int retexec1,retexec2,retexec3,retexec4,retexec5,retexec6;
	ret1=fork();
	if(ret1==0)
	{
		retexec1=execlp("gcc","gcc","-c","circle.c",NULL);
		if(retexec1==-1)
		{
			printf("Circle failed\n");
			exit(-1);
		}
		_exit(0);
	}
	ret2=fork();
	if(ret2==0)
	{
		retexec2=execlp("gcc","gcc","-c","square.c",NULL);
		if(retexec2==-1)
		{
			printf("square failed\n");
			exit(-1);
		}
		_exit(0);
	}
	ret3=fork();
    if(ret3==0)
	{
		retexec3=execlp("gcc","gcc","-c","rectangle.c",NULL);
		if(retexec3==-1)
		{
			printf("Rectangle failed\n");
			exit(-1);
		}
		_exit(0);
	}
	ret4=fork();
	if(ret4==0)
	{
		retexec4=execlp("gcc","gcc","-c","main.c",NULL);
		if(retexec4==-1)
		{
			printf("Main failed\n");
			exit(-1);
		}
		_exit(0);
	}
	for(int i=0;i<4;i++)
	{
		wait(&status);
		printf("Parent exit status %d:%d\n",i,WEXITSTATUS(status));
		if(WEXITSTATUS(status)==0)
		{
			printf("Success\n\n");
		}
	}
	ret5=fork();
	if(ret5==0)
	{
		retexec5=execlp("gcc","gcc","-o","program.out","main.o","circle.o","square.o","rectangle.o",NULL);
		if(retexec5==-1)
		{
			printf("Linking failed\n");
			exit(-1);
		}
		_exit(0);
	}
	wait(&status);
	printf("Parent: exit status :%d\n",WEXITSTATUS(status));
	if(WEXITSTATUS(status)==0)
	{
	   printf("Success\n\n");
	}
	ret6=fork();
	if(ret6==0)
	{
		retexec6=execlp("./program.out","./program.out",NULL);
		if(retexec6==-1)
		{
			printf("Running failed\n");
			exit(-1);
		}
		_exit(0);
	}
	wait(&status);
	printf("Program exit status :%d\n",WEXITSTATUS(status));
}

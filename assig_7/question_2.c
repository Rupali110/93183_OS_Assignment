#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

void main(void)
{
	int ret1,ret2,ret3;

	printf("Program started\n");
	ret1=fork();
	if(ret1==0)
	{
		printf("Child 1 here\n");
		ret2=fork();
		if(ret2==0)
		{
			printf("Child 2 here\n");
			ret3=fork();
			if(ret3==0)
			{
				printf("Child 3 here\n");
				sleep(5);
				exit(0);
				
			}
			else
			{
				waitpid(ret3,NULL,0);
				printf("parent of child 3 exited\n");
			}
			sleep(5);
			exit(0);
		}
		else
		{
			waitpid(ret2,NULL,0);
			printf("parent of child 2 exited\n");

		}
		sleep(5);
		exit(0);

	}
	else
	{
		waitpid(ret1,NULL,0);
		printf("Parent of child 1 exited \n");
	}
}


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

void main(void)
{
	int ret,i;
	
	for(i=1;i<=5;i++)
	{
		ret=fork();
		if(ret==0)
		{
			printf("Hello iam a child no : %d\n",i);
			sleep(5);
			printf("Done %d\n",i);
			exit(0);
		}

	}
	for(i=1;i<=5;i++)
	{
		wait(NULL);
		printf("Iam parent no :%d waiting \n",i);
	}
	printf("All done...bye...bye\n");

}

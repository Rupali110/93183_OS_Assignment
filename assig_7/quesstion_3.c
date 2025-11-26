#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int main(void)
{
	printf("Program started !!!\n");
	int count=0;
	int ret;
	while(1)
	{
		ret=fork();
		if(ret<0)
		{
			printf("Process creation failed \n");
			printf("Maximum created processes : %d\n\n",count);
			break;
		}
		else if(ret==0)
		{
			exit(0);
		}
		else
		{
			count++;
		}
	}
		
	while(wait(NULL)>0);
	return 0;
}

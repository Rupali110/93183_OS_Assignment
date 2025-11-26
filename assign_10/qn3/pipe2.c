#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
void main(void)
{
	int arr[2];
	if(pipe(arr)==-1)
	{
		perror("pipe failed !!\n");
		_exit(-1);
	}

	int ret1=fork();

	if(ret1==0)
	{
		printf("child block entered\n");
		close(arr[0]);
		dup2(arr[1],1);
		close(arr[1]);
		execlp("who","who",NULL);
		_exit(0);

	}

	int ret2=fork();

	if(ret2==0)
	{
		printf("child block\n");
		close(arr[1]);
		dup2(arr[0],0);
		close(arr[0]);
		execlp("wc","wc",NULL);
		_exit(0);
	}
	close(arr[0]);
	close(arr[1]);

	waitpid(ret1,NULL,0);
	waitpid(ret2,NULL,0);
	
}


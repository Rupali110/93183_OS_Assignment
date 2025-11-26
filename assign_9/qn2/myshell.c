#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
void sigchld_handler(int sig)
{
	while(waitpid(-1,NULL,WNOHANG)>0);
}
void main(void)
{
	char str[256];
	char *token[20];
	char *ptr;
	int i;
	signal(SIGCHLD,sigchld_handler);
	while(1)
	{
		printf("cmd> ");
		gets(str);
		i=0;
		ptr=strtok(str," ");
		while(ptr!=NULL)
		{
			token[i]=ptr;
			ptr=strtok(NULL," ");
			i++;
		}
		token[i]=NULL;
		if(strcmp(token[0],"exit")==0)
		{
			_exit(0);
		}
		else if (strcmp(token[0],"cd")==0)
		{
			chdir(token[1]);
		}
		else
		{
			int retchild,retexec,flag=0;
			int last=i-1;
			if(strcmp(token[last],"&")==0)
			{
				flag=1;
				token[last]=NULL;
			}
			retchild= fork();
			if(retchild==0)
			{
				retexec=execvp(token[0],token);
				if(retexec==-1)
				{
					printf("Exec failed..\n");
				}
				_exit(0);
			}
			if(flag)
			{
				printf("Not waiting for child PID:%d\n",retchild);
			}
			else
			{
		    	wait(NULL);
			}
		}

	}
}


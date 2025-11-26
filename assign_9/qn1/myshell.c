#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
void sigint_handler(int sig)
{
	;
}
void main(void)
{
	char str[256];
	char *token[20];
	char *ptr;
	int i;
	signal(SIGINT,sigint_handler);
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
			int retchild,retexec;
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
			wait(NULL);
		}

	}
}


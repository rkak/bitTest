#include <stdio.h>		// printf()
#include <unistd.h>		// fork()
#include <wait.h>		// wait()
#include <signal.h>		// signal(), kill()
#include <stdlib.h>
#include <string.h>


static void sig_handler(int signum)
{
		printf("I got signal : signum=%d\n",signum);
		exit(0);
}


int main(void)
{
		pid_t pid;
		char *temp;


		temp = strsignal(SIGINT);
		printf("%s\n", temp);
		temp = strsignal(SIGKILL);


		pid=fork();

		//자식 프로세스일 경우
		if(pid==-1)
		{
				printf("Error:fork pid=-1");
				return -1;
		}
		else if(pid==0)
		{
				// signal which can't be registed handler
				// use 'if' for confirming what I can get to know the signal
				if(signal(SIGKILL,sig_handler) == SIG_ERR)
						printf("\ncan't catch SIGKILL\n");
				if(signal(SIGINT, sig_handler) == SIG_ERR)
						printf("\ncan't catch SIGINT\n");
				while(1)
				{
						printf("Hello world\n");
						sleep(1);
				}
		}
		else
		{
				sleep(10);
				kill(pid,SIGKILL);
		}

		wait(NULL);
		return 0;
}


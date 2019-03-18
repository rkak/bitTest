#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sigHandler(int sig){
		printf("Raise() : I got siganl %d\n", sig);
		(void)signal(SIGINT, SIG_DFL);
}

int main(void){
		int count = 0;
		signal(SIGINT, sigHandler);
		sleep(1);

		while(1){
				count++;
				printf("Hello Wolrd\n");
				if(count == 3){
						raise(SIGINT);
						count = 0;
				}
		}
		sleep(1);
}

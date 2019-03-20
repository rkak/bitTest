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
						// send a signal(here, SIGINT) to processorself. if it has threads, they can be received that signal
						raise(SIGINT);
						count = 0;
				}
		}
		sleep(1);
}

#include <unistd.h>	// fork()
#include <stdio.h>	// printf()
#include <sys/types.h>	// some types
#include <wait.h>	// wait()
#include <stdlib.h>	// exit()

#define MYTIME 20

int main(void){
		pid_t pid;
		char * message;
		int n;
		
		printf("fork program starting\n");

		switch(pid = fork()){
				case -1: perror("fork failed");
						 exit(1);
				case 0: message = "This is the child";
						n = 3;
						break;
				default: message = "This is the parent";
						 n = 5;
						 break;
		}

		for(; n > 0; n--){
				puts(message);
				sleep(1);
		}
		if(pid >0){
				// after execute and printed above all, put the shell instrument ps -al and confirm that the child process is zombie.
				printf("Child Proc State : Zombie, about %d sec\n", MYTIME);
				sleep(MYTIME);
				wait(NULL);
		}
		exit(0);

}

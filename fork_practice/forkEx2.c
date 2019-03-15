#include <unistd.h>	// fork()
#include <stdio.h>	// printf()
#include <sys/types.h>	// some types
#include <wait.h>	// wait()
#include <stdlib.h>	// exit()

int main(void){
		pid_t pid;
		char * message;
		int n;
		int status;
		
		printf("fork program starting\n");

		switch(pid = fork()){
				case -1: perror("fork failed");
						 exit(1);
				case 0: message = "This is the child";
						n = 5;
						break;
				default: message = "This is the parent";
						 n = 3;
						 break;
		}

		for(; n > 0; n--){
				puts(message);
				sleep(1);
		}
		if(pid)
				wait(&status);
		exit(0);

}

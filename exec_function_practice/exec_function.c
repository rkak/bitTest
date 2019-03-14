#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// this code is for kind of exec function

int main(int argc, char * argv[]){
		printf("Running ps with execlp\n");

		int num = atoi(argv[1]);
		char numChr[10];

		num++;

		sprintf(numChr, "%d", num);

		char *const ps_envp[] = {"PATH = ~/linux_exercise/exec_function_practice", (char *)0};
		char *const arg[] = {"exec_function", numChr, NULL};

		switch(num){
		case 0:
				printf("execl() : path, arg in hand\n");
				execl("./exec_function", "exec_function", numChr, NULL); 
				break;
		case 1:
				printf("execlp() : $PATH, arg in hand\n");
				execlp("exec_function", "exec_function", numChr, NULL); 
				break;
		case 2:
				printf("execle() : $PATH in hand, arg in hand\n");
				execle("exec_function", "exec_function", numChr, NULL, ps_envp); 
				break;
		case 3:
				printf("execv() : path, arg\n");
				execv("./exec_function", arg); 
				break;
		case 4:
				printf("execvp() : $PATH, arg\n");
				execvp("exec_function", arg); 
				break;
		case 5:
				printf("execve() : $PATH in hand, arg\n");
				execve("exec_function", arg, ps_envp); 
				break;
		}

		printf("Done.\n");
		exit(0);


}

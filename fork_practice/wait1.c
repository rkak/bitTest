#include <sys/types.h>	// pid_t
#include <sys/wait.h>	// wait()
#include <unistd.h>		// fork()
#include <stdio.h>		// printf()
#include <stdlib.h>		// exit()

void pr_exit(int status){
		// regular exit
		if(WIFEXITED(status))
				printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
		// exit by signal
		else if(WIFSIGNALED(status))
				printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status), WCOREDUMP(status) ?"(core file generated)" : "");
		// stop by signal
		else if(WIFSTOPPED(status))
				printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}


int main(void){
		pid_t pid;
		char * msg;
		int n;
		int exit_code;

		printf("fork program starting\n");
		pid = fork();
		switch(pid){
				case -1 : perror("fork failed");
						 exit(1);
				case 0 : msg = "This is the child";
						 n = 5;
						 exit_code = 37;
						 break;
				default : msg = "This is the parent";
						  n = 3;
						  exit_code = 0;
						  break;
		}
		for(; n > 0; n--){
				puts(msg);
				sleep(1);
		}

		if(pid){
				int stat_val;
				pid_t child_pid;
				child_pid = wait(&stat_val);
				printf("Child has finished: PID = %d\n", child_pid);
				pr_exit(stat_val);
		}
		exit(exit_code);

}

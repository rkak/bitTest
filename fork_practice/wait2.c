#include <stdio.h>	// printf()
#include <sys/types.h>	// pid_t
#include <unistd.h>	// fork()
#include <stdlib.h>	// exit()
#include <sys/wait.h>	// wait()

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
		pid_t pid; int status;
		if( (pid = fork()) < 0)
				perror("fork error");
		else if(pid == 0) exit(7);		// normal exit of child

		if(wait(&status) == pid)		// wait for child
				pr_exit(status);
		
		if( (pid = fork()) < 0)
				perror("fork error");
		else if(pid == 0) abort();		// child : generates SIGABRT

		if(wait(&status) == pid)		// wait for child
				pr_exit(status);

		if( (pid = fork()) < 0)
				perror("fork error");
		else if(pid == 0) status /= 0;		// child : divide by  0 nerates SIGFPE

		if(wait(&status) == pid)		// wait for child
				pr_exit(status);
}

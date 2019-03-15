#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>	// wait()

int main(void){
		pid_t pid;
		int x = 0;
		int status;
		x = 1;

		if((pid = fork()) == 0){
				printf("pid = %ld I am process %ld ppid = %ld\n", (long)pid, (long)getpid(), (long)getppid());
				sleep(1);
				printf("Done\n");
				return 0;
		}
		else{
				printf("pid = %ld I am process %ld\n", (long)pid, (long)getpid());
		}

		wait(&status);

		return 0;
}

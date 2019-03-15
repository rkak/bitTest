#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void){
		pid_t pid;
		int x = 0;

		pid = fork();

		x = 1;

		if(!pid){
				printf("pid = %ld I am process %ld ppid = %ld\n", (long)pid, (long)getpid(), (long)getppid());
				sleep(1);
				printf("Done\n");
		}
		else{
				printf("pid = %ld I am process %ld\n", (long)pid, (long)getpid());
		}

		return 0;
}

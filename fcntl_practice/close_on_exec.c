#include <unistd.h>	// close(), write(), execl(), execlp()
#include <fcntl.h>	// open(), O_CREAT
#include <stdio.h>

#define DEBUG

int main(){
		int fd;
		int val;
		fd = open("exec_copy.txt", O_CREAT | O_TRUNC, 0644); // O_TRUNC : if file existed, cover it

	//	execute loop program
	//	execl("./loop", "./loop", (char *)0);
	//	execlp("ls -al", "ls -al", (char *)0);	// make child process like fork()
												// copy fds to child process
		val = fcntl(fd, F_GETFD, 0);

#ifdef DEBUG
		if(val & FD_CLOEXEC)
				printf("Before : close-on-exec bit on\n");
		else
				printf("Before : close-on-exec bit off\n");
#endif

		val |= FD_CLOEXEC;

#ifdef DEBUG
		if(val & FD_CLOEXEC)
				printf("After : close-on-exec bit on\n");
		else
				printf("After : close-on-exec bit off\n");
#endif

		fcntl(fd, F_SETFD, val);

		execl("./loop", "./loop", (char *)0);
		
		close(fd);

		return 0;
}

#include <unistd.h>	// dup(), close(), STDOUT_FILENO
#include <stdio.h>	// printf()
#include <fcntl.h>	// creat(), open()

int main(void){
		int fd, fd2;
		fd = creat("dup_result", 0644);
		fd2 = dup2(fd, STDOUT_FILENO);

		printf("fd : %d, fd2 : %d\n", fd, fd2);

		close(fd);
		
		printf("Hello world!\n");

		close(fd2);
		return 0;
}

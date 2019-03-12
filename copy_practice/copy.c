//ex)  copy a.txt b.txt

#include <stdio.h> // printf()
#include <fcntl.h> // O_RDONLY, O_WRONLY, O_RDWR
#include <unistd.h> // read(), write(), open(), close()
#define BUF_SIZE 1024

// #define DEBUG

int main(int argc, char *argv[]){
	int fd1, fd2, len;
	char buf[BUF_SIZE];

#ifdef DEBUG
	printf("argc : %d\n", argc);
	printf("argv[1] : %s\n", argv[1]);
	printf("argv[2] : %s\n", argv[2]);
#endif

	fd1 = open(argv[1], O_RDONLY); // Open read file
	fd2 = open(argv[2], O_WRONLY | O_CREAT); // Open write file

	// read & write
	while((len = read(fd1, buf, sizeof(buf))) > 0)
		write(fd2, buf, len);

	close(fd1);
	close(fd2);

	return 0;

}

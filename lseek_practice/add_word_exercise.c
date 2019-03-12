#include <stdio.h>	// printf()
#include <unistd.h>	// lseek(), close(), write(), SEEK_CUR, SEEK_END, SEEK_SET
#include <fcntl.h>	// open(), O_RDWR, O_RDONLY, O_WRONLY
#include <string.h>	// strlen()

int main(void){
	int fd;
	char buf[100];

	fd = open("test.txt", O_RDWR);
	if(fd < 0)
			printf("%s open error\n", "test.txt");
	lseek(fd, 34, SEEK_SET);
	read(fd, buf, 100);

	lseek(fd, 34 + 9, SEEK_SET);
	write(fd, buf, strlen(buf));

	lseek(fd, 34, SEEK_SET);
	write(fd, "vehicles ", 9);

	close(fd);

	return 0; 


}

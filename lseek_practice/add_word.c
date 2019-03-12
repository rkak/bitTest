#include <stdio.h>
#include <unistd.h>	// close(), write(), lseek(), SEEK_CUR, SEEK_SET, SEEK_END
#include <fcntl.h>	// open()
#include <string.h>	// strlen(), strstr()

#define DEBUG

int main(void){
	int fd;
	char buf[100];
	char words[1000];
	char * target;
	char add_word[10];
	int target_location;

	memset(add_word, 0, sizeof(add_word));
	sprintf(add_word, "vehicles ");
	fd = open("test.txt", O_RDWR);
	if(fd < 0)
			printf("%s open error", "test.txt");

#ifdef DEBUG
	printf("fd : %d\n", fd);
#endif

	read(fd, words, 1000);

#ifdef DEBUG
	printf("read words : %s\n", words);
#endif

	target = strstr(words, "after");
	target_location = (target - words) / sizeof(char);

#ifdef DEBUG
	printf("target location : %d\n", target_location);
#endif

	int offset = lseek(fd, target_location, SEEK_SET);

#ifdef DEBUG
	printf("cur offset : %ld\n", lseek(fd, 0, SEEK_CUR));
#endif

	read(fd, buf, 100);

#ifdef DEBUG
	printf("read buf : %s\n", buf);
#endif

	lseek(fd, target_location + strlen(add_word), SEEK_SET);
	write(fd, buf, strlen(buf));
	offset = lseek(fd, target_location, SEEK_SET);
	int wt = write(fd, add_word, strlen(add_word));

#ifdef DEBUG
	printf("second offset : %ld\n", lseek(fd, 0, SEEK_CUR));
	printf("offset : %d\nwrite byte : %d\n", offset, wt);
#endif

	close(fd);
	return 0;

}

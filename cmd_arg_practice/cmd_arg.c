#include <stdio.h>
#include <unistd.h>

extern char ** environ;

int main(int argc, char *argv[]){
	setenv("mydir", "/home/hw", 0);
	setenv("kdrenel_src = %s\n", getenv("KERNEL_SRC"));

	while(*environ){
		printf("%s\n", *environ++);
	}
	sleep(10);
	return 0;
}

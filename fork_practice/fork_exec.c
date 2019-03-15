#include <stdio.h>	// printf()
#include <stdlib.h>	// exit()
#include <sys/types.h>	// pid_t
#include <wait.h>	// wait()
#include <unistd.h>	// fork()
#include <spawn.h>	// posix_spawn()

void my_execv(const char * path, char * const argv[]){
		int ret;
		pid_t pid;

		pid = fork();

		if(pid == -1){
				perror("fork");
				exit(EXIT_FAILURE);
		}

		if(pid == 0){
				ret = execv(path, argv);

				if(ret == -1){
						perror("execv");
						exit(EXIT_FAILURE);
				} }

		wait(NULL);	// instead of NULL, if you put nothing, it warns.
}

int my_posix_spawn(const char *path, char *const argv[]){
		pid_t pid;
		int ret = posix_spawn(&pid, path, NULL, NULL, argv, NULL);

		int status;

		waitpid(pid, &status, 0);

		return ret;

}

int main(void){
		char path[] = "/bin/ls";
		char *argv_ls[] = {"ls", "-al", "."};

//		my_execv(path, argv_ls);
		my_posix_spawn(path, argv_ls);

		return 0;

}

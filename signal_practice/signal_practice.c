#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <wait.h>

// it needs a sync
// after a sync signal, then practice on child proc.
// use a signal for sync
// after you confirm the structure of program, you can doc coding.

void pr_exit(int * status){

}

void usr1handler(int sig){
		sigset_t new, old;
		sigfillset(&new);
		sigemptyset(&old);
//		if(sigprocmask(SIG_BLOCK, &new, &old) < 0)
//				perror("USR1_NEW");
		printf("Hello\n");
//		if(sigprocmask(SIG_SETMASK, &old, &new) < 0)
//				perror("USR1_OLD");
		fflush(stdout);
}

void usr2handler(int sig){
		sigset_t new, old;
		sigfillset(&new);
		sigemptyset(&old);
//		if(sigprocmask(SIG_BLOCK, &new, &old) < 0)
//				perror("USR2_NEW");
		printf("World\n");
//		if(sigprocmask(SIG_SETMASK, &old, &new) < 0)
//				perror("USR2_OLD");
		fflush(stdout);
}

int main(void){
		pid_t pid;
  
		int status = 0;
		sigset_t newmask, oldmask;

//		struct sigaction newuser1, newuser2;
//		newuser1.sa_handler = usr1handler;
//		newuser2.sa_handler = usr2handler;

//		sigemptyset(&newuser1.sa_mask);
//		sigemptyset(&newuser2.sa_mask);

//		if(sigaction(SIGUSR1, &newuser1, NULL) == -1){
//				perror("USR1");
//		}
//		if(sigaction(SIGUSR2, &newuser2, NULL) == -1){
//				perror("USR2");
//		}
		

		pid = fork();

		switch(pid){
		case -1:
				perror("fork");
				break;
		case 0:
		//		printf("my pid : %d\n", getpid());

				signal(SIGUSR1, usr1handler);
				signal(SIGUSR2, usr2handler);

				sigemptyset(&newmask);
				sigemptyset(&oldmask);

				sigaddset(&newmask, SIGUSR1);
				sigaddset(&newmask, SIGUSR2);

				if(sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
						perror("SIG_BLOCK error");

				sleep(5);


//				for(int i=0; i < 5;i++){
//						pause();
//						printf("child first i : %d\n", i);
//						fflush(stdout);
//				}

				if(sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
						perror("SIG_SETMASK error");

				fflush(stdout);

				for(int i=0; i < 5;i++){
						pause();
				//		printf("child first i : %d\n", i);
						fflush(stdout);
//						while(getchar() != '\n');
				}

				printf("gg");
				exit(0);
		
				break;
		default:
		//		printf("child pid : %d\n", pid);
				sleep(1);
				for(int i=0; i<9; i++){
						if( i % 2 == 0){
								kill(pid, SIGUSR1);
//								printf("i 0\n");
						}
						else{
								kill(pid, SIGUSR2);
//								printf("i 1\n");
						}
						sleep(1);

				}
				kill(pid, SIGQUIT);
				if(wait(&status) == pid){
		//			pr_exit(&status);
					exit(0);
				}
		}
		printf("Not good exit\n");
}

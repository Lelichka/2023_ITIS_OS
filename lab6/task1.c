#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

void printInfo(char* process, int pid, int ppid) {
	struct timeval tv;
	gettimeofday(&tv, NULL);

	printf("%s PID: %d\t Parent PID: %d\n", process, pid, ppid);
	printf("Current time: %ld : %ld : %ld : %ld\n", (tv.tv_sec / 3600) % 24, (tv.tv_sec / 60) % 60, tv.tv_sec % 60, tv.tv_usec / 1000);
}

int main() {
	pid_t child1, child2;

	child1 = fork();

	if (child1 < 0){
		printf("Fork failed");
	}
	else if (child1 == 0){
		printInfo("Child 1",getpid(), getppid());
		exit(0);
	}
	else{
		child2 = fork();

		if (child2 < 0){
			printf("Fork failed");
		}
		else if (child2 == 0){
			printInfo("Child 2",getpid(), getppid());
			exit(1);
		}
		else{
			printInfo("Parent", getpid(), getppid());
			system("ps -x");
			waitpid(child1, NULL, 0);
			waitpid(child2, NULL, 0);
		}
	}

    	return 0;
}


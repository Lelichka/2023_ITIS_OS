#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    	char command[100];

	while(1){
		
		printf("Enter command (or 'exit'):");
		fgets(command, 100, stdin);
		
		char *token;
		int i = 0;
		char *arguments[50];

		command[strcspn(command,"\n")] = 0;

		if (strcmp(command,"exit") == 0){
			break;
		}

		token = strtok(command, " ");
		while(token != NULL){
			arguments[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		arguments[i] = NULL;

		pid_t child = fork();

		if (child < 0){
			printf("Fork failed");
		}
		else if (child == 0){
			execvp(arguments[0], arguments);
			exit(1);
		}
		else{
			int status;
			waitpid(child, &status, 0);
			if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                		printf("Exec failed\n");
            		}	
		}
	}

	return 0;
}

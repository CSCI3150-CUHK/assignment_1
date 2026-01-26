#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#define WRITE_END 1     // pipe write end
#define READ_END 0      // pipe read end

/*	shell_execute - Function to execute the command with specified command content and command arguments. 
*	@args	String array with command and its arguments. 
*	@argc	Total number of strings including the command, its arguments and the NULL in the end
*/
int shell_execute(char ** args, int argc){
	
	int child_pid, wait_return, status;

	/* Execute built-in commands */
	/* exit */
	if(strcmp(args[0], "exit") == 0 ){
		return -1; 
	}
	/* TODO: cd */
	if (strcmp(args[0], "cd") == 0) {
		if (args[1] == NULL) {
			fprintf(stderr, "cd: missing agrument\n");
			return 0;
		}
		if (chdir(args[1]) != 0) {
			perror("cd");
		}
		return 0;
	}


	/* Non-built-in commands. These commands should be executed in a child process so the parent process can continue to invoke other commands */	
	/* One command without pipe */
	if((child_pid = fork()) < 0){
		printf("fork() error \n");
	}
	else if(child_pid == 0 ){
		/* TODO: execute the command and check if the command is correctly executed */
		execvp(args[0], args);
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
	
	/* TODOs: one pipe and two pipes */
	int num = 1; //numer of commands
	for (int i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "|") == 0) {
            num++;
        }
    }

	int pipe_full[2];
	int previous_pipe = STDIN_FILENO;

	pid_t *child_pid = (pid_t *)malloc(num * sizeof(pid_t));
	if (child_pid == NULL) {
		return 1;
	}

	int current_cmd_start = 0;
	for (int j = 0; j < num; j++) {
		int current_cmd_end = current_cmd_start;
		while (args[current_cmd_end] != NULL && strcmp(args[current_cmd_end], "|") != 0) {
			current_cmd_end++;
		}

		char *current_cmd_args
		int count = 0; // counting the num of current commands
		//check for empty commands
		if (current_cmd_args[0] == NULL) {
			return 1;
		}

		for (int k = current_cmd_start; k < current_cmd_end; k++) {
			current_cmd_args[count++] = args[k];
		}
		current_cmd_args[count++] = args[k];
		
		if (i < num -1) {
			if (pipe(pipe_full) == -1) {
				perror("pipe")
			}
		}

		pit_t pid = fork();
		if (pid < 0) {
			perror("fork");
		} else if (pid == 0) {
			if (previous_pipe != STDIN_FILEN) {
				if (dup2(previous_pipe, STDIN_FILEN) == -1) {
					perror("dup2 stdin");
					exit(EXIT_FAILURE);
				}
			}
			 if (i < num_commands - 1) {
                if (dup2(pipe_fds[WRITE_END], STDOUT_FILENO) == -1) {
                    perror("dup2 stdout");
                    exit(EXIT_FAILURE);
                }
                close(pipe_fds[READ_END]);  
                close(pipe_fds[WRITE_END]); 
            }
			execvp(current_cmd_args[0], current_cmd_args);
            perror(current_cmd_args[0]);
            exit(EXIT_FAILURE); 
		} else {
			child_pids[i] = pid;
			if (i < num_commands - 1) {
                close(pipe_fds[WRITE_END]);
            }
			if (prev_pipe_read_fd != STDIN_FILENO) {
                close(prev_pipe_read_fd);
            }
			if (i < num_commands - 1) {
                prev_pipe_read_fd = pipe_fds[READ_END];
            }
		}
		cmd_start_idx = cmd_end_idx + 1;

	}
	
	/* wait for child process to terminate */
	while((wait_return = wait(&status)) > 0);
			
	return 0;

}

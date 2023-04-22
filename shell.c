#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char input[1024]; // buffer to hold user input
    char *args[64]; // array to hold parsed command and arguments
    int status;

    while (1) {
        printf("zed-shell$ "); // print shell prompt to console
        fgets(input, sizeof(input), stdin); // read user input from console and store in buffer

        int i = 0;
        args[i] = strtok(input, " \n"); // use strtok to parse first argument from input

        while (args[i] != NULL) { // loop until all arguments have been parsed
            i++;
            args[i] = strtok(NULL, " \n"); // use strtok to parse next argument from input
        }
        args[i] = NULL; // set last argument to NULL to terminate argument list

        if (strcmp(args[0], "exit") == 0) { // if user entered "exit" command, exit the shell program
            exit(0);
        }

        pid_t pid = fork(); // create a new process using fork()

        if (pid == 0) { // if we're in the child process
            execvp(args[0], args); // use execvp to execute the command with the specified arguments
            printf("Invalid command\n"); // if execvp returns, the command was not valid, so print an error message
            exit(0); // exit the child process
        } else { // if we're in the parent process
            wait(&status); // wait for the child process to finish executing
        }
    }
    return 0;
}
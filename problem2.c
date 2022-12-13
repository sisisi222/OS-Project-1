/*
Name: Huong Duong
Operating Systems - Assignment 1 - Problem 2
In this problem, we have to do the following:
- Based on previous problem, use fork() to create processes and exec() (or one of the many variants) to assign the newly created processes what to do
- Mimic the behavior of a shell command
- Expects an input of the form: cmd1 | cmd2
- Creates two processes
- Makes the first process run cmd1
- Makes the second process run cm2
- Make sure that the output of the first process becomes the input of the second process (using the dunction pipe())
- Waits for the two processes to finish before it ends by printing ++++ on a new line
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    
    char* cmd[argc]; //create a list to store two different commands from input
    
    //Store the input to the cmd array and skip the executable command and "|"
    int cmdCount = 0; //index for cmd array
    int i; //for loop
    for (i = 0; i < argc; i++) {
        if (i%2 == 0) {
            continue;
        }
        else {
            cmd[cmdCount] = argv[i];
            cmdCount++; 
        }
    }

    int fd[2]; //pipe - store the two ends

    //Check if pipe fails
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe fails!");
        return 1;
    }

    //create the two children processses
    //first child
    int firstPid = fork();
    if (firstPid < 0) {
        fprintf(stderr, "Fork fails!");
        exit(1);
    }

    else if (firstPid == 0) {
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp(cmd[0], cmd[0], NULL);
    }

    //second child 
    int secondPid = fork();
    if (secondPid < 0) {
        fprintf(stderr, "Fork fails!");
        exit(1);
    }

    else if (secondPid == 0) {
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp(cmd[1], cmd[1], NULL);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(firstPid, NULL, 0);
    waitpid(secondPid, NULL, 0);
    printf("++++\n");
    return 0;
}

/*
Name: Huong Duong
Operating System - Assignment 1 - Problem 1
In this problem, we have to do the following:
    - Takes an input from the command line. Refer the input as cmd if only one word
    Refer the input as cmd and params if more than one word.
    If the input has multiple separators, cmd is the sequence of characters before the first separator, 
    and params is the rest of the input. Eg: ls -a -l then cmd is 'ls' and params is '-a -l'
    - Create a new process - using fork()
    - Makes the new process execute cmd with params as parameters, if given
    - Waits for the new process to finish executing, and then prints ++++ on a new line

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(int argc, char *argv[]) {
    /*refer the input as cmd if only one word
    refer the sequence of characters before the firest separator of the input if more than one word */
    char* cmd = argv[1];

    //Create a list to store the cmd and params
    char* params[argc]; 

    //Initializ the list to NULL
    int i; //for loop
    for(i = 0; i < argc; i++) {
        params[i] = NULL;
    }

    //Add the parameters to the list
    for(i = 0; i < argc - 1; i++) {
        params[i] = argv[i+1];
    }

    //create a new process - using fork()
    int process = fork();

    if (process < 0) {
        fprintf(stderr, "ERROR! FORK FAILED!\n");
        exit(1);
    }

    //Make the new process execute cmd with params as parameters in this child process
    else if (process == 0) {
        execvp(cmd, params);
    }

    //Waits for the new process to finish executing, then print ++++ on a new line in parent process
    else {
        wait(NULL);
        printf("++++\n");
    }

    return 0;

}
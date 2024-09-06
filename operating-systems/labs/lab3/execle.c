/*
* Title: Operating Systems Lab 3
* Author: Noah Grant
* Date: November 10, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    char* env[] = {"HOME=/usr/home", "LOGNAME=home", NULL};

    execle("L3exe", "hello", "world", "execle", NULL, env);

    printf("This shouldn't print since a new process started...\n");

    return 0;
}

/*
1. Explain the specialty of the given exec*() function (what are the pros?)
execle() allows the user to start a new process with a given filename and arguments.
The first argument must a pointer to a path name that identifies the new process
image file for the new process image.The next arguments up to a NULL character will be passed in to
the new process. After that, the next set of inputs will be used to set up the
environment. Another NULL character is placed at the end. Since the argument 
parameters can be passed in independently instead of needing to be in an array,
multiple random variables can be passed in without needing to be in an array.

2. Given an example of when you’d not choose to use this given version of exec*() function
You would not use this exec*() function unless you want the new process to be executed in a 
different environment than the parent/initial process. If you are ok with the environment being
the same, than there is no point to use this function.
*/

/*
* Title: Operating Systems Lab 3
* Author: Noah Grant
* Date: November 10, 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    execlp("./L3exe", "hello", "world", "execlp", NULL);

    printf("This shouldn't print since a new process started...\n");

    return 0;
}

/*
1. Explain the specialty of the given exec*() function (what are the pros?)
execlp() allows the user to start a new process with a given filename and arguments.
The first argument must be the filename associated with the file being executed.
The remaining arguments will be passed in to the new process. The last argument must be a NULL character.
Since the argument parameters can be passed in independently instead of needing to be in an array,
multiple random variables can be passed in without needing to be in an array.

2. Given an example of when you’d not choose to use this given version of exec*() function
One reason to not use this function would be for security. The execlp() function has to
look up the file on the PATH which can be convinient but insecure. It is possible to inject
malicious code into the PATH lookup.
*/

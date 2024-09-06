#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // POSIX standard unix library
#include <sys/wait.h> // for wait()

int main() {
    int a = 3;

    // Socket information (including initialized contents) will be copied
    // File handle will be copied
    // Everything except PID line will be copied

    // Anything above this line is coppied and cloned into the subprocess
    int pid = fork(); // Creating a doppledanger
    // Below this line we have two processes
    // 1. Parent process
    // PID recieved a non-zero PID number matching the child process
    // Parent now hold control over the lifecycle of the child process
    // - Parent process holds origional copies of the variables before fork()
    if (pid > 0) {
        int status = -1; // Child process return code

        // All code here will be executed by only the parent process
        printf("[PARENT] I'm the parent process - child PID: %d\n", pid);

        for (int i = 50; i > 0; i--, a++) {
            printf("[PARENT] i=%d, a=%d\n", i, a);
        }
        
        // Brute force method for process synchronization - WAIT
        //usleep(500000);

        // Better synchronization
        wait(&status);
        printf("[PARENT] Child process finished with status: %d\n", WEXITSTATUS(status));
        printf("[PARENT] done\n");
        
        exit(EXIT_SUCCESS);
    }

    // 2. Child process
    // PID recieves 0, indicating you are the child process
    // Child process holds no knowledge of teh parent process (in the beginning)
    // - Child process holds a new copy of the variables before fork()
    // - Resides in new memory space, new PCB
    else if (pid == 0) {
        // All code here will only be executed by the child proces=
        
        // Swap the child process with a new process image
        // Pass NULL after all other parameters you want to pass to the child process
        //execlp("./fork2", "Program Name: fork2", NULL);
        int res = execlp("ls", "Prog Name: ls", NULL);

        // If execlp failed to execute, the process image will not be repalced
        // therefore, we can reach this protion of the code
        if (res < 0) {
            perror("[CHILD] Process image failed to be repalced, shutting down...\n");
            exit(-10);
        }

        exit(EXIT_SUCCESS);
    }

    else {
        // pid < 0, fork call failed (probably due to low memory)
        // shutdown of wait a bit more
        perror("Failed to fork a child process, shutting down...\n");
        
        exit(EXIT_FAILURE);
    }

    // Ubuntu doesn't close parent process until child process is done but this
    // is not the case for all distros.

    // Child process launches at different times based on when it can get the 
    // required resources

    return 0;
}

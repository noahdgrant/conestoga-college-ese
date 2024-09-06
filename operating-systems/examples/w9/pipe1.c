// Pipe example

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define PIPE_LEN 26

int main() {
    int myPCpipe[2];
    int myCPpipe[2];
    char buf[30];
    int pid;

    // Create pipe
    // Need two pipes for bidirectional communication
    // myPCpipe[0] = read
    // myPCpipe[1] = write
    if (pipe(myPCpipe) == -1) {
        printf("PC Pipe creation failed...\n");
        return -1;
    }
    
    if (pipe(myCPpipe) == -1) {
        printf("CP Pipe creation failed...\n");
        return -1;
    }

    pid = fork();
    if (pid == 0) {
        // child process
        // child has duplicate myPCpipe[2] with the same file descriptors
        close(myCPpipe[0]); // Child only write into CPpipe, so read is not needed
        close(myPCpipe[1]); // Child only read from PCpipe, so write is not needed

        for (int i = 0; i < 3; i++) {
            printf("[CHILD] Writing into the pipe (%d), i = %d\n", myCPpipe[1], i); 
            write(myCPpipe[1], "Test message from child!", 25); // write(PIPE DES, STRING, LENGTH)
            
            printf("[CHILD] Reading from pipe (%d)\n", myPCpipe[0]);
            read(myPCpipe[0], buf, 26); // read(PIPE DES, BUFFER, LENGTH)
            printf("[CHILD] Contents read from %d buffer: %s\n",i, buf);
        }

        return 0;
    }
    else {
        // parent process
        close(myCPpipe[1]); // Parent only need from CPpipe, so write is not needed
        close(myPCpipe[0]); // Parent only write into PCpipe, so read is not needed
        
        for (int i = 0; i < 3; i++) {
            printf("[PARENT] Writing into the pipe (%d), i = %d\n", myPCpipe[1], i); 
            write(myPCpipe[1], "Test message!", 26); // write(PIPE DES, STRING, LENGTH)
            
            printf("[PARENT] Reading from pipe (%d)\n", myCPpipe[0]);
            read(myCPpipe[0], buf, 25); // read(PIPE DES, BUFFER, LENGTH)
            printf("[PARENT] Contents read from %d buffer: %s\n",i, buf);
        }

        sleep(3); // Waiting for child to finish. Not best way to do this. Go loop at fork() examples
        return 0;
    }

    return 0;
}

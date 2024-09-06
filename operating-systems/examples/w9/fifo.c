#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main() {
    // Create a FIFO (named pipe) from within the program
    // The FIFO will exist even after the program shuts down
    int result = mkfifo("myFIFO", 0777);
    if (result != 0) {
        printf("FIFO creation failed...probably already created\n");
    }

    char buf[100];

    if (fork() == 0) {
        // Child process
        int myFIFO = open("myFIFO", O_RDONLY);

        read(myFIFO, buf, 100);
        printf("[CHILD] I heard: %s\n", buf);
        
        exit(0);
    }
    else {
        // Parent process
        // Only the write portion can/should be non-blocking
        int myFIFO = open("myFIFO", O_WRONLY | O_NONBLOCK);

        printf("[PARENT] What is your input?\n");
        fflush(stdin);
        fgets(buf, 100, stdin);

        printf("[PARENT] I'm passing the message into the FIFO...\n");
        write(myFIFO, buf, 100);

        exit(0);
    }
    

    return 1;
}

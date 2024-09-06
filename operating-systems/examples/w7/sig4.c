#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigquit_handler(int signum) {
    printf("[SIGQUIT_Handler]: Caught signal number %d\n", signum);
    printf("[SIGQUIT_Handler]: Exiting program...\n");

    exit(0);
}

int main() {

    int pid = fork();
    if (pid == 0) {
        // Child proces
        signal(SIGQUIT, sigquit_handler);

        while (1) {
            printf("[CHILD] Sleeping...\n");
            sleep(1);
        }
    }
    else {
        // Parent process
        printf("[PARENT] Wait for 5 seconds before telling the child process to quit\n");
        sleep(5);

        printf("[PARENT] Killing child process...\n");
        kill(pid, SIGQUIT);
    }

    return 0;
}

// kill() send signal from one proc to another
// raise() send signal from one proc to itself

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int);

int main() {

    // Setup signal handler
    // Use SIG_IGN to ignore a signal: signal(SIGINT, SIG_IGN);
    signal(SIGINT, sigint_handler);
    
    // Random lengthy process
    for (int i = 0; i < 5; i++) {
        printf("Sleeping...%d\n", i);
        sleep(2);
    }

    printf("DONE.\n");

    return 0;
}

// CTRL+C send SIGINT to the foreground process
void sigint_handler(int signum) {
    printf("[SIGINT_Handler]: Caught signal number %d\n", signum);
    printf("[SIGINT_Handler]: Exiting program...\n");

    exit(0);
}

// SIGINT wakes up CPU from sleep and doesn't return to that sleep after

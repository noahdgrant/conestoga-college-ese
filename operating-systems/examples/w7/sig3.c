#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Setting up user signal

void custom_handler(int signum) {
    printf("\n[SIGUSR1] Custom handler is called\n");

    raise(SIGINT); // Cascading signals
}

void sigint_handler(int signum) {
    printf("[SIGINT_Handler]: Caught signal number %d\n", signum);
    printf("[SIGINT_Handler]: Exiting program...\n");

    exit(0);
}

int main() {
    signal(SIGUSR1, custom_handler);
    signal(SIGINT, sigint_handler);

    printf("Slepping for 3 seconds... and then buzz myself\n");

    sleep(3);

    raise(SIGUSR1); // Throw a signal back at the process itself

    printf("Done, exiting...\n");

    return 0;
}

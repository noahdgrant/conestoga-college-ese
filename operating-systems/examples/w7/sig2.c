#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Setting up Alarm Signal - SIGALRM

void alarm_handler(int signum) {
    printf("\nOperation timed out...\n");
    exit(0);
}

int main() {
    char buf[128];

    // If input is not received within 10 seonds, I need an alarm to go off
    signal(SIGALRM, alarm_handler);

    alarm(10); // Kernel will throw backat a SIGALRM after 10 seconds if the alarm is not disabled before then

    printf("Give me some input within 10 seconds: ");
    fflush(stdout);
    fflush(stdin);

    fgets(buf, sizeof(buf), stdin);

    alarm(0); // Disable the alarm by setting it to 0

    printf("\nInput received: %s\n", buf);

    return 0;
}

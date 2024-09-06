// Pipe size example

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int count;

void alarm_handler() {
    printf("Write blocked after %d bytes...\n", count);
    exit(0);
}

int main() {
    int mypipe[2];
    char c = '@';
    count = 0;

    pipe(mypipe);
    signal(SIGALRM, alarm_handler);

    while (1) {
        alarm(3); // Setup watchdog timer for blocking call
        write(mypipe[1], &c, 1); // Will block if pipe is full
        alarm(0);
        count++;

        if (count % 1024 == 0) {
            printf("%d bytes in pipe\n", count);
        }
    }

    return 0;
}

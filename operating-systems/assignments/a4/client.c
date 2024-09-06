// Title: Client for Operating Systems assignment 4
// Author: Noah Grant
// Date: November 29, 2023

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LETTERS 1024
#define NUM_LETTERS 20
#define TERMINAL_PADDING 10

void SIGINT_handler(int sig_num);

int done = 0;

// Structure for shared memory
typedef struct letter_buffer {
    int pos;
    char letters[MAX_LETTERS];
    pid_t pid;
    int sem_id;
} random_letter_generator;

random_letter_generator *shm_ptr;

int main() {
    // Sharmed memory variables
    int shm_id;
    key_t shm_key;
    
    // Semaphore variables
    struct sembuf sem_acquire = {0, -1, SEM_UNDO};
    struct sembuf sem_release = {0, 1, SEM_UNDO};

    // Application variables
    char buffer[MAX_LETTERS];
    int histogram[NUM_LETTERS];
    double histogram_scale = 1;
    int highest_letter_count = 0;
    pid_t pid;
    struct winsize terminal_size;

    // Setup signal handler
    signal(SIGINT, SIGINT_handler);

    // Create key for shared memory
    if ((shm_key = ftok(".", 'A')) == -1) {
        printf("[Client] ERROR: Cannot allocate shared memory key\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[Client] Shared memory key allocated\n");
    }

    // If shared memory exists, use it. Otherwise, try to launch the server
    if ((shm_id = shmget(shm_key, sizeof(random_letter_generator), 0)) == -1) {
        printf("[Client] Shared memory doesn't exist...trying to launch server\n");
        
        // Launch server in child process
        if ((pid = fork()) < 0) {
            printf("[Client] ERROR: Failed to spawn child process\n");
            exit(EXIT_FAILURE);
        }
        if (pid == 0) {
            // Child process
            char* args[] = {"./server", NULL};
            execvp(args[0], args);
            printf("[Client] ERROR: Failed to launch server\n");
            exit(EXIT_FAILURE);
        }

        // Attempt to connect to server again
        sleep(1);
        if ((shm_id = shmget(shm_key, sizeof(random_letter_generator), 0)) == -1) {
            printf("[Client] ERROR: The server/client suite is no longer working\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("[Client] Shared memory ID: %d\n", shm_id);

    // Attach to shared memory
    if ((shm_ptr = (random_letter_generator*)shmat(shm_id, NULL, 0)) == NULL) {
        printf("[Client] ERROR: Cannot attach to shared memory\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[Client] Attached to shared memory\n");
    }

    // Generate histogram of letters in the shared memory
    while (!done) {
        system("clear");
        ioctl(0, TIOCGWINSZ, &terminal_size);

        // Reset histogram
        for (int i = 0; i < sizeof(histogram); i++) {
            histogram[i] = 0;
        }

        histogram_scale = 1;
        highest_letter_count = 0;

        // Decrement semaphore
        if (semop(shm_ptr->sem_id, &sem_acquire, 1) == -1) {
            printf("[Client] ERROR: Can't start critical region\n");
            exit(EXIT_FAILURE);
        }

        /* CRITICAL REGION - START */
        
        strncpy(buffer, shm_ptr->letters, sizeof(buffer));
        
        /* CRITICAL REGION - END */

        // Increment semaphore
        if(semop(shm_ptr->sem_id, &sem_release, 1) == -1) {
            printf("[Client] ERROR: Can't exit critical region\n");
            semctl(shm_ptr->sem_id, 0, IPC_RMID);
            exit(EXIT_FAILURE);
        }

        // Find the number of occurances of each letter currently in the shared memory
        for (int i = 0; i < sizeof(buffer); i++) {
            histogram[buffer[i] - 'A']++;
        }

        // Calculate histogram scale
        for (int i = 0; i < NUM_LETTERS; i++) {
            if (histogram[i] > highest_letter_count) {
                highest_letter_count = histogram[i];
            }
        }

        histogram_scale = ceil(highest_letter_count / ((double)terminal_size.ws_col - TERMINAL_PADDING)); 
        if (histogram_scale < 1) {
            histogram_scale = 1;
        }

        // Print out histogram
        printf("========== Histogram of current letters in shared memory ==========\n");
        printf("Scale: * = %d letter(s)\n\n", (int)histogram_scale);
        for (int i = 0; i < NUM_LETTERS; i++) {
            printf("%c |", ('A' + i));
            for (int j = 0; j < (histogram[i] / histogram_scale); j++) {
                printf("*");
            }
            printf("  %d\n", histogram[i]);
        }

        sleep(2);
    }

    // Detach from shared memory
    shmdt(shm_ptr);
    printf("[Client] Detached from shared memory\n");

    printf("[Client] Quiting...\n");
    return 0;
}

void SIGINT_handler(int sig_num){
    printf("[Client] Terminate client command received...shutting down\n");
    done = 1;

    // Send kill command to the server
    kill(shm_ptr->pid, SIGINT);
}

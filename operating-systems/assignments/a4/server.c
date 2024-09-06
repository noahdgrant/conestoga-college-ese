// Title: Server for Operating Systems assignment 4
// Author: Noah Grant
// Date: November 29, 2023

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_LETTERS 1024
#define NUM_LETTERS 20
#define LETTERS_PER_QUARTER_SECOND 32

void SIGINT_handler(int sig_num);

int done = 0;

// Structure for shared memory
typedef struct letter_buffer {
    int pos;
    char letters[MAX_LETTERS];
    pid_t pid;
    int sem_id;
} random_letter_generator;

int main() {
    // Shared memory variables
    int shm_id;
    key_t shm_key;
    random_letter_generator* shm_ptr;

    // Semaphore variables
    struct sembuf sem_acquire = {0, -1, SEM_UNDO};
    struct sembuf sem_release = {0, 1, SEM_UNDO};
    unsigned short sem_init[1] = {1};
    int sem_id;

    // Setup signal handler
    signal(SIGINT, SIGINT_handler);

    // Create key for shared memory
    if ((shm_key = ftok(".", 'A')) == -1) {
        printf("[Server] ERROR: Cannot allocate shared memory key\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[Server] Shared memory key allocated\n");
    }

    // Create shared memory if it doesn't exist
    if ((shm_id = shmget(shm_key, sizeof(random_letter_generator), 0)) == -1) {
        printf("[Server] Shared memory doesn't exist...creating!\n");

        if ((shm_id = shmget(shm_key, sizeof(random_letter_generator), IPC_CREAT | 0660)) == -1) {
            printf("[Server] ERROR: Cannot create shared memory\n");
            exit(EXIT_FAILURE);
        } else {
            printf("[Server] Shared memory created\n");
        }
    }
    printf("[Server] Shared memory ID: %d\n", shm_id);

    // Attach to shared memory
    if ((shm_ptr = (random_letter_generator*)shmat(shm_id, NULL, 0)) == NULL) {
        printf("[Server] ERROR: Cannot attach to shared memory\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[Server] Attached to shared memory\n");
    }

    // Setup semaphore
    if ((sem_id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666)) == -1) {
        printf("[Server] ERROR: Couldn't get semaphore\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[Server] Semaphore ID: %d\n", sem_id);
    }

    if (semctl(sem_id, 0, SETALL, sem_init) == -1) {
        printf("[Server] ERROR: Couldn't initialize semaphore\n");
        exit(EXIT_FAILURE);
    } else {
        printf("[Server] Semaphore initialized\n");
    }

    // Initialize data in shared memory
    for (int i = 0; i < MAX_LETTERS; i++) {
        shm_ptr->letters[i] = '\0';
    }
    shm_ptr->pos = 0;
    shm_ptr->pid = getpid();
    shm_ptr->sem_id = sem_id;

    // Generate random lettes until told to stop
    while (!done) {
        char random_letter;

        // Decrement semaphore
        if (semop(shm_ptr->sem_id, &sem_acquire, 1) == -1) {
            printf("[Server] ERROR: Can't start critical region\n");
            exit(EXIT_FAILURE);
        }

        /* CRITICAL REGION - START */

        // Generate random letters between A-T
        for (int i = 0; i < LETTERS_PER_QUARTER_SECOND; i++) {
            random_letter = 'A' + (rand() % NUM_LETTERS);
            shm_ptr->letters[shm_ptr->pos] = random_letter;
            shm_ptr->pos = (shm_ptr->pos + 1) % MAX_LETTERS;
        }
        
        /* CRITICAL REGION - END */

        // Increment semaphore
        if(semop(shm_ptr->sem_id, &sem_release, 1) == -1) {
            printf("[Server] ERROR: Can't exit critical region\n");
            semctl(shm_ptr->sem_id, 0, IPC_RMID);
            exit(EXIT_FAILURE);
        }

        usleep(250000);
    }

    // Release the semaphore
    semctl(shm_ptr->sem_id, 0, IPC_RMID, 0);
    printf("[Server] Semaphore released\n");

    // Detach from shared memory
    shmdt(shm_ptr);
    printf("[Server] Detached from shared memory\n");

    // Delete the shared memory
    shmctl(shm_id, IPC_RMID, 0);
    printf("[Server] Shared memory deleted\n");

    printf("[Server] Quiting...\n");
    return 0;
}

void SIGINT_handler(int sig_num){
    printf("[Server] Terminate server command received...shutting down\n");
    done = 1;
}

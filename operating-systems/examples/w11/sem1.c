// Semaphore example

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>

char* data[10] = {"apple", "beef", "car", "dog", "elephant", "red", "houses", "apartment", "juice", "water"};

int main() {
    // Setup semaphore (P/V operations)
    struct sembuf P = {0 , -1, SEM_UNDO}; // P() - wait(), decrement sem #0
    struct sembuf V = {0 , 1, SEM_UNDO};  // signal(), infrement sem #0

    int semID; // Track semaphore ID
    char semID_str[20]; // Need to pass the sem ID to my child processs. Alternative way of ftok() sharing among processes

    FILE *fp;
    int status;

    unsigned short init_values[1] = {1}; // Setting up a binary semaphore / MUTEX

    printf("[PARENT] Obtaining semaphore...\n");

    semID = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT); // IPC_PRIVATE: I want a token from OS, but I don't want it publically accessible
    if (semID == -1) {
        printf("[PARENT] semaphore acquisition failed...\n");
        exit(EXIT_FAILURE);
    }

    printf("[PARENT] Initializing semaphores...\n");
    status = semctl(semID, 0, SETALL, init_values);
    if (status == -1) {
        printf("[PARENT] Failed to initialize semaphores...\n");
        exit(EXIT_FAILURE);
    }

    // Fork new process as the observer/consumer
    printf("[PARENT] Forking child process to share info through shared file...\n");

    switch(fork()) {
        case 0:
            // Child process
            // Pass the semID as a string over to the child process as the input arg
            sprintf(semID_str, "%d", semID);
            execl("./sem2", "sem2", semID_str, NULL);

            // If execl() fails, we will reach this portion of the code
            printf("[CHILD] Failed to lauch sem2...\n");
            semctl(semID, 0, IPC_RMID);
            exit(EXIT_FAILURE);
            break;

        case -1:
            // Failed
            printf("[PARENT] Failed to fork child process...\n");
            semctl(semID, 0, IPC_RMID);
            exit(EXIT_FAILURE);
            break;
    }

    // Setup shared file
    // Shared file needs access control - use binary semaphore to protect it
    for (int i = 0; i < 10; i++) {
        // P()
        status = semop(semID, &P, 1);
        if (status == -1) {
            printf("[PARENT] Semaphore operation failed, can't start CS...\n");
            // Maybe need a clean up operation here
            exit(EXIT_FAILURE);
        }
        
        printf("[PARENT] In CS, writing to file...\n");

        // Write into the file when in CS
        fp = fopen("sharedFile.txt", "w");

        fprintf(fp, "%s", data[i]);

        fclose(fp);

        sleep(2); // Represents bust critical section (CS) work

        printf("[PARENT] Done in CS...\n");

        // V()
        if(semop(semID, &V, 1) == -1) {
            printf("[PARENT] Semaphore operation failed, can't end CS...\n");
            // Maybe need a clean up operation here
            exit(EXIT_FAILURE);
        }
    }

    // Parent process will be the producer
    printf("[PARENT] Shutting down...\n");
    sleep(5); // Allow child to finish file access
    remove("sharedFile.txt");
    semctl(semID, 0, IPC_RMID);
    sleep(2); // Allow child process to shut down by recognizing no semaphores are there anymore

    return 0;
}

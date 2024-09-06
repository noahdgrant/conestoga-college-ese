// Semaphore 2 (part of sem1 example)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>

// Child process - the consumer

// Coming from exectl() call in the parent process sem1
int main(int argc, char* argv[]) {
    // Setup semaphore (P/V operations)
    struct sembuf P = {0 , -1, SEM_UNDO}; // P() - wait(), decrement sem #0
    struct sembuf V = {0 , 1, SEM_UNDO};  // signal(), infrement sem #0
    
    int semID; // Track semaphore ID

    FILE *fp;
    char str_data[256];

    printf("[CHILD] Child process started...\n");

    // Obtain the semID for IPC
    if (argc != 2) {
        printf("[CHILD] Incorrect number of arguments to latch\n");
        exit(EXIT_FAILURE);
    }

    semID = atoi(argv[1]);

    printf("[CHILD] Semaphore ID obtained: %d\n", semID);

    printf("[CHILD] Start the infinite program loop...\n");
    // Infinite program loop until the semaphore is deleted by the parent
    while (1) {
        // P()
        if(semop(semID, &P, 1) == -1) {
            printf("[CHILD] Semaphore operation failed, can't start CS...\n");
            break;
        }

        // Critial section
        fp = fopen("sharedFile.txt", "r");
        fgets(str_data, sizeof(str_data), fp);
        printf("[CHILD] Received from the parent: %s\n", str_data);
        fclose(fp);

        // V()
        if(semop(semID, &V, 1) == -1) {
            printf("[CHILD] Semaphore operation failed, can't end CS...\n");
            break;
        }
    }

    printf("[CHILD] Semaphore gone. I'm done!\n");

    return 0;
}

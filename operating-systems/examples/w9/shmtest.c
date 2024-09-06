#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 1024

// Other examples are posted on eConestoga that will be helpful for Assignment 3

int main(int argc, char* argv[]) {
    key_t key; // Unique key used to associate a peice of shared memory
    int shmID; // ID to the associated shared memory
    char* data;
    int res;

    if (argc > 2) {
        printf("Wrong usage...\n");
        return -10;
    }
    // if argc = 1 (only the program launch command)
    // Read from shared mem, and delete the shared mem
    // if argc = 2 (program cmd + string)
    // Create  if possible the shared mem, and write the string into the shared mem

    // Create a unique token in preparation for the shared memory creation
    key = ftok(".", 'T');
    if (key == -1) {
        printf("Ftok failed...\n");
        return -1;
    }

    if (argc == 2) {
        // Allocate shared memory
        shmID = shmget(key, SHM_SIZE, 0777 | IPC_CREAT); // Step 1 - malloc() 
    }
    else {
        shmID = shmget(key, SHM_SIZE, 0777); 
    }
        
    
    if (shmID == -1) {
        printf("shmget() failed...\n");
        return -2;
    }
    
    // Attach to shared memory
    data = (char*)shmat(shmID, (void*)0, 0); // step 2 - malloc()
    if (data == (char*)-1) {
        printf("shmat() failed...\n");
        return -3;
    }

    if (argc == 2) {
        // Write mode
        strncpy(data, argv[1], SHM_SIZE);
    }
    else {
        // Read mode
        printf("Shared memory contains: %s\n", data);
    }

    // Detatch from shared memory
    res = shmdt(data); // step 1 - free()
    if (res == -1) {
        printf("shmdt() failed...\n");
        return -4;
    }

    if (argc == 1) {
        // Deallocate the shared memory
        res = shmctl(shmID, IPC_RMID, NULL);
        if (res == -1) {
            printf("shmctl() failed...\n");
            return -5;
        }
    }

    return 0;
}

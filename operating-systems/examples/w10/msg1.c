#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>

// Usage:
// ./msg1 [-r / -w] [message contents]

// Define message structure
struct msgStr {
    long msgType; // mandatory for message sorting in the Linux msg queue

    // Custum structure that can be changed to anything
    struct {
        long pid;       // Process ID fo the sender
        char str[100];  // Message to be sent from the producer process
    } data;
} msgRecord;

int main(int argc, char* argv[]) {
    key_t myKey;
    int msgQID;
    int status;                 // Capture return status from msg API calls (error handling)
    struct msgStr msgRecord;    // My message to send / to receive

    // Get / create a public token
    myKey = ftok(argv[0], 'V'); // my choice of token to see whether it is taken... (V is randomly chosen)
    printf("Key value is %d\n", myKey);

    if (argc < 2) {
        printf("Usage: ./msg1 [-r / -w] [msg contents]\n");
        exit(EXIT_FAILURE);
    }

    // Check if in read or write mode
    if (strcmp(argv[1], "-r") == 0) {
        /* READ MODE */
        int thismType = 99; // Arbitrary number

        // Open msg queue if possible, then read
        msgQID = msgget(myKey, S_IRUSR); // S_IRUSR is user-mode read access
        if (msgQID < 0) {
            printf("Message queue doesn't exist\n");
            exit(EXIT_FAILURE);
        }

        status = msgrcv(msgQID,             // Which message queue to receive
                (void*)&msgRecord,          // Data to receive
                sizeof(msgRecord.data),     // Only receiving the data section
                thismType,                  // 0-any type
                IPC_NOWAIT);                // 0 for BLOCKING, IPC_NOWAIT for NON_BLOCKING
        if (status < 0) {
            printf("Bad receive on mType: %d...\n", thismType);
            exit(EXIT_FAILURE);
        }

        printf("Message received: PID = %ld, String = %s\n", msgRecord.data.pid, msgRecord.data.str);
    }
    else if (strcmp(argv[1], "-w") == 0) {
        /* WRITE MODE */
        // Open message queue or create it if it doesn't exist
        msgQID = msgget(myKey, S_IWUSR | S_IRUSR | IPC_CREAT);
        if (msgQID < 0) {
            printf("Message queue cannot be created\n");
            exit(EXIT_FAILURE);
        }

        msgRecord.msgType = 99;         // Arbitrary number for filtering
        msgRecord.data.pid = getpid();  // Get my process PID

        strcpy(msgRecord.data.str, argv[2]); // Copy the input string into the message (assume it is provided)

        // Send msg
        status = msgsnd(msgQID,             // Which message queue
                (void*)&msgRecord,          // Message to send
                sizeof(msgRecord.data),     // Just the data, because msgsnd() is going to process mType as an intrinsic sorting param
                0);                         // 0 for BLOCKING, IPC_NOWAIT for NON_BLOCKING
        if (status < 0) {
            printf("Bad send...No message will be available\n");
        }
        else {
            sleep(20); // I will remove the message queue after 20 seconds
        }

        // Delete the message queueu
        status = msgctl(msgQID, IPC_RMID, 0); // Almost identical to SHMCTL
        if (status < 0) {
            printf("Failed to remove MSG_Q...\n");
            exit(EXIT_FAILURE);
        }

        printf("Message queue closed...\n");
    }
    else {
        printf("Usage: ./msg1 [-r / -w] [msg contents]\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}

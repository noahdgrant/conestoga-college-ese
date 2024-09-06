// Multithreading example

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> // POSIX multithread library
#include <signal.h>

// thread function
// input type - must be a void pointer (so we can cast it to point to any structures)
// return type - must be a void pointer (so we can point to a return structure, and allow the invoker to cast it)
void* my_thread_function(void* p){
    // inside here, we've got the second mainline (thread 2)

    printf("[THREAD1] my TID is %ld\n", pthread_self());

    for (int i = 0; i < 80000; i++) {
        if (i % 8000 == 0) {
            printf("[THREAD1] Count: %d\n", i);
        }
    }

    pthread_exit(0); // or use return 0;
}

void* my_idle_thread(void* p){
    // do nothing except block
    while(1);
    
    pthread_exit(0);
}

int main() { // Mainline, thread 1

    // 1. Create new thread
    // 1.1 call on pthread_create()
    // 1.2 give reference to the tid variable in the mainline
    // 1.3 create a "thread function" and pass its function name (function pointer) to pthread_create()
    // 1.4 provide void pointer to an input parameter structure in our example we won't have any structures.
    
    pthread_t tid1; // int type, but specifically used for holding TID
    pthread_t tid2;
    void* status;

     if(pthread_create(&tid1, NULL, my_thread_function, (void*)0) != 0) {
        perror("thread creation failed, exiting...\n");
        exit(-15);
     }
     
     if(pthread_create(&tid2, NULL, my_idle_thread, (void*)0) != 0) {
        perror("thread creation failed, exiting...\n");
        exit(-15);
     }

     printf("[MAIN] thread created with TID: %ld\n", tid1);
     printf("[MAIN] thread created with TID: %ld\n", tid2);

    // 2. Do work in mainline
    for (int i = 0; i < 50000; i++) {
        if (i % 5000 == 0) {
            printf("[MAIN] Count: %d\n", i);
        }
    }

    // 3. Do work in the new thread

    // 4. Have mainline wait for thread to finish before exiting program
    // Allow user to enter something if the user wants to terminate teh heavy-lifting thread
    // Whenever the user enters the shutdown command, we will kill the greedy thread
    //printf("Press any key to shutdown the thread at any time!\n");
    //getchar(); // synchronous blocking IO call (mainline stuck here until char entered)

    pthread_join(tid1, &status);
    
    pthread_kill(tid2, SIGKILL);
    // Thread signal call - sending a signal to intervene the execution process of a thread
    // SIGKILL is a signal intructing the thread to stop whatever it is going and terminate itself


    // When pthread_join() is called, the mainline checks if the thread with TID has ended.
    // If not, the mainline is going to block on this statement until the thread finishes
    // If yes, mainline will continue
    // pthread_join(tid, &status);

    printf("\n[MAIN] system shutdown\n");

    return 0;
}

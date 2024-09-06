/*
* Operating Systems Lab 4
* Author: Noah Grant
* Date: November 29, 2023
*/

#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>

#define NUM_SUBJECTS 1
#define NUM_OBSERVERS 4
#define NUM_VALID_OUTPUTS 3

typedef struct tag_semaphore {
   int id;
   int init_val[1];
   struct sembuf acquire;
   struct sembuf release;
} semaphore;

semaphore semaphore_init(int init_val);
void semaphore_get(semaphore* sem);
void semaphore_wait(semaphore* sem);
void semaphore_signal(semaphore* sem);
void semaphore_delete(semaphore* sem);

void* subject(void* p);
void* observer(void* p);

semaphore sem_write_switch;
semaphore sem_no_writers;
semaphore sem_read_switch;
semaphore sem_no_readers;
semaphore sem_done;

int done;                           // Number of observer threads that are done 
int output;                         // Random integer
int readers = 0;                    // Number of readers in the critical section
int writers = 0;                    // Number of writers in critical section

int main() {
    // Thread variables
    pthread_t sub;
    pthread_t observerID[NUM_OBSERVERS];
    pthread_attr_t attr;
    long mod[NUM_OBSERVERS] = {3, 5, 7, 25};

    // Setup semaphores
    sem_write_switch = semaphore_init(NUM_SUBJECTS);
    sem_no_writers = semaphore_init(1);
    sem_read_switch = semaphore_init(NUM_OBSERVERS);
    sem_no_readers = semaphore_init(1);
    sem_done = semaphore_init(1);
    
    // Setup semaphores
    semaphore_get(&sem_write_switch);
    semaphore_get(&sem_no_writers);
    semaphore_get(&sem_read_switch);
    semaphore_get(&sem_no_readers);
    semaphore_get(&sem_done);

    // Initialize threads through thread attribute configuration
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    
    // Create threads
    if (pthread_create(&sub, &attr, subject, NULL) != 0) {
        perror("[Main] Subject thread creation failed, exiting...\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < NUM_OBSERVERS; i++) {
        if (pthread_create(&observerID[i], &attr, observer, (void*)mod[i]) != 0) {
            printf("[Main] Observer %u thread creation failed, exiting...\n", (int)observerID[i]);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to finish - non-blocking main thread
    while (1) {
        semaphore_wait(&sem_done);

        /* CRITICAL REGION - START */

        if (done < NUM_OBSERVERS) {
            // Threads still working

            // Uncomment the line below if you want to see the main thread waiting for observers to finish
            // I commented it out for now because it makes the output a lot cleaning
//            printf("[Main] %d / %d threads done...waiting for threads\n", done, NUM_OBSERVERS);
            
            /* CRITICAL REGION - END */

            semaphore_signal(&sem_done);
        }
        else {
            // All threads are done
            break;
        }
    }
    
    printf("[Main] %d / %d threads done...killing subject thread\n", done, NUM_OBSERVERS);
    pthread_kill(sub, SIGKILL);

    // Release the semaphores
    semaphore_delete(&sem_write_switch);
    semaphore_delete(&sem_no_writers);
    semaphore_delete(&sem_read_switch);
    semaphore_delete(&sem_no_readers);
    semaphore_delete(&sem_done);
    printf("[Main] Semaphores released\n");
    

    printf("[Main] Exiting...\n");

    return 0;
}

// Function to generate a random number on the Subject thread
void* subject(void* p) {
    int tmp = 0;  

    while (1) {
        // Generate random number
        tmp = rand() % 1000;
        if (tmp % 5 == 0) {
            semaphore_wait(&sem_write_switch);
            writers++;
            if (writers == 1) {
                semaphore_wait(&sem_no_readers);
            }
            semaphore_signal(&sem_write_switch);

            semaphore_wait(&sem_no_writers);

            /* CRITICAL REGION - START */

            output = tmp;
            
            /* CRITICAL REGION - END */

            semaphore_signal(&sem_no_writers);
            
            semaphore_wait(&sem_write_switch);
            writers--;
            if (writers == 0) {
                semaphore_signal(&sem_no_readers);
            }
            semaphore_signal(&sem_write_switch);
        }
    }
    
    pthread_exit(EXIT_SUCCESS);
}

// Function for Observer threads
void* observer(void* p) {
    long value = (long)p;
    int valid = 0;

    while (valid < NUM_VALID_OUTPUTS) {
        semaphore_wait(&sem_no_readers);

        semaphore_wait(&sem_read_switch);
        readers++;
        if (readers == 1) {
            semaphore_wait(&sem_no_writers);
        }
        semaphore_signal(&sem_read_switch);

        semaphore_signal(&sem_no_readers);

        /* CRITICAL REGION - START */

        if (output % value == 0) {
            printf("[Observer %ld] Output = %d\n", value, output);
            valid++;
        }

        /* CRITICAL REGION - END */
        
        semaphore_wait(&sem_read_switch);
        readers--;
        if (readers == 0) {
            semaphore_signal(&sem_no_writers);
        }
        semaphore_signal(&sem_read_switch);
    }

    // Tell main thread that this thread is done
    semaphore_wait(&sem_done);

    /* CRITICAL REGION - START */

    done++;

    /* CRITICAL REGION - END */

    semaphore_signal(&sem_done);

    pthread_exit(EXIT_SUCCESS);
}

semaphore semaphore_init(int init_val) {
    semaphore sem;
    sem.id = 0;
    sem.init_val[0] = init_val;
    sem.acquire.sem_num = 0;
    sem.acquire.sem_op = -1;
    sem.acquire.sem_flg = SEM_UNDO;
    sem.release.sem_num = 0;
    sem.release.sem_op = 1;
    sem.release.sem_flg = SEM_UNDO;

    return sem;
}

void semaphore_get(semaphore* sem) {
    if ((sem->id = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666)) == -1) {
        printf("ERROR: Couldn't get semaphore\n");
        exit(EXIT_FAILURE);
    }

    if (semctl(sem->id, 0, SETALL, sem->init_val) == -1) {
        printf("ERROR: Couldn't initialize semaphore\n");
        exit(EXIT_FAILURE);
    }
}

void semaphore_wait(semaphore* sem) {
    if (semop(sem->id, &sem->acquire, 1) == -1) {
        printf("ERROR: Can't start critical region\n");
        exit(EXIT_FAILURE);
    }
}

void semaphore_signal(semaphore* sem) {
    if(semop(sem->id, &sem->release, 1) == -1) {
        printf("ERROR: Can't exit critical region\n");
        semctl(sem->id, 0, IPC_RMID);
        exit(EXIT_FAILURE);
    }
}

void semaphore_delete(semaphore* sem) {
    semctl(sem->id, 0, IPC_RMID, 0);
}

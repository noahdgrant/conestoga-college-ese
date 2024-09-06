/*
* Operating Systems Assignment 3
* Author: Noah Grant
* Date: November 10, 2023
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#define NUM_OBSERVERS 4
#define NUM_VALID_OUTPUTS 3

void* subject(void* p);
void* observer(void* p);

int output;                         // Random integer
pthread_mutex_t outputMutex;        // MUTEX to protect 'output' variable
pthread_cond_t outputUpdate;        // Condition variable to signal 'output' update

int done;                           // Number of observer threads that are done 
pthread_mutex_t doneMutex;          // MUTEX to protect 'done' variable

int main() {
    pthread_t sub;
    pthread_t observerID[NUM_OBSERVERS];
    pthread_attr_t attr;
    long mod[NUM_OBSERVERS] = {3, 5, 7, 25};

    // Initialize MUTEX
    if (pthread_mutex_init(&outputMutex, NULL) != 0) {
        perror("Output MUTEX creation failed\n");
        exit(EXIT_FAILURE);
    }
    
    if (pthread_mutex_init(&doneMutex, NULL) != 0) {
        perror("Done MUTEX creation failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialize condition variable
    if (pthread_cond_init(&outputUpdate, NULL) != 0) {
        perror("Output conditional variable creation failed...\n");
        exit(EXIT_FAILURE);
    }
    
    // Initialize threads through thread attribute configuration
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
    
    // Initialize threads
    if (pthread_create(&sub, &attr, subject, NULL) != 0) {
        perror("Subject thread creation failed, exiting...\n");
        exit(EXIT_FAILURE);
    }
    
    for (int i = 0; i < NUM_OBSERVERS; i++) {
        if (pthread_create(&observerID[i], &attr, observer, (void*)mod[i]) != 0) {
            printf("Observer %u thread creation failed, exiting...\n", (int)observerID[i]);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to finish - non-blocking main thread
    while (1) {
        pthread_mutex_lock(&doneMutex);
        if (done < NUM_OBSERVERS) {
            // Threads still working

            // Uncomment the line below if you want to see the main thread waiting for observers to finish
            // I comment it out for now because it makes the output a lot cleaning
//            printf("[Main] %d / %d threads done...waiting for threads\n", done, NUM_OBSERVERS);
            pthread_mutex_unlock(&doneMutex);
        }
        else {
            // All threads are done
            break;
        }
    }
    
    printf("[Main] %d / %d threads done...killing subject thread\n", done, NUM_OBSERVERS);
    pthread_kill(sub, SIGKILL);

    // Clean up MUTEXs
    pthread_mutex_destroy(&outputMutex);
    pthread_mutex_destroy(&doneMutex);
    
    // Clean up condition variables
    pthread_cond_destroy(&outputUpdate);

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
            pthread_mutex_lock(&outputMutex);
            output = tmp;
            pthread_cond_broadcast(&outputUpdate);
            pthread_mutex_unlock(&outputMutex);
        }
    }
    
    pthread_exit(EXIT_SUCCESS);
}

// Function for Observer threads
void* observer(void* p) {
    long value = (long)p;
    int valid = 0;

    while (valid < NUM_VALID_OUTPUTS) {
        pthread_mutex_lock(&outputMutex);
        pthread_cond_wait(&outputUpdate, &outputMutex);
        if (output % value == 0) {
            printf("[Observer %ld] Output = %d\n", value, output);
            valid++;
        }
        pthread_mutex_unlock(&outputMutex);
    }

    pthread_mutex_lock(&doneMutex);
    done++;
    pthread_mutex_unlock(&doneMutex);

    pthread_exit(EXIT_SUCCESS);
}


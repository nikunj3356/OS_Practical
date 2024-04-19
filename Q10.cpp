#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;
#define TRUE 1
#define FALSE 0

int flags[2];
int turn;
int shared_resource = 0;

sem_t semaphore;

void* thread1(void* arg) {
    int i;
    for (i = 0; i < 5; i++) {
        // Entry section
        flags[0] = TRUE;
        turn = 1;
        while (flags[1] && turn == 1)
            ; // Busy wait

        // Critical section
        sem_wait(&semaphore);
        cout << "Thread 1 is in critical section\n";
        shared_resource++;
        sem_post(&semaphore);

        // Exit section
        flags[0] = FALSE;

        // Remainder section
        cout << "Thread 1 is in remainder section\n";
    }
    pthread_exit(NULL);
}

void* thread2(void* arg) {
    int i;
    for (i = 0; i < 5; i++) {
        // Entry section
        flags[1] = TRUE;
        turn = 0;
        while (flags[0] && turn == 0)
            ; // Busy wait

        // Critical section
        sem_wait(&semaphore);
        cout << "Thread 2 is in critical section\n";
        shared_resource--;
        sem_post(&semaphore);

        // Exit section
        flags[1] = FALSE;

        // Remainder section
        cout << "Thread 2 is in remainder section\n";
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid1, tid2;

    // Initialize semaphore
    sem_init(&semaphore, 0, 1);

    // Create threads
    pthread_create(&tid1, NULL, thread1, NULL);
    pthread_create(&tid2, NULL, thread2, NULL);

    // Join threads
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Destroy semaphore
    sem_destroy(&semaphore);

    cout << "Shared resource value: " << shared_resource << endl;

    return 0;
}
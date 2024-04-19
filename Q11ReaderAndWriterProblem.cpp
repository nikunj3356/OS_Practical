#include <semaphore.h>
#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

sem_t semaphoreX, semaphoreY;
pthread_t writerThread, readerThreads[100];
int readerCount = 0;

void* reader(void* param) {
    sem_wait(&semaphoreX);
    readerCount++;
    if (readerCount == 1)
        sem_wait(&semaphoreY);
    sem_post(&semaphoreX);
    cout << readerCount << " reader is inside" << endl;
    usleep(3);
    sem_wait(&semaphoreX);
    readerCount--;
    if (readerCount == 0) {
        sem_post(&semaphoreY);
    }
    sem_post(&semaphoreX);
    cout << readerCount + 1 << " Reader is leaving" << endl;
    return NULL;
}

void* writer(void* param) {
    cout << "Writer is trying to enter" << endl;
    sem_wait(&semaphoreY);
    cout << "Writer has entered" << endl;
    sem_post(&semaphoreY);
    cout << "Writer is leaving" << endl;
    return NULL;
}

int main() {
    int numReaders, i;
    cout << "Enter the number of readers: ";
    cin >> numReaders;
    cout << endl;
    sem_init(&semaphoreX, 0, 1);
    sem_init(&semaphoreY, 0, 1);
    for (i = 0; i < numReaders; i++) {
        pthread_create(&writerThread, NULL, reader, NULL);
        pthread_create(&readerThreads[i], NULL, writer, NULL);
    }
    for (i = 0; i < numReaders; i++) {
        pthread_join(writerThread, NULL);
        pthread_join(readerThreads[i], NULL);
    }
    return 0;
}

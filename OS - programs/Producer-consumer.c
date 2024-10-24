#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
#define NUM_ITEMS 10
int buffer[BUFFER_SIZE];
int in = 0; // Index for next item to produce
int out = 0; // Index for next item to consume
sem_t empty; // Semaphore to count empty slots
sem_t full; // Semaphore to count full slots
pthread_mutex_t mutex; // Mutex for critical section
void* producer(void* arg) {
for (int i = 0; i < NUM_ITEMS; i++) {
int item = rand() % 100; // Produce an item
sem_wait(&empty); // Decrease the count of empty slots
pthread_mutex_lock(&mutex); // Enter critical section
// Add item to buffer
buffer[in] = item;
printf("Producer produced: %d\n", item);
in = (in + 1) % BUFFER_SIZE;
pthread_mutex_unlock(&mutex); // Exit critical section
sem_post(&full); // Increase the count of full slots
sleep(rand() % 2); // Simulate variable production time
}
return NULL;
}
void* consumer(void* arg) {
for (int i = 0; i < NUM_ITEMS; i++) {
sem_wait(&full); // Decrease the count of full slots
pthread_mutex_lock(&mutex); // Enter critical section
// Remove item from buffer
int item = buffer[out];
printf("Consumer consumed: %d\n", item);
out = (out + 1) % BUFFER_SIZE;
pthread_mutex_unlock(&mutex); // Exit critical section
sem_post(&empty); // Increase the count of empty slots
sleep(rand() % 2); // Simulate variable consumption time
}
return NULL;
}
int main() {
pthread_t prod, cons;
// Initialize semaphores and mutex
sem_init(&empty, 0, BUFFER_SIZE); // All slots are empty initially
sem_init(&full, 0, 0); // No slots are full initially
pthread_mutex_init(&mutex, NULL);
// Create producer and consumer threads
pthread_create(&prod, NULL, producer, NULL);
pthread_create(&cons, NULL, consumer, NULL);
// Wait for threads to finish
pthread_join(prod, NULL);
pthread_join(cons, NULL);
// Cleanup
sem_destroy(&empty);
sem_destroy(&full);
pthread_mutex_destroy(&mutex);
return 0;
}
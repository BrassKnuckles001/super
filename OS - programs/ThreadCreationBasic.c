#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void *threadFunction(void *arg)
{
    int threadID = *((int *)arg);
    printf("Hello from thread %d!\n", threadID);
    sleep(1);
    printf("Thread %d finished execution.\n", threadID);
    return NULL;
}
int main()
{
    pthread_t threads[7];
    int threadIDs[7];

    for (int i = 0; i < 7; i++)
    {
        threadIDs[i] = i + 1;

        if (pthread_create(&threads[i], NULL, threadFunction, &threadIDs[i]))
        {
            perror("Failed to create thread");
            return 1;
        }
    }
    for (int i = 0; i < 7; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("All threads have finished execution.\n");
    return 0;
}
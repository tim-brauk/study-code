#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_ITERATIONS 100000
#define NUM_ITERATIONS2 150000
int counter = 0;
pthread_mutex_t mutex;
void* increment(void* arg)
{
    for(int i = 0; i < NUM_ITERATIONS; i++)
    {
        pthread_mutex_lock(&mutex);
        counter++;//kritscher abschnitt
        pthread_mutex_unlock(&mutex);

    }
    return NULL;
}

void* dekrement(void* arg)
{
    for (int i = 0; i < NUM_ITERATIONS2; i++)
    {
        pthread_mutex_lock(&mutex);
        counter--;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_t thread1,thread2,thread3;
    pthread_create(&thread1, NULL, increment, NULL);
    pthread_create(&thread2, NULL, increment, NULL);
    pthread_create(&thread3,NULL, dekrement, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2,NULL);
    pthread_join(thread3,NULL);
    pthread_mutex_destroy(&mutex);
    printf("Counter: %d\n", counter);
    return 0;
}
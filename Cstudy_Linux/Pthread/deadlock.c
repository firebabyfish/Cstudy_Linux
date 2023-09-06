#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t mutex_1, mutex_2;

void *work_1()
{
    pthread_mutex_lock(&mutex_1);
    sleep(1);
    pthread_mutex_lock(&mutex_2);
    printf("work_1...\n");
    pthread_mutex_unlock(&mutex_2);
    pthread_mutex_unlock(&mutex_1);
}

void *work_2()
{
    pthread_mutex_lock(&mutex_2);
    pthread_mutex_lock(&mutex_1);
    printf("work_2...\n");
    pthread_mutex_unlock(&mutex_1);
    pthread_mutex_unlock(&mutex_2);
}

int main()
{
    pthread_mutex_init(&mutex_1, NULL);
    pthread_mutex_init(&mutex_2, NULL);

    pthread_t tid_1, tid_2;

    pthread_create(&tid_1, NULL, work_1, NULL);
    pthread_create(&tid_2, NULL, work_2, NULL);

    pthread_join(tid_2, NULL);
    pthread_join(tid_1, NULL);

    pthread_mutex_destroy(&mutex_2);
    pthread_mutex_destroy(&mutex_1);

    return 0;
}
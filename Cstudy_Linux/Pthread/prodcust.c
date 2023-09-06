/*
    简易生产者消费者模型
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct Node
{
    int num;
    struct Node* next;
};

struct Node *head = NULL;
pthread_mutex_t mutex;
pthread_cond_t cond;

void *producer(void *arg)
{
    // 不断添加新的结点添加到链表中
    while (1)
    {
        pthread_mutex_lock(&mutex);
        struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->num = rand() % 100;
        printf("add Node, num : %d, tid : %ld\n", newNode->num, pthread_self());

        // 只要生产就通知消费
        pthread_cond_signal(&cond);

        pthread_mutex_unlock(&mutex);
        usleep(100);
    }

    return NULL;

}

void *customer(void *arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
        struct Node *tmp = head;
        if (head != NULL)
        {
            head = head->next;
            printf("del Node, num : %d, tid : %ld\n", tmp->num, pthread_self());
            free(tmp);
            pthread_mutex_unlock(&mutex);
            usleep(100);
        }
        else 
        {
            // 没有生产，需要等待
            pthread_cond_wait(&cond, &mutex);
            pthread_mutex_unlock(&mutex);
        }
    }

    return NULL;
    
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_t proc[5], cust[5];
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&proc[i], NULL, producer, NULL);
        pthread_create(&proc[i], NULL, customer, NULL);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_detach(proc[i]);
        pthread_detach(cust[i]);
    }

    while (1)
    {
        // 延时防止互斥量直接被销毁
        sleep(10);
    }

    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    return 0;
}
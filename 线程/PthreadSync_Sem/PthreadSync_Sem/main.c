//
//  main.c
//  PthreadSync_Sem
//
//  Created by macuser on 16/6/20.
//  Copyright © 2016年 ndl. All rights reserved.
//

#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>


sem_t sem1;
sem_t sem2;

void thread_a(void *arg){
    sem_wait(&sem1);
    printf("thread a\n");
}

void thread_b(void *arg){
    sem_wait(&sem2);//阻塞直到sem2大于0
    printf("thread b\n");
    sem_post(&sem1);
}

void thread_c(void* arg){
    printf("thread c\n");
    sem_post(&sem2);
}

//线程按照c->b->a执行
int main(int argc, const char * argv[]) {
    pthread_t a,b,c;
    
    sem_init(&sem1, 0, 0);
    sem_init(&sem2, 0, 0);
    
    pthread_create(&a, NULL, (void *)thread_a, NULL);
    pthread_create(&b, NULL, (void *)thread_b, NULL);
    pthread_create(&c, NULL, (void *)thread_c, NULL);
    
    pthread_join(a, NULL);
    pthread_join(b, NULL);
    pthread_join(c, NULL);
    
    sem_destroy(&sem1);
    sem_destroy(&sem2);
    return 0;
}

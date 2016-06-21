//
//  main.c
//  PthreadSync_cond
//
//  Created by macuser on 16/6/21.
//  Copyright © 2016年 ndl. All rights reserved.
//

#include <stdio.h>
#include <pthread.h>

char buffer[128];
int bufferHasData = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void readBuffer(void *arg){
    while (1) {
        
        pthread_mutex_lock(&mutex);
        printf("start\n");
        if (!bufferHasData) {
            pthread_cond_wait(&cond, &mutex);
        }
        //printf("signaled\n");
        printf("read!!!   data = %s\n",buffer);
        bufferHasData = 0;
        pthread_mutex_unlock(&mutex);
    }
}

void writeBuffer(char *data){
    printf("write buffer\n");
    pthread_mutex_lock(&mutex);
    //printf("here\n");
    if (bufferHasData == 0) {
        sprintf(buffer, "%s", data);
        printf("write!!!   data = %s\n",buffer);
        bufferHasData = 1;
        pthread_cond_signal(&cond);
    }
    pthread_mutex_unlock(&mutex);
}

int main(int argc, const char * argv[]) {
//    char buf[128];
//    sprintf(buf, "%s", "wwwww");
//    printf("%s\n",buf);//wwwww
//    sprintf(buf, "%s", "sss");
//    printf("%s\n",buf);//sss
    
    char input[128];
    pthread_t readThread;
    
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_create(&readThread, NULL, (void *)readBuffer, NULL);
    
    while (1) {
        scanf("%s",input);
        writeBuffer(input);
    }
    
    
    return 0;
}

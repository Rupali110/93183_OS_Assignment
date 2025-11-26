#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_sun, sem_info;

void* print_sun(void *arg) {
    while(1) {
        sem_wait(&sem_sun);
        printf("SUNBEAM\n");
        fflush(stdout);
        sem_post(&sem_info);
        sleep(1);
    }
    return NULL;
}

void* print_info(void *arg) {
    while(1) {
        sem_wait(&sem_info);
        printf("INFOTECH\n");
        fflush(stdout);
        sem_post(&sem_sun);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t tid1, tid2;
    sem_init(&sem_sun, 0, 1);
    sem_init(&sem_info, 0, 0);

    pthread_create(&tid1, NULL, print_sun, NULL);
    pthread_create(&tid2, NULL, print_info, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&sem_sun);
    sem_destroy(&sem_info);
    return 0;
}


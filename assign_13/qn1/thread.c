#include <stdio.h>
#include <pthread.h>

#define SIZE 10

void* thread_func(void *param) {
    int *arr = (int*)param;
    for(int i = 0; i < SIZE - 1; i++) {
        int min_idx = i;
        for(int j = i + 1; j < SIZE; j++) {
            if(arr[j] < arr[min_idx])
                min_idx = j;
        }
        int temp = arr[i];
        arr[i] = arr[min_idx];
        arr[min_idx] = temp;
    }
    return NULL;
}

int main() {
    pthread_t tid;
    int arr[SIZE] = {29, 10, 14, 37, 13, 5, 22, 8, 19, 1};
    pthread_create(&tid, NULL, thread_func, (void*)arr);
    pthread_join(tid, NULL);
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}


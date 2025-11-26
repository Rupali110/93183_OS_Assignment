#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct array {
    int *arr;
    int size;
};

void* thread_func(void *param) {
    struct array *a = (struct array*)param;
    int n = a->size;
    int *arr = a->arr;
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    return NULL;
}

int main() {
    pthread_t tid;
    int n;
    scanf("%d", &n);
    int *arr = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct array a = {arr, n};
    pthread_create(&tid, NULL, thread_func, (void*)&a);
    pthread_join(tid, NULL);

    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}


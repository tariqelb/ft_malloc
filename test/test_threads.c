#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 10
#define ALLOCS_PER_THREAD 100
#define ALLOC_SIZE 1024

void *thread_func(void *arg) {
    int i;
    char *addr;

    for (i = 0; i < ALLOCS_PER_THREAD; i++) {
        addr = (char *)malloc(ALLOC_SIZE);
        if (addr == NULL) {
            write(1, "ERROR: malloc failed in thread\n", 31);
            return (NULL);
        }
        addr[0] = 'a';
        free(addr);
    }
    return (NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int i;

    for (i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, thread_func, NULL) != 0) {
            write(1, "ERROR: pthread_create failed\n", 29);
            return (1);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    write(1, "Thread test completed successfully.\n", 36);
    return (0);
}

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// Shared resource (replace with your actual data structure)
int counter = 0;

// Mutex lock for synchronization
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* increment(void* arg) {
    int num_iterations = *((int*)arg);  // Cast argument to integer

    for (int i = 0; i < num_iterations; i++) {
        // Lock the mutex before accessing the shared resource
        pthread_mutex_lock(&mutex);

        counter++;
        printf("Process %d incremented counter to: %d\n", (int)pthread_self(), counter);

        // Unlock the mutex after accessing the shared resource
        pthread_mutex_unlock(&mutex);

        // Simulate some work done by the process
        sleep(1);
    }

    return NULL;
}

int main() {
    int num_processes = 2;  // Adjust as needed
    int iterations = 5;     // Adjust as needed

    pthread_t threads[num_processes];

    // Create threads and pass the number of iterations as an argument
    for (int i = 0; i < num_processes; i++) {
        if (pthread_create(&threads[i], NULL, increment, &iterations) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_processes; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            return 1;
        }
    }

    printf("Final counter value: %d\n", counter);

    return 0;
}

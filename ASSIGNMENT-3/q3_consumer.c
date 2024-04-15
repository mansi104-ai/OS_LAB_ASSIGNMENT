#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 100

// Structure to store the message content (same as producer)
typedef struct {
    long mtype;
    char data[MAX_SIZE];
} message_t;

int main() {
    // Open the message queue created by the producer
    key_t key = ftok(".", 'p');
    int msgqid = msgget(key, 0);  // Open existing queue

    if (msgqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    message_t msg;

    // Receive messages from the queue
    for (int i = 0; i < 5; i++) {
        if (msgrcv(msgqid, &msg, sizeof(msg.data), 1, 0) == -1) {  // Receive message with type 1
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        printf("Consumer received message: %s\n", msg.data);
    }

    printf("Consumer finished receiving messages.\n");

    return EXIT_SUCCESS;
}

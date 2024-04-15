#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_SIZE 100  // Adjust as needed

// Structure to store the message content
typedef struct {
    long mtype;
    char data[MAX_SIZE];
} message_t;

int main() {
    // Create a message queue
    key_t key = ftok(".", 'p');  // Generate unique key based on filename and character
    int msgqid = msgget(key, IPC_CREAT | 0666);  // Create queue with read/write permissions

    if (msgqid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    message_t msg;

    // Simulate data generation and sending messages
    for (int i = 0; i < 5; i++) {
        snprintf(msg.data, MAX_SIZE, "Item %d", i);  // Format data into message
        msg.mtype = 1;  // Message type (adjust if needed)

        if (msgsnd(msgqid, &msg, sizeof(msg.data), 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        printf("Producer sent message: %s\n", msg.data);
        sleep(1);  // Simulate work done by producer
    }

    printf("Producer finished sending messages.\n");

    // Remove the message queue (optional)
    if (msgctl(msgqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

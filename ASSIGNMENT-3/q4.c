#include <stdio.h>
#include <stdlib.h>
#include <limits.h>  // For INT_MAX

// Process structure (consider adding fields like process ID, arrival time, etc.)
typedef struct {
    int burst_time;
    int priority;  // Lower value indicates higher priority
} process_t;

// Function prototypes
void fcfs(process_t processes[], int n);
void round_robin(process_t processes[], int n, int quantum);
void priority(process_t processes[], int n);

// Function to swap two process structures
void swap(process_t *a, process_t *b) {
    process_t temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;  // Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input validation: Ensure positive number of processes
    if (n <= 0) {
        fprintf(stderr, "Invalid number of processes: %d\n", n);
        exit(EXIT_FAILURE);
    }

    process_t processes[n];

    // Input validation: Ensure non-negative burst times
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        if (processes[i].burst_time < 0) {
            fprintf(stderr, "Invalid burst time: %d\n", processes[i].burst_time);
            exit(EXIT_FAILURE);
        }
    }

    int choice;
    printf("\nScheduling algorithms:\n");
    printf("1. First Come First Served (FCFS)\n");
    printf("2. Round Robin (RR)\n");
    printf("3. Priority Scheduling (non-preemptive)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(processes, n);
            break;
        case 2:
            int quantum;
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &quantum);
            round_robin(processes, n, quantum);
            break;
        case 3:
            // Input validation: Ensure valid priorities (lower value = higher priority)
            for (int i = 0; i < n; i++) {
                printf("Enter priority for process %d (lower value = higher priority): ", i + 1);
                scanf("%d", &processes[i].priority);
            }
            priority(processes, n);
            break;
        default:
            printf("Invalid choice.\n");
    }

    return 0;
}

// FCFS (First Come First Served)
void fcfs(process_t processes[], int n) {
    int waiting_time[n], completion_time[n], avg_wt = 0, avg_ct = 0;

    for (int i = 0; i < n; i++) {
        waiting_time[i] = 0;
        if (i > 0) {
            waiting_time[i] = completion_time[i - 1];
        }
        completion_time[i] = waiting_time[i] + processes[i].burst_time;
        avg_wt += waiting_time[i];
        avg_ct += completion_time[i];
    }

    printf("\nProcess\tBurst Time\tWaiting Time\tCompletion Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processes[i].burst_time, waiting_time[i], completion_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)avg_wt / n);
    printf("Average Completion Time: %.2f\n", (float)avg_ct / n);
}

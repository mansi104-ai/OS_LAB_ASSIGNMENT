#include <stdio.h>
#include <limits.h>  // For INT_MAX

// Process structure
typedef struct {
    int pid;  // Process ID
    int burst_time;
    int arrival_time;  // Consider adding this for advanced algorithms
    int priority;  // Lower value indicates higher priority
    int completion_time;
    int turn_around_time;
    int waiting_time;
} process_t;

// Function prototypes
void fcfs(process_t processes[], int n);
void round_robin(process_t processes[], int n, int quantum);
void priority(process_t processes[], int n);
void calculate_performance(process_t processes[], int n);

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

    // Input process details (burst time, optional: arrival time, priority)
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;  // Assign process ID
        printf("Enter burst time for process %d: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);

        // Input validation: Ensure non-negative burst times
        if (processes[i].burst_time < 0) {
            fprintf(stderr, "Invalid burst time: %d\n", processes[i].burst_time);
            exit(EXIT_FAILURE);
        }

        // Consider adding input for arrival time and priority based on your requirements
    }

    // Function calls for each scheduling algorithm
    printf("\n** FCFS Algorithm Results:**\n");
    fcfs(processes, n);

    printf("\n\n** Round Robin Algorithm Results (time quantum = 2):**\n");
    round_robin(processes, n, 2);  // Adjust quantum as needed

    printf("\n\n** Priority Algorithm Results:**\n");
    priority(processes, n);

    // Calculate and display performance metrics
    printf("\n** Performance Comparison:\n");
    calculate_performance(processes, n);

    return 0;
}

// FCFS (First Come First Served)
void fcfs(process_t processes[], int n) {
    int waiting_time[n], completion_time[n], avg_wt = 0, avg_ct = 0;
    int current_time = 0;  // Track current time for process execution

    for (int i = 0; i < n; i++) {
        waiting_time[i] = current_time;
        completion_time[i] = waiting_time[i] + processes[i].burst_time;
        processes[i].turn_around_time = completion_time[i] - processes[i].arrival_time;  // Adjust if arrival time is used
        processes[i].waiting_time = waiting_time[i];
        current_time = completion_time[i];

        avg_wt += waiting_time[i];
        avg_ct += completion_time[i];
    }

    printf("Process\tBurst Time\tWaiting Time\tTurn Around Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].waiting_time, processes[i].turn_around_time);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)avg_wt / n);
    printf("Average Completion Time: %.2f\n", (float)avg_ct / n);
}

// Round Robin
void round_robin(process_t processes[], int n, int quantum) {
    int remaining_time[n];  // Keep track of remaining burst time for each process
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    fprintf(stderr, "Failed to fork process\n");
    return 1;
  } else if (pid == 0) {
    // Child process
    printf("Child process: PID = %d\n", getpid());
  } else {
    // Parent process
    printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
    int status;
    wait(&status); // Wait for child process to finish
    printf("Parent process: Child process exited with status %d\n", status);
  }

  return 0;
}

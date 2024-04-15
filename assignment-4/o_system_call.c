#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // For write()

int main(int argc, char *argv[]) {
    // Check for correct usage (program name and filename)
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the file for writing
    FILE *fp = fopen(argv[1], "w");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Get the value of n (assuming it's already defined or read from user input)
    int n;  // Replace with your logic to obtain the value of n

    // Write the value of n to the file
    ssize_t bytes_written = write(fileno(fp), &n, sizeof(n));
    if (bytes_written == -1) {
        perror("write");
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    // Success message (consider using fflush(fp) for buffered output if needed)
    printf("Value %d written to file: %s\n", n, argv[1]);

    // Close the file
    if (fclose(fp) != 0) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

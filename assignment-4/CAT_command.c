0#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if a filename is provided
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open the file in read mode
    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    // Read and print characters until the end of the file
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    // Close the file
    if (fclose(fp) != 0) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

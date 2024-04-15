#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // For string manipulation (strcpy)

int main(int argc, char *argv[]) {
    // Check for correct usage (program name, source, and destination)
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Copy source and destination filenames
    char source_file[1024];  // Adjust size as needed
    char destination_file[1024];
    strcpy(source_file, argv[1]);
    strcpy(destination_file, argv[2]);

    // Open source file for reading
    FILE *fp_source = fopen(source_file, "rb");
    if (fp_source == NULL) {
        perror("fopen (source)");
        exit(EXIT_FAILURE);
    }

    // Open destination file for writing (create if it doesn't exist)
    FILE *fp_dest = fopen(destination_file, "wb");
    if (fp_dest == NULL) {
        perror("fopen (destination)");
        fclose(fp_source);  // Close source even on destination error
        exit(EXIT_FAILURE);
    }

    // Copy file contents in a loop (replace with more efficient buffer if needed)
    int ch;
    while ((ch = fgetc(fp_source)) != EOF) {
        if (fputc(ch, fp_dest) == EOF) {
            perror("fputc");
            fclose(fp_source);
            fclose(fp_dest);
            exit(EXIT_FAILURE);
        }
    }

    // Close files
    if (fclose(fp_source) != 0 || fclose(fp_dest) != 0) {
        perror("fclose");
        exit(EXIT_FAILURE);
    }

    printf("File '%s' copied to '%s' successfully.\n", source_file, destination_file);

    return EXIT_SUCCESS;
}

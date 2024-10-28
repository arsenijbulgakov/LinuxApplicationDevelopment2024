#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define ARGS_ERROR 1
#define OPEN_ERROR 2
#define CLOSE_ERROR 3
#define READ_ERROR 4
#define WRITE_ERROR 5
#define REMOVE_ERROR 6



FILE* open_file(const char *filename, const char *mode) {
    FILE *file = fopen(filename, mode);

    if (!file) {
        fprintf(stderr, "%s: can't open file\n", filename);
        exit(OPEN_ERROR);
    }

    return file;
}

void close_file(FILE *file, const char *filename) {
    if (fclose(file)) {
        fprintf(stderr, "%s: can't close file\n", filename);
        exit(CLOSE_ERROR);
    }
}


void move_file(const char *infile_name, const char *outfile_name) {
    FILE *infile;
    FILE *outfile;

    int c;

    infile = open_file(infile_name, "r");
    outfile = open_file(outfile_name, "w");

    while ((c = fgetc(infile)) != EOF) {
        
        fputc(c, outfile);
        fflush(outfile);

        if (ferror(outfile)) {
            fclose(infile);
            fclose(outfile);
            remove(infile_name);
            fprintf(stderr, "%s: can't write to file\n", outfile_name);
            exit(WRITE_ERROR);
        }
    }

    if (ferror(infile)) {
        fclose(infile);
        fclose(outfile);
        remove(infile_name);
        fprintf(stderr, "%s: can't read from file\n", infile_name);
        exit(READ_ERROR);
    }

    close_file(outfile, outfile_name);
    close_file(infile, infile_name);

    if (remove(infile_name)) {
        fprintf(stderr, "%s: can't remove file\n", infile_name);
        exit(REMOVE_ERROR);
    }
}


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: move infile outfile\n");
        return ARGS_ERROR;
    }

    move_file(argv[1], argv[2]);

    return 0;
}
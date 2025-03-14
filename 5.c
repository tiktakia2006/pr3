#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_FILE_SIZE 1024 * 1024 // 1 MB

void check_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    if (ftell(file) > MAX_FILE_SIZE) {
        printf("File size limit exceeded\n");
        exit(1);
    }
    fseek(file, 0, SEEK_SET);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    FILE *src = fopen(argv[1], "r");
    if (!src) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    FILE *dst = fopen(argv[2], "w");
    if (!dst) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(src);
        return 1;
    }

    check_file_size(src);

    char ch;
    while ((ch = fgetc(src)) != EOF) {
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);

    return 0;
}

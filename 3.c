#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_FILE_SIZE 100

int main() {
    FILE *file = fopen("dice_rolls.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    int roll;
    srand(time(NULL));

    for (int i = 0; i < 1000; i++) {
        roll = (rand() % 6) + 1;

        fseek(file, 0, SEEK_END);
        if (ftell(file) >= MAX_FILE_SIZE) {
            printf("File size limit reached\n");
            fclose(file);
            return 0;
        }

        fprintf(file, "%d\n", roll);
    }

    printf("Data successfully written to file\n");

    fclose(file);
    return 0;
}



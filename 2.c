#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int i = 0;
    int max_files = 5000;
    int fds[max_files];

    for (i = 0; i < max_files; i++) {
        fds[i] = open("tempfile.txt", O_CREAT | O_WRONLY, 0666);
        if (fds[i] < 0) {
            perror("Failed to open file");
            break;
        }
    }

    printf("Opened %d files successfully.\n", i);

    for (int j = 0; j < i; j++) {
        close(fds[j]);
    }

    return 0;
}


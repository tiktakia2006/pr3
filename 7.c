#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
    struct rlimit limit;

    if (getrlimit(RLIMIT_NOFILE, &limit) == 0) {
        printf("Soft limit for open files: %ld\n", limit.rlim_cur);
        printf("Hard limit for open files: %ld\n", limit.rlim_max);
    } else {
        perror("getrlimit for RLIMIT_NOFILE");
    }

    if (getrlimit(RLIMIT_NPROC, &limit) == 0) {
        printf("Soft limit for processes: %ld\n", limit.rlim_cur);
        printf("Hard limit for processes: %ld\n", limit.rlim_max);
    } else {
        perror("getrlimit for RLIMIT_NPROC");
    }

    return 0;
}

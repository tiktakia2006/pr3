#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>

#define MAX_CPU_TIME 5

void set_cpu_time_limit() {
    struct rlimit rl;
    rl.rlim_cur = rl.rlim_max = MAX_CPU_TIME;
    if (setrlimit(RLIMIT_CPU, &rl) == -1) {
        perror("Failed to set CPU time limit");
        exit(1);
    }
}

void generate_lottery_numbers() {
    int i, num;
    int numbers_49[49], numbers_36[36];
    int selected_49[7], selected_36[6];

    for (i = 0; i < 49; i++) numbers_49[i] = i + 1;
    for (i = 0; i < 36; i++) numbers_36[i] = i + 1;

    for (i = 0; i < 7; i++) {
        num = rand() % (49 - i);
        selected_49[i] = numbers_49[num];
        numbers_49[num] = numbers_49[49 - i - 1];
    }

    for (i = 0; i < 6; i++) {
        num = rand() % (36 - i);
        selected_36[i] = numbers_36[num];
        numbers_36[num] = numbers_36[36 - i - 1];
    }

    printf("7 numbers from 49: ");
    for (i = 0; i < 7; i++) printf("%d ", selected_49[i]);
    printf("\n6 numbers from 36: ");
    for (i = 0; i < 6; i++) printf("%d ", selected_36[i]);
    printf("\n");
}

int main() {
    set_cpu_time_limit();
    srand(time(NULL));

    generate_lottery_numbers();
    return 0;
}

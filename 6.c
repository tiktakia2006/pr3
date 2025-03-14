#include <stdio.h>

void recursiveFunction(int n) {
    if (n == 0) {
        return;
    }
    printf("Recursive call: %d\n", n);
    recursiveFunction(n - 1);
}

int main() {
    int depth = 10000;
    printf("Start of recursion\n");
    recursiveFunction(depth);
    return 0;
}

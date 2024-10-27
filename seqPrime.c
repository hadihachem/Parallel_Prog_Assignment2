#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {
    int n = 100000;
    int *array = malloc((n + 1) * sizeof(int));
    clock_t start_time = clock();
    for (int i = 2; i <= n; i++) {
        array[i] = 1;
    }
    for (int p = 2; p <= sqrt(n); p++) {
        if (array[p]) {
            for (int i = p * p; i <= n; i += p) {
                array[i] = 0;
            }
        }
    }

    clock_t end_time = clock();
    double elapsed = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %f seconds\n", elapsed);
    return 0;
}
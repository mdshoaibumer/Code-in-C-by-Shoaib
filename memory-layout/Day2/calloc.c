#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)calloc(5, sizeof(int)); // Allocate and initialize 5 integers
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    for (int i = 0; i < 5; i++) {
        printf("%d ", ptr[i]); // Should print zeros
    }
    free(ptr);
    ptr = NULL;
    return 0;
}
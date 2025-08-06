#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(5 * sizeof(int)); // Allocate for 5 integers
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    for (int i = 0; i < 5; i++) {
        ptr[i] = i + 1;
    }
    ptr = (int *)realloc(ptr, 8 * sizeof(int)); // Resize to 8 integers
    if (ptr == NULL) {
        printf("Memory reallocation failed\n");
        return -1;
    }
    for (int i = 5; i < 8; i++) {
        ptr[i] = i + 1; // Initialize new elements
    }
    for (int i = 0; i < 8; i++) {
        printf("%d ", ptr[i]);
    }
    free(ptr);
    ptr = NULL;
    return 0;
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptr = (int *)malloc(5 * sizeof(int));
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
        return -1;
    }
    free(ptr); // Free the allocated memory
    ptr = NULL; // Prevent dangling pointer
    return 0;
}
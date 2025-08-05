#include <stdio.h>
#include <stdlib.h>

int main() {
    // Allocate memory on the Heap
    int* heap_var = (int*)malloc(sizeof(int));
    if (heap_var != NULL) {
        *heap_var = 40;  // Assign a value
        printf("Heap variable: %d, Address: %p\n", *heap_var, (void*)heap_var);
        free(heap_var);  // Free the memory
    } else {
        printf("Memory allocation failed\n");
    }
    return 0;
}
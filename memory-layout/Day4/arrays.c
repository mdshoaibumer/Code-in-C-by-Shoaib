#include <stdio.h>    // For input/output
#include <stdlib.h>   // For dynamic allocation (malloc, realloc, free)
#include <string.h>   // For string functions and memcpy

// Function to print an array (demonstrates passing array to function)
void printArray(const int arr[], int size) {
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to search for an element (linear search)
int searchElement(const int arr[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            return i;  // Return index if found
        }
    }
    return -1;  // Not found
}

// Comparison function for qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Function definition (placed before use for clarity)
void modifyArray(int arr[], int size) {
    arr[0] = 99;  // Modifies original array
}

// Example function with static minimum size for parameter
void processArray(int arr[static 5]) {
    for (int i = 0; i < 5; i++) {
        arr[i] += 1;
    }
}

// 15. restrict keyword example (optimization hint)
void sumArrays(int n, int *restrict a, int *restrict b, int *restrict c) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

int main() {
    // 1. Basic Array Declaration and Initialization
    int basicArray[5];  // Uninitialized local array (garbage values)
    int initializedArray[5] = {10, 20, 30, 40, 50};
    int partialArray[5] = {1, 2};  
    int autoSizeArray[] = {100, 200, 300};

    basicArray[0] = 5;
    basicArray[1] = 10;
    printf("Basic array first element: %d\n", basicArray[0]);

    printf("Initialized array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", initializedArray[i]);
    }
    printf("\n");

    int size = sizeof(initializedArray) / sizeof(initializedArray[0]);
    printf("Size of initializedArray: %d\n", size);

    // 2. Multi-dimensional Arrays
    int matrix[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("Matrix[1][2]: %d\n", matrix[1][2]);

    printf("Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // 3. Arrays and Pointers
    int *ptr = initializedArray;
    printf("Via pointer: %d\n", *(ptr + 1));

    ptr++;
    *ptr = 25;
    printf("Modified via pointer: %d\n", initializedArray[1]);

    char *strings[3] = {"Hello", "World", "C"};
    printf("First string: %s\n", strings[0]);

    // 4. Passing Arrays to Functions
    printArray(initializedArray, 5);
    modifyArray(initializedArray, 5);
    printArray(initializedArray, 5);

    // 5. Dynamic Arrays
    int *dynamicArray = malloc(4 * sizeof(int));
    if (dynamicArray == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        dynamicArray[i] = i * 10;
    }
    printArray(dynamicArray, 4);

    dynamicArray = realloc(dynamicArray, 6 * sizeof(int));
    dynamicArray[4] = 50;
    dynamicArray[5] = 60;
    printArray(dynamicArray, 6);

    free(dynamicArray);

    // 6. Strings as Char Arrays
    char str[6] = "Hello";
    printf("String: %s\n", str);

    char copy[6];
    strcpy(copy, str);
    printf("Copied string: %s\n", copy);

    printf("Length: %zu\n", strlen(str));

    // 7. Common Operations
    int index = searchElement(initializedArray, 5, 30);
    printf("Index of 30: %d\n", index);

    int unsorted[4] = {40, 10, 30, 20};
    qsort(unsorted, 4, sizeof(int), compare);
    printArray(unsorted, 4);

    int dest[5];
    memcpy(dest, initializedArray, sizeof(initializedArray));
    printArray(dest, 5);

    // 8. Variable-Length Arrays (C99+)
    int vlaSize = 3;
    int vla[vlaSize];
    for (int i = 0; i < vlaSize; i++) {
        vla[i] = i + 1;
    }
    printArray(vla, vlaSize);

    // 9. Designated Initializers (C99)
    int designated[5] = {[2] = 100, [4] = 50};
    printArray(designated, 5);

    // 10. sizeof Pitfall
    int arrLocal[10];
    printf("Size in same scope: %zu\n", sizeof(arrLocal));
    int *arrPtr = arrLocal;
    printf("Size after decay to pointer: %zu\n", sizeof(arrPtr));

    // 11. memset for initialization
    memset(arrLocal, 0, sizeof(arrLocal));
    printArray(arrLocal, 10);

    // 12. Boundary check example (commented to avoid crash)
    // arrLocal[10] = 5;  // Undefined behavior! Index out of bounds.

    // 13. Multidimensional Dynamic Array (single block)
    int rows = 2, cols = 3;
    int *dyn2D = malloc(rows * cols * sizeof(int));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            dyn2D[i * cols + j] = i + j;
        }
    }
    printf("Dynamic 2D array:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", dyn2D[i * cols + j]);
        }
        printf("\n");
    }
    free(dyn2D);

    // 14. const with arrays
    const int constArr[3] = {1, 2, 3};
    printArray(constArr, 3);
    // constArr[0] = 10; // Error: read-only

    int A[3] = {1, 2, 3}, B[3] = {4, 5, 6}, C[3];
    sumArrays(3, A, B, C);
    printArray(C, 3);

    // 16. Static keyword in parameter (min size guarantee)
    processArray(initializedArray);
    printArray(initializedArray, 5);

    return 0;
}

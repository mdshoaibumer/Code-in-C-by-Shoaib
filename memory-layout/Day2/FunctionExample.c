#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    printf("Enter the initial number of elements: ");
    scanf("%d", &n);
    
    // Step 1: Allocate memory for the initial array using malloc
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed for arr\n");
        return -1;
    }
    
    printf("Enter %d elements: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    // Step 2: Allocate memory for cumulative sum using calloc (initialized to 0)
    int *cumsum = (int *)calloc(n, sizeof(int));
    if (cumsum == NULL) {
        printf("Memory allocation failed for cumsum\n");
        free(arr);
        return -1;
    }
    
    // Compute initial cumulative sum
    if (n > 0) {
        cumsum[0] = arr[0];
        for (int i = 1; i < n; i++) {
            cumsum[i] = cumsum[i-1] + arr[i];
        }
    }
    
    // Print initial arrays
    printf("Initial array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\nCumulative sum: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", cumsum[i]);
    }
    printf("\n");
    
    char choice;
    printf("Do you want to add more elements? (y/n): ");
    scanf(" %c", &choice); // Space before %c to consume newline
    
    if (choice == 'y' || choice == 'Y') {
        int m;
        printf("Enter the number of additional elements: ");
        scanf("%d", &m);
        int new_size = n + m;
        
        // Step 3: Resize arr using realloc
        int *new_arr = (int *)realloc(arr, new_size * sizeof(int));
        if (new_arr == NULL) {
            printf("Memory reallocation failed for arr\n");
            free(cumsum);
            free(arr);
            return -1;
        }
        arr = new_arr;
        
        // Resize cumsum using realloc
        int *new_cumsum = (int *)realloc(cumsum, new_size * sizeof(int));
        if (new_cumsum == NULL) {
            printf("Memory reallocation failed for cumsum\n");
            free(arr);
            free(cumsum);
            return -1;
        }
        cumsum = new_cumsum;
        
        printf("Enter %d additional elements: ", m);
        for (int i = n; i < new_size; i++) {
            scanf("%d", &arr[i]);
        }
        
        // Recompute cumulative sum from scratch
        if (new_size > 0) {
            cumsum[0] = arr[0];
            for (int i = 1; i < new_size; i++) {
                cumsum[i] = cumsum[i-1] + arr[i];
            }
        }
        
        // Print updated arrays
        printf("Updated array: ");
        for (int i = 0; i < new_size; i++) {
            printf("%d ", arr[i]);
        }
        printf("\nUpdated cumulative sum: ");
        for (int i = 0; i < new_size; i++) {
            printf("%d ", cumsum[i]);
        }
        printf("\n");
    }
    
    // Step 4: Free allocated memory
    free(arr);
    free(cumsum);
    arr = NULL; // Prevent dangling pointers
    cumsum = NULL;
    
    return 0;
}
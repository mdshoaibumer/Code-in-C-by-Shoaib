**Day 2: Mastering Dynamic Memory Allocation in C**
Welcome to Day 2 of my C programming journey! Today, I dove deep into Dynamic Memory Allocation in C, a powerful feature that allows flexible memory management at runtime. I explored the four key functions—malloc, calloc, realloc, and free—and created a program that combines all of them to manage dynamic arrays. Here's a summary of what I learned and a code example I’m sharing in my GitHub repository.
What I Learned
Dynamic memory allocation in C lets us allocate memory on the heap during program execution, making it ideal for handling data of unknown size, like user inputs or dynamic data structures. The <stdlib.h> library provides:

malloc: Allocates uninitialized memory.
calloc: Allocates and initializes memory to zero.
realloc: Resizes previously allocated memory.
free: Releases memory to prevent leaks.

I learned the importance of checking for NULL pointers after allocation, setting pointers to NULL after freeing to avoid dangling pointers, and handling edge cases like zero-sized allocations. I also discovered real-world applications, such as dynamic arrays and linked lists, and best practices to avoid memory leaks and fragmentation.
Code Example
Below is a program that uses all four functions to manage two arrays: one for user-input numbers and another for their cumulative sum. The program:

Allocates an array with malloc for user input.
Uses calloc for a zero-initialized array to store cumulative sums.
Resizes both arrays with realloc if the user adds more elements.
Frees memory with free to ensure no leaks.

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

Key Takeaways

Flexibility: Dynamic memory allocation adapts to runtime needs, unlike static arrays.
Error Handling: Always check for NULL after allocation and reallocation.
Memory Management: Free memory promptly and set pointers to NULL to avoid issues.
Applications: Useful for dynamic data structures like linked lists or resizable arrays.

What's Next?
Tomorrow, I’ll explore dynamic data structures like linked lists, building on this foundation. Check out the full code in my GitHub repository and let me know your feedback or suggestions! What’s your favorite use of dynamic memory in C? Share your thoughts or questions in the issues section!

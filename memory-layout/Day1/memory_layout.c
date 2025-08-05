#include <stdio.h>
#include <stdlib.h>

/*
 * Memory Segments Diagram
 * ----------------------
 * This diagram illustrates the typical memory layout of a C program with the code segment at the bottom (lowest memory
 * addresses) and the stack at the top (highest memory addresses). The diagram is oriented with the lowest addresses at the
 * bottom of the ASCII art and the highest at the top, as requested. Note: Actual addresses and segment order may vary
 * depending on the OS, compiler, and linker. Addresses are virtual and may be affected by alignment, ASLR, or linker scripts.
 *
 * High Memory Addresses
 * +-------------------------+
 * | Stack                   |  <- Local variables, function call frames (e.g., main_local, local_var)
 * | (Grows downward)        |
 * +-------------------------+
 * | ... (free memory) ...   |
 * +-------------------------+
 * | Heap                    |  <- Dynamically allocated memory (e.g., malloc, calloc)
 * | (Grows upward)          |
 * +-------------------------+
 * | Data Segment            |
 * |   - Read-only Data      |  <- String literals (e.g., "Hello, World!") in .rodata
 * |   - BSS (uninitialized) |  <- Uninitialized global/static variables (e.g., global_uninitialized)
 * |   - Initialized Data    |  <- Initialized global/static variables (e.g., global_initialized, static_global)
 * +-------------------------+
 * | Code Segment (.text)    |  <- Executable instructions (e.g., main, demonstrate_memory)
 * | (Read-only)             |
 * +-------------------------+
 * Low Memory Addresses
 *
 * Notes:
 * - Code Segment: Stores the program's executable code, typically at the lowest addresses.
 * - Data Segment: Includes initialized data (.data), uninitialized data (.bss), and read-only data (.rodata).
 * - Heap: Used for dynamic memory allocation, grows toward higher addresses.
 * - Stack: Used for local variables and function calls, starts at high addresses and grows downward.
 * - String literals are in .rodata (part of the data segment), not the code segment, despite being read-only.
 */


// Global variable (uninitialized) - stored in BSS (Block Started by Symbol) segment
// BSS is part of the data segment, used for uninitialized static/global variables
int global_uninitialized;

// Global variable (initialized) - stored in initialized data segment
// This is also part of the data segment, used for initialized static/global variables
int global_initialized = 100;

// Static global variable - stored in initialized data segment
// Static variables have file scope and persist for the program's lifetime
static int static_global = 200;

// Function to demonstrate stack and heap memory
void demonstrate_memory() {
    // Local variable - stored in stack segment
    // Stack is used for local variables and function call frames
    int local_var = 10;

    // Static local variable - stored in initialized data segment
    // Retains value between function calls, but scope is limited to this function
    static int static_local = 20;

    // Dynamic memory allocation - stored in heap segment
    // Heap is used for dynamically allocated memory via malloc/calloc
    int *heap_var = (int *)malloc(sizeof(int));
    *heap_var = 30;

    // Printing addresses and values to show where variables are stored
    printf("  Inside demonstrate_memory():\n");
    printf("  local_var (stack)          : value = %d, address = %p\n", local_var, (void *)&local_var);
    printf("  static_local (data segment): value = %d, address = %p\n", static_local, (void *)&static_local);
    printf("  heap_var (heap)            : value = %d, address = %p\n", *heap_var, (void *)heap_var);

    // Free heap memory to prevent memory leak
    free(heap_var);
}

int main() {
    // Local variable in main - stored in stack segment
    int main_local = 50;

    // String literal - stored in read-only part of data segment (.rodata)
    // String literals are typically stored in a read-only memory area
    char *string_literal = "Hello, World!";

    // Printing addresses and values to show memory segments
    printf("  In main():\n");
    printf("  main_local (stack)                : value = %d, address = %p\n", main_local, (void *)&main_local);
    printf("  global_uninitialized (BSS)        : value = %d, address = %p\n", global_uninitialized, (void *)&global_uninitialized);
    printf("  global_initialized (data segment) : value = %d, address = %p\n", global_initialized, (void *)&global_initialized);
    printf("  static_global (data segment)      : value = %d, address = %p\n", static_global, (void *)&static_global);
    printf("  string_literal (code segment)     : value = %s, address = %p\n", string_literal, (void *)string_literal);

    // Call function to demonstrate stack and heap
    demonstrate_memory();

    // Code itself (e.g., this main function) is stored in the code/text segment
    // The code segment contains the executable instructions of the program
    printf("\nFunction demonstrate_memory (code segment): address = %p", (void *)demonstrate_memory);
    printf("\nFunction main (code segment)              : address = %p\n", (void *)main);

    return 0;
}
/*
📤 Sample Output:

  In main():
  main_local (stack)                : value = 50, address = 0061FF18
  global_uninitialized (BSS)        : value = 0, address = 00407070
  global_initialized (data segment) : value = 100, address = 00404004
  static_global (data segment)      : value = 200, address = 00404008
  string_literal (code segment)     : value = Hello, World!, address = 00405135
  Inside demonstrate_memory():
  local_var (stack)          : value = 10, address = 0061FEE8
  static_local (data segment): value = 20, address = 0040400C
  heap_var (heap)            : value = 30, address = 00922EA8

Function demonstrate_memory (code segment): address = 00401460
Function main (code segment)              : address = 004014F2

*/

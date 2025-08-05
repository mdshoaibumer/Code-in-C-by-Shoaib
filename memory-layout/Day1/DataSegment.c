#include <stdio.h>

// Global variables
int global_initialized = 10;        // Initialized Data (read-write)
int global_uninitialized;          // BSS (uninitialized, set to 0)
static int static_initialized = 20; // Initialized Data (read-write)
static int static_uninitialized;    // BSS (uninitialized, set to 0)
const int global_const = 30;       // Initialized Data (read-only, e.g., .rodata)

int main() {
    // Print values and addresses of global and static variables
    printf("Global initialized  : %d, Address: %p\n", global_initialized, (void*)&global_initialized);
    printf("Global uninitialized: %d, Address: %p\n", global_uninitialized, (void*)&global_uninitialized);
    printf("Static initialized  : %d, Address: %p\n", static_initialized, (void*)&static_initialized);
    printf("Static uninitialized: %d, Address: %p\n", static_uninitialized, (void*)&static_uninitialized);
    printf("Global const        : %d, Address: %p\n", global_const, (void*)&global_const);
    return 0;
}
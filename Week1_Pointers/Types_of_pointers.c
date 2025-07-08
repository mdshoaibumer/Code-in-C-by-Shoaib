#include <stdio.h>
#include <stdlib.h>

void greet() {
    printf("Hello from function pointer!\n");
}

struct Point {
    int x, y;
};

int main() {
    // 1. NULL Pointer
    int *null_pointer = NULL;
    // A pointer initialized to NULL, indicating it doesn't point to any valid memory location.

    // 2. Void Pointer
    void *void_pointer;
    // A generic pointer that can point to any data type, but cannot be dereferenced directly without casting.

    // 3. Wild Pointer
    int *wild_pointer;
    // A pointer that is declared but not initialized. It may point to an arbitrary memory location (undefined behavior).

    // 4. Dangling Pointer
    int *dangling_pointer = (int *)malloc(sizeof(int));
    free(dangling_pointer);
    // After freeing, dangling_pointer becomes a dangling pointer — it points to deallocated memory.

    // 5. Double Pointer
    int value = 10;
    int *ptr1 = &value;
    int **ptr2 = &ptr1;
    // A pointer to another pointer. Useful in dynamic memory allocation and passing pointers to functions.

    // 6. Function Pointer
    void (*func_ptr)() = greet;
    func_ptr();
    // A pointer that stores the address of a function and can be used to call it.

    // 7. Constant Pointer
    int a = 5;
    int *const const_ptr = &a;
    // A constant pointer: the address it holds cannot be changed, but the value at that address can be modified.

    // 8. Pointer to Constant
    const int b = 15;
    const int *ptr_to_const = &b;
    // A pointer to a constant: the value it points to cannot be changed through the pointer.

    // 9. Constant Pointer to Constant
    const int c = 25;
    const int *const const_ptr_to_const = &c;
    // A constant pointer to a constant: neither the address nor the value can be changed.

    // 10. Array of Pointers
    int x = 1, y = 2, z = 3;
    int *arr_of_ptrs[] = {&x, &y, &z};
    // An array where each element is a pointer to an integer.

    // 11. Pointer to Array
    int arr[5] = {10, 20, 30, 40, 50};
    int (*ptr_to_array)[5] = &arr;
    // A pointer that points to an entire array of 5 integers.

    // 12. Pointer to Structure
    struct Point p = {100, 200};
    struct Point *ptr_to_struct = &p;
    // A pointer that points to a structure. Common in dynamic data structures.

    return 0;
}

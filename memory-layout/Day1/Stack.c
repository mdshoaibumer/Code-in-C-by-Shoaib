#include <stdio.h>

void myFunction(int param) {
    int local_var = 20;          // Local variable on Stack
    const int local_const = 30;  // Local const on Stack
    printf("Local variable in myFunction: %d, Address: %p\n", local_var, (void*)&local_var);
    printf("Local const                 : %d, Address: %p\n", local_const, (void*)&local_const);
    printf("Parameter                   : %d, Address: %p\n", param, (void*)&param);
}

int main() {
    int main_local = 10;  // Local variable on Stack
    printf("Local variable in main      : %d, Address: %p\n", main_local, (void*)&main_local);
    myFunction(main_local);
    return 0;
}
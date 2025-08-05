#include <stdio.h>

// A function whose instructions are stored in the Text Segment
void myFunction() {
    printf("Hello from myFunction\n");
}

int main() {
    // Print the address of myFunction (Text Segment)
    printf("Address of myFunction: %p\n", (void*)myFunction);
    myFunction();
    return 0;
}
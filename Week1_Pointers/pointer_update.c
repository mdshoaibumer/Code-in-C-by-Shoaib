#include <stdio.h>
#include <stdlib.h>

int main(){
    int num = 66;
    int *ptr = &num;

    printf("Original Value of num : %d\n", num);
    printf("Original address of ptr : %p\n", ptr);

    printf("-----After the update of integer -----\n");
    num = 66 * 100;
    printf("Updated Value of num : %d\n", num);
    printf("Updated address of ptr : %p\n", ptr);

    printf("-----After the update of pointer -----\n");
    *ptr+=*ptr**ptr;
    printf("Updated Value of num : %d\n", num);
    printf("Updated address of ptr : %p\n", ptr);
    return EXIT_SUCCESS;
}
#include <stdio.h>
#include <stdlib.h>

int main(){
    char ch = 'A';
    int a = 10;
    float flt_num = 23.56;
    double dbl_num = 88.0987;

    printf("Address of char ch           : %p\n", &ch);
    printf("Address of int a             : %p\n", &a);
    printf("Address of float flt_num is  : %p\n", &flt_num);
    printf("Address of double dbl_num is : %p\n", &dbl_num);
    printf("\n");

    return EXIT_SUCCESS;
}
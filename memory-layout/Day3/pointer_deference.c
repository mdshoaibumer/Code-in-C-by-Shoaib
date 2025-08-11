#include <stdio.h>
#include <stdlib.h>

int main(){

    char ch         = 'A';
    int a           = 10;
    float flt_num   = 23.56;
    double dbl_num  = 88.0987;

    printf("-----Address of variables using reference operator-----\n");
    printf("Address of char ch           : %p\n", &ch);
    printf("Address of int a             : %p\n", &a);
    printf("Address of float flt_num is  : %p\n", &flt_num);
    printf("Address of double dbl_num is : %p\n", &dbl_num);

    char *ptrch         = &ch;
    int *ptra           = &a;
    float *ptrflt_num   = &flt_num;
    double *ptrdbl_num  = &dbl_num;

    printf("-----Address of variables using pointers-----\n");
    printf("Address of char ch           : %p\n", ptrch);
    printf("Address of int a             : %p\n", ptra);
    printf("Address of float flt_num is  : %p\n", ptrflt_num);
    printf("Address of double dbl_num is : %p\n", ptrdbl_num);

    printf("-----Value of variables using pointers-----\n");
    printf("Value of char ch           : %c\n", *ptrch);
    printf("Value of int a             : %d\n", *ptra);
    printf("Value of float flt_num is  : %f\n", *ptrflt_num);
    printf("Value of double dbl_num is : %lf\n", *ptrdbl_num);

    return EXIT_SUCCESS;
}
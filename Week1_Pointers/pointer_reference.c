#include <stdio.h>

int main(){

    int a =20;
    int *ptra = &a;


    printf("-----Address-----\n");
    printf("Address of int a %p\n", &a);
    printf("Address of int ptra %p\n", ptra);

    printf("-----Value-----\n");
    printf("Value of int a %d\n", a);
    printf("Value of int *ptra %d\n", *ptra);

    return 0;

}
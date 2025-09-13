#include <stdio.h>
#include <stdlib.h>

void temp(int i) {
    int a[2];
    int b[3];
    int *c;
    int *d;

    c = (int *)malloc(sizeof(int) * 4);
    d = (int *)malloc(sizeof(int) * 5);

    printf("Addresses of arrays:\n");
    printf("a (stack, 2 ints) : %p\n", (void*)a);
    printf("b (stack, 3 ints) : %p\n", (void*)b);
    printf("c (heap, 4 ints)  : %p\n", (void*)c);
    printf("d (heap, 5 ints)  : %p\n", (void*)d);

    free(c);
    free(d);

    return;
}

int main(void) {
    temp(0);
    return 0;
}

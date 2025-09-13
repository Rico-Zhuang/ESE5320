#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(void) {
    int top = 20;
    int *p_top = &top;
    int *h50 = malloc(sizeof *h50); *h50 = 50;
    int *h5  = malloc(sizeof *h5 ); *h5  = 5;
    int *h6  = malloc(sizeof *h6 ); *h6  = 6;
    int *h7  = malloc(sizeof *h7 ); *h7  = 7;

    int *p_h50 = h50;
    int *p_h5  = h5;

    printf("Stack:\n");
    printf("%11p  %14d\n",   (void*)&top, top);
    printf("%11p  %14p\n", (void*)&p_top, (void*)p_top);
    printf("%11p  %14p\n", (void*)&p_h50, (void*)p_h50);
    printf("%11p  %14p\n", (void*)&p_h5,  (void*)p_h5);

    printf("\nHeap:\n");
    printf("h50: %p = %d\n", (void*)h50, *h50);
    printf(" h5: %p = %d\n", (void*)h5,  *h5 );
    printf(" h6: %p = %d\n", (void*)h6,  *h6 );
    printf(" h7: %p = %d\n", (void*)h7,  *h7 );

    free(h50); free(h5); free(h6); free(h7);
    return 0;
}
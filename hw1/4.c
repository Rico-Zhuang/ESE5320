#include <stdio.h>

int main(void) {
    double a[] = {3.14, 2.71};
    unsigned char *p = (unsigned char *)a;
    for (size_t i = 0; i < sizeof(a); i++) {
        printf("Byte %2zu: 0x%02X\n", i, p[i]);
    }
    return 0;
}

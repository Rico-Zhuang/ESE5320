#include <stdio.h>
#include <limits.h>

int main() {
    printf("Max unsigned int: %u\n", UINT_MAX);
    printf("Binary: ");
    for (int i = sizeof(UINT_MAX) * 8 - 1; i >= 0; i--) {
        printf("%u", (UINT_MAX >> i) & 1);
    }
    printf("\n");
    return 0;
}
#include <stdio.h>

int main(void) {
    int a[2][4] = { {10, 20, 30, 40}, {50, 60, 70, 80} };

    int *row[2] = { a[0], a[1] };

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("row[%d][%d] = %d\n", i, j, row[i][j]);
        }
    }

    return 0;
}

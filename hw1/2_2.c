#include <stdio.h>

int main(void) {
    int a[2][4] = { {10, 20, 30, 40}, {50, 60, 70, 80} };
    int *row0 = a[0];
    int *row1 = a[1];
    int *rows[2] = { row0, row1 };
    int **pp = rows;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("pp[%d][%d] = %d\n", i, j, pp[i][j]);
        }
    }
    return 0;
}

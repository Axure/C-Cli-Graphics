#include "../../lib/graphics_lib.h"
#include "../../lib/utils.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>

const char * UR = "┐";
const char * R = "┤";
const char * L = "├";
const char * U = "┬";
const char * D = "┴";
const char * DR = "┘";
const char * UL = "┌";
const char * DL = "└";
const char * C = "┼";

const char * horse = "*";




int main(int argc, char **argv) {
    setlocale(LC_CTYPE, "chs");

    int n, m;
    n = string_to_number(argv[1]);
    m = string_to_number(argv[2]);

    printf("The chessboard is %d times %d.\n", n, m);

    printf("%s", UL);
    for (int i = 1; i < m - 1; ++i) {
        printf("%s", U);
    }
    printf("%s\n", UR);

    for (int j = 1; j < n - 1; ++j) {
        printf("%s", L);
        for (int i = 1; i < m - 1; ++i) {
            printf("%s", C);
        }
        printf("%s\n", R);
    }
    // The crucial obstacle to ASCII board is that the characters are not square. Instead, they are tall.
    printf("%s", DL);
    for (int i = 1; i < m - 1; ++i) {
        printf("%s", D);
    }
    printf("%s\n", DR);

    return 0;
}
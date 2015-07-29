#include "../../lib/graphics_lib.h"
#include "../../lib/utils.h"
#include <stdio.h>
#include <wchar.h>

const wchar_t UR = L'┐';
const wchar_t R = L'┤';
const wchar_t L = L'├';
const wchar_t U = L'┬';
const wchar_t D = L'┴';
const wchar_t DR = L'┘';
const wchar_t UL = L'┌';
const wchar_t DL = L'└';
const wchar_t C = L'┼';

const wchar_t horse = L'*';




int main(int argc, char **argv) {
    int n, m;
    n = string_to_number(argv[1]);
    m = string_to_number(argv[2]);

    printf("The chessboard is %d times %d.\n", n, m);

    wprintf(L"%lc", R);

    return 0;
}
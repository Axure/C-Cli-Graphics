#include "../../lib/graphics_lib.h"
#include "../../lib/utils.h"
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdbool.h>

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

#define BOARD_SIZE 10;

// Strictly follow the MVC pattern.
// Design properly from the very beginning.
// One session is exactly just inside the function?
// No global variables? Or all global?
// For the sake of memory management, all globa?

void horse_exhaustion(int chess_board[10][10], int width, int height);

int main(int argc, char **argv) {
    setlocale(LC_CTYPE, "chs");

    bool horse_board[BOARD_SIZE][BOARD_SIZE];

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

    horse_exhaustion(horse_board, m, n);

    return 0;
}

void horse_exhaustion(int chess_board[10][10], int width, int height)
{
    /*!
     * Init the model.
     */
    for(int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j) {
            chess_board[i][j] = false;
        }
    }



    /*!
     * Init the view.
     */


    /*!
     * Exhaustion
     */
    while()
    {
        /*!
         * Pass to the view
         */
    }
}
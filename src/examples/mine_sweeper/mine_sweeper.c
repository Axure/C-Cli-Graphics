#include "../../lib/graphics_lib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// We should follow the MVC pattern.


void mine_sweeper_init();

void mine_sweeper_recount(enum MineSweeperModelState model[SIZE][SIZE], int count[SIZE][SIZE], int size);

void mine_sweeper_debug_plot(enum MineSweeperModelState model[SIZE][SIZE], int count[SIZE][SIZE], int size);

void mine_sweeper_plot(enum MineSweeperModelState model[SIZE][SIZE], bool revealed[SIZE][SIZE], int count[SIZE][SIZE],
                       struct int_coordinate pointer,
                       int size);

void mine_sweeper_update_pointer(int x, int y, struct int_coordinate *p_pointer);

int main(int argc, char **argv) {
    log_file = fopen("./mine_sweeper.log", "w+");
    init();
    init_buffer();
    refresh();
    struct real_coordinate origin = {-4.0, -4.0};
//    plot(test, origin, 8, 5);

    get_screen_size();
    mine_sweeper_init();
    refresh();
//    plot(test, origin, 8, 5);

    // ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
//    while (1) {
//    	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
//    	if (old_w.ws_col != w.ws_col || old_w.ws_row != w.ws_row) {
//    		// system("clear");
//    		// printf("Width %d, Height %d\n", w.ws_col, w.ws_row); // You should output to the buffer now;
//    		old_w = w;
//    		buffer_changed = 1;
//    	}
//    	if (buffer_changed == 1) {
//    		refresh();
//    		// printf("fuck\n");
//    		buffer_changed = 0;
//    	}
//
//    }






    /*!
     * Main body
     */
    while (true) {

    }


    return 0;  // make sure your main returns int
}

// Currently the model is still coupled.
/*!
 * Initialize the model
 * \sa mine_sweeper_recount
 * \sa mine_sweeper_plot
 */
void mine_sweeper_init() {
    enum MineSweeperModelState mine_sweeper_model_state[SIZE][SIZE];
    int mine_sweeper_model_count[SIZE][SIZE];
    bool mine_sweeper_model_revealed[SIZE][SIZE];

    struct int_coordinate mine_sweeper_pointer = {0, 0};

    srand(time(NULL));

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if ((rand() % 6) == 0) {
                mine_sweeper_model_state[i][j] = Bomb;
            } else {
                mine_sweeper_model_state[i][j] = Empty;
            }
            mine_sweeper_model_count[i][j] = 0;
            mine_sweeper_model_revealed[i][j] = false;
        }
    }

    mine_sweeper_recount(mine_sweeper_model_state, mine_sweeper_model_count, SIZE);
    mine_sweeper_plot(mine_sweeper_model_state, mine_sweeper_model_revealed, mine_sweeper_model_count,
                      mine_sweeper_pointer, SIZE);

    for (int k = 0; k < SIZE; ++k) {
        for (int i = 0; i < SIZE; ++i) {
            fprintf(log_file, "fucked %d", mine_sweeper_model_state[k][i]);
        }
        fprintf(log_file, "\n");
    }
    // `buffer` is a global thing.
    char command;
    while ((command = getchar()) != EOF) {
        printf("The command is %c.\n", command);
        switch (command) {
            case 'a':
                mine_sweeper_update_pointer(mine_sweeper_pointer.x, mine_sweeper_pointer.y - 1, &mine_sweeper_pointer);
                break;
            case 's':
                mine_sweeper_update_pointer(mine_sweeper_pointer.x + 1, mine_sweeper_pointer.y, &mine_sweeper_pointer);
                break;
            case 'd':
                mine_sweeper_update_pointer(mine_sweeper_pointer.x, mine_sweeper_pointer.y + 1, &mine_sweeper_pointer);
                break;
            case 'w':
                mine_sweeper_update_pointer(mine_sweeper_pointer.x - 1, mine_sweeper_pointer.y, &mine_sweeper_pointer);
                break;
            case 'r':
                mine_sweeper_model_revealed[mine_sweeper_pointer.x][mine_sweeper_pointer.y] = true;
            default:
                break;
        }
        mine_sweeper_plot(mine_sweeper_model_state, mine_sweeper_model_revealed, mine_sweeper_model_count,
                          mine_sweeper_pointer, SIZE);
//        printf("%c\n", command);
    }
//    while (true) {
////        getchar();
//
//
////        mine_sweeper_plot(mine_sweeper_model_state, mine_sweeper_model_revealed, mine_sweeper_model_count,
////                          mine_sweeper_pointer, SIZE);
//    }
}

/*!
 * Recalculate the counts of/in the model
 * \param model The model array
 * \param count The count array
 * \param size The size of the model
 */
void mine_sweeper_recount(enum MineSweeperModelState model[SIZE][SIZE], int count[SIZE][SIZE], int size) {
    for (int i = 1; i < size - 1; ++i) {
        for (int j = 1; j < size - 1; ++j) {
            if (model[i][j] == Bomb) {
                count[i - 1][j - 1]++;
                count[i - 1][j]++;
                count[i - 1][j + 1]++;
                count[i][j - 1]++;
                count[i][j + 1]++;
                count[i + 1][j - 1]++;
                count[i + 1][j]++;
                count[i + 1][j + 1]++;
            }
        }
    }

    for (int i = 1; i < size - 1; i++) {
        if (model[i][0] == Bomb) {
            count[i - 1][0]++;
            count[i + 1][0]++;
            count[i - 1][1]++;
            count[i][1]++;
            count[i + 1][1]++;
        }
    }

    for (int i = 1; i < size - 1; i++) {
        if (model[i][size - 1] == Bomb) {
            count[i - 1][size - 1]++;
            count[i + 1][size - 1]++;
            count[i - 1][size - 2]++;
            count[i][size - 2]++;
            count[i + 1][size - 2]++;
        }
    }

    for (int j = 1; j < size - 1; j++) {
        if (model[0][j] == Bomb) {
            count[0][j - 1]++;
            count[0][j + 1]++;
            count[1][j - 1]++;
            count[1][j]++;
            count[1][j + 1]++;
        }
    }

    for (int j = 1; j < size - 1; j++) {
        if (model[size - 1][j] == Bomb) {
            count[size - 1][j - 1]++;
            count[size - 1][j + 1]++;
            count[size - 2][j - 1]++;
            count[size - 2][j]++;
            count[size - 2][j + 1]++;
        }
    }

    if (model[0][0] == Bomb) {
        count[0][1]++;
        count[1][0]++;
        count[1][1]++;
    }
    if (model[0][size - 1] == Bomb) {
        count[0][size - 2]++;
        count[1][size - 1]++;
        count[1][size - 1]++;
    }
    if (model[size - 1][0] == Bomb) {
        count[size - 2][0]++;
        count[size - 1][1]++;
        count[size - 2][1]++;
    }
    if (model[size - 1][size - 1] == Bomb) {
        count[size - 2][size - 1]++;
        count[size - 1][size - 2]++;
        count[size - 2][size - 2]++;
    }
}

/*!
 * Directly draw the board from the model. Simple MVC.
 * \param model the model
 * \param count
 * \param size
 */
void mine_sweeper_debug_plot(enum MineSweeperModelState model[SIZE][SIZE], int count[SIZE][SIZE], int size) {
    int origin_x = 5;
    int origin_y = 5;

    // Maybe we need some diff techniques on the buffer change redraw functionality/sub-procedure.

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (model[i][j] == Bomb) {
                buffer[i * 2 + origin_x][j * 2 + origin_y].character = '*';
            } else {
                buffer[i * 2 + origin_x][j * 2 + origin_y].character = (char) (count[i][j] == 0) ? '0' : (char) ('0' +
                                                                                                                 count[i][j]); //TODO: clear this warning
            }
        }
    }

    refresh();
}

void mine_sweeper_update_pointer(int x, int y, struct int_coordinate *p_pointer) {
    int origin_x = 5;
    int origin_y = 5;
    buffer[p_pointer->x * 2 + origin_x - 1][p_pointer->y * 2 + origin_y].character = ' ';
    buffer[p_pointer->x * 2 + origin_x + 1][p_pointer->y * 2 + origin_y].character = ' ';
    buffer[p_pointer->x * 2 + origin_x][p_pointer->y * 2 + origin_y - 1].character = ' ';
    buffer[p_pointer->x * 2 + origin_x][p_pointer->y * 2 + origin_y + 1].character = ' ';

    p_pointer->x = x;
    p_pointer->y = y;
}

void mine_sweeper_plot(enum MineSweeperModelState model[SIZE][SIZE], bool revealed[SIZE][SIZE], int count[SIZE][SIZE],
                       struct int_coordinate pointer,
                       int size) {
    int origin_x = 5;
    int origin_y = 5;

    // Maybe we need some diff techniques on the buffer change redraw functionality/sub-procedure.

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (revealed[i][j]) {
                if (model[i][j] == Bomb) {
                    printf("Bomb!\n");
                    buffer[i * 2 + origin_x][j * 2 + origin_y].character = '*';
                } else {
                    buffer[i * 2 + origin_x][j * 2 + origin_y].character = (char) (count[i][j] == 0) ? '0' : (char) (
                            '0' + count[i][j]); //TODO: clear this warning
                }
            } else {
                buffer[i * 2 + origin_x][j * 2 + origin_y].character = '+';
            }

        }
    }

    buffer[pointer.x * 2 + origin_x - 1][pointer.y * 2 + origin_y].character = '-';
    buffer[pointer.x * 2 + origin_x + 1][pointer.y * 2 + origin_y].character = '-';
    buffer[pointer.x * 2 + origin_x][pointer.y * 2 + origin_y - 1].character = '|';
    buffer[pointer.x * 2 + origin_x][pointer.y * 2 + origin_y + 1].character = '|';

    refresh();
}
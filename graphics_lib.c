#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <time.h>

#include <time.h>

struct winsize old_w;
struct winsize w;
// char buffer[500][500]; // Change it to dynamic allocation according to the window size in the future...
int buffer_changed = 0;

FILE *log_file;

//const int SIZE = 8;
#define SIZE 8

typedef double(*two_dim_implicit)(double, double);

struct int_coordinate {
    int x, y;
};
struct real_coordinate {
    double x, y;
};


struct buffer_point {
    char character;
    int r, g, b; // 216 color
    int br, bg, bb;
};
struct buffer_point buffer[500][500];

enum MineSweeperModelState { Bomb, Empty };

void plot(two_dim_implicit func, struct real_coordinate origin, double scope, double tolerance);

void init();

void init_buffer();

void refresh();

static struct int_coordinate get_screen_size();

void set_foreground(struct buffer_point *p_buffer_point, int r, int g, int b);

void set_background(struct buffer_point *p_buffer_point, int r, int g, int b);

void mine_sweeper_init();
void mine_sweeper_recount(enum MineSweeperModelState model[SIZE][SIZE], int count[SIZE][SIZE], int size);
void mine_sweeper_plot(enum MineSweeperModelState model[SIZE][SIZE], int count[SIZE][SIZE], int size);


static inline double abs_d(double x) {
    return (x >= 0) ? x : -x;
}

static inline struct int_coordinate get_screen_size() {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    struct int_coordinate screen = {(int) w.ws_col, (int) w.ws_row};
    return screen;
}
// TODO: implement a coordinate converter that allows us to set arbitrary direction of the axises?



void plot(two_dim_implicit func, struct real_coordinate origin, double horizontal_scope, double tolerance) {
    struct int_coordinate screen = get_screen_size();
    double unit = horizontal_scope / screen.y;
    struct real_coordinate plane;
    double func_result;
    for (int j = 0; j < screen.x; ++j) {
        for (int i = 0; i < screen.y; ++i) {
            // Calculate real coordinate
            plane.x = origin.x + unit * i;
            plane.y = origin.y + unit * j / 2.0;
            func_result = abs_d(func(plane.x, plane.y));
            fprintf(log_file, "coordinate on screen: %d, %d, real coordinate %lf, %lf, value %lf\n", i, j, plane.x,
                    plane.y, (func(plane.x, plane.y)));

            if (func_result <= tolerance) {

                buffer[i][j].character = "@%#*+=-:."[(int) (func_result / tolerance * 9.0)];
            }
            else {
                buffer[i][j].character = ' ';
            }
        }
    }

    refresh();
}

void init() {
    get_screen_size();
    old_w.ws_row = 0;
    old_w.ws_col = 0;
}

void init_buffer() {
    srand(time(NULL));
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 500; ++j) {
//			buffer[i][j].character = 65;
//            buffer[i][j] = {' ', 0, 0, 0, 5, 5, 5};
//			buffer[i][j].r = rand() % 6;
//			buffer[i][j].g = rand() % 6;
//			buffer[i][j].b = rand() % 6;
//			buffer[i][j].br = rand() % 6;
//			buffer[i][j].bg = rand() % 6;
//			buffer[i][j].bb = rand() % 6;

            buffer[i][j].character = ' ';
//            buffer[i][j] = {' ', 0, 0, 0, 5, 5, 5};
            buffer[i][j].r = 5;
            buffer[i][j].g = 5;
            buffer[i][j].b = 5;
            buffer[i][j].br = 0;
            buffer[i][j].bg = 0;
            buffer[i][j].bb = 0;
        }
    }
}

void refresh() {
    system("clear");
    fprintf(log_file, "The system screen is %d * %d\n", w.ws_row, w.ws_col);
    int i;
    for (i = 0; i < w.ws_row - 1; ++i) {
        for (int j = 0; j < w.ws_col; ++j) {
            fprintf(log_file, "%c", buffer[i][j].character);
            printf("\e[38;5;%dm\e[48;5;%dm%c\e[0m", buffer[i][j].b * 36 + buffer[i][j].g * 6 + buffer[i][j].r + 16,
                   buffer[i][j].bb * 36 + buffer[i][j].bg * 6 + buffer[i][j].br + 16, buffer[i][j].character);
            // printf("3");
        }
        fprintf(log_file, "\n");
        printf("\n");
    }
    for (int j = 0; j < w.ws_col; ++j) {
        fprintf(log_file, "%c", buffer[i][j].character);
        printf("\e[38;5;%dm\e[48;5;%dm%c\e[0m", buffer[i][j].b * 36 + buffer[i][j].g * 6 + buffer[i][j].r + 16,
               buffer[i][j].bb * 36 + buffer[i][j].bg * 6 + buffer[i][j].br + 16, buffer[i][j].character);
        // printf("%c", buffer[i][j]);
        // printf("4");
    }
    fflush(stdout);
    // printf("Fuck you");
}

void set_foreground(struct buffer_point *p_buffer_point, int r, int g, int b) {
    p_buffer_point->r = r;
    p_buffer_point->g = g;
    p_buffer_point->b = b;
}

void set_background(struct buffer_point *p_buffer_point, int r, int g, int b) {
    p_buffer_point->br = r;
    p_buffer_point->bg = g;
    p_buffer_point->bb = b;
}

void draw_circle() {

}

// void 

double test(double x, double y) {
    return x * x + y * y - 9;
}

int main(int argc, char **argv) {
    log_file = fopen("./log_file.txt", "w+");
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
    getchar();
    return 0;  // make sure your main returns int
}



void mine_sweeper_init() {
    enum MineSweeperModelState mine_sweeper_model_state[SIZE][SIZE];
    int mine_sweeper_model_count[SIZE][SIZE];

    srand(time(NULL));

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if ((rand() % 6) == 0) {
                mine_sweeper_model_state[i][j] = Bomb;
            } else {
                mine_sweeper_model_state[i][j] = Empty;
            }
            mine_sweeper_model_count[i][j] = 0;
        }
    }

    mine_sweeper_recount(mine_sweeper_model_state, mine_sweeper_model_count, SIZE);
    mine_sweeper_plot(mine_sweeper_model_state, mine_sweeper_model_count, SIZE);

    for (int k = 0; k < SIZE; ++k) {
        for (int i = 0; i < SIZE; ++i) {
            fprintf(log_file, "fucked %d", mine_sweeper_model_state[k][i]);
        }
        fprintf(log_file, "\n");
    }
}

void mine_sweeper_recount(enum MineSweeperModelState model[SIZE][SIZE], int count[SIZE][SIZE], int size) {
    for (int i = 1; i < size - 1; ++i) {
        for (int j = 1; j < size - 1; ++j) {
            if (model[i][j] == Bomb)
            {
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

    for (int i = 1; i < size - 1; i++)
    {
        if (model[i][0] == Bomb)
        {
            count[i - 1][0]++;
            count[i + 1][0]++;
            count[i - 1][1]++;
            count[i][1]++;
            count[i + 1][1]++;
        }
    }

    for (int i = 1; i < size - 1; i++)
    {
        if (model[i][size - 1] == Bomb)
        {
            count[i - 1][size - 1]++;
            count[i + 1][size - 1]++;
            count[i - 1][size - 2]++;
            count[i][size - 2]++;
            count[i + 1][size - 2]++;
        }
    }

    for (int j = 1; j < size - 1; j++)
    {
        if (model[0][j] == Bomb)
        {
            count[0][j - 1]++;
            count[0][j + 1]++;
            count[1][j - 1]++;
            count[1][j]++;
            count[1][j + 1]++;
        }
    }

    for (int j = 1; j < size - 1; j++)
    {
        if (model[size - 1][j] == Bomb)
        {
            count[size - 1][j - 1]++;
            count[size - 1][j + 1]++;
            count[size - 2][j - 1]++;
            count[size - 2][j]++;
            count[size - 2][j + 1]++;
        }
    }

    if (model[0][0] == Bomb)
    {
        count[0][1]++;
        count[1][0]++;
        count[1][1]++;
    }
    if (model[0][size - 1] == Bomb)
    {
        count[0][size - 2]++;
        count[1][size - 1]++;
        count[1][size - 1]++;
    }
    if (model[size - 1][0] == Bomb)
    {
        count[size - 2][0]++;
        count[size - 1][1]++;
        count[size - 2][1]++;
    }
    if (model[size - 1][size - 1] == Bomb)
    {
        count[size - 2][size - 1]++;
        count[size - 1][size - 2]++;
        count[size - 2][size - 2]++;
    }
}

void mine_sweeper_plot(enum MineSweeperModelState model[SIZE][SIZE], int count[SIZE][SIZE], int size)
{
    int origin_x = 5;
    int origin_y = 5;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (model[i][j] == Bomb)
            {
                buffer[i + origin_x][j + origin_y].character = '*';
            } else {
                buffer[i + origin_x][j + origin_y].character = (count[i][j] == 0) ? ' ' : (char)('0' + count[i][j]);
            }
        }
    }
}
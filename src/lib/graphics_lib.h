#ifndef GRAPHICS_LIB_
#define GRAPHICS_LIB_

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

struct winsize old_w;
struct winsize w;
// char buffer[500][500]; // Change it to dynamic allocation according to the window size in the future...
extern int buffer_changed;

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

#endif
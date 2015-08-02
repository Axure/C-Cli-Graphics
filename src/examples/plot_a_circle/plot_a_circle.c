#include "../../lib/graphics_lib.h"
#include "../../lib/math_plot.h"

double test(double x, double y) {
    return x * x + y * y - 9;
}


int main() {
    log_file = fopen("./log_file.txt", "w+");
    init();
    init_buffer();
    refresh();
    struct real_coordinate origin = {-4.0, -4.0};
    plot(test, origin, 8, 5);

    get_screen_size();
    mine_sweeper_init();
    refresh();
    plot(test, origin, 8, 5);

    ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
    while (1) {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        if (old_w.ws_col != w.ws_col || old_w.ws_row != w.ws_row) {
            // system("clear");
            // printf("Width %d, Height %d\n", w.ws_col, w.ws_row); // You should output to the buffer now;
            old_w = w;
            buffer_changed = 1;
        }
        if (buffer_changed == 1) {
            refresh();
            // printf("fuck\n");
            buffer_changed = 0;
        }

    }
    getchar();
}
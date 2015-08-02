#include "graphics_lib.h"

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
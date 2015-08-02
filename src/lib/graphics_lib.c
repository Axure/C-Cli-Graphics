#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <time.h>


#include "graphics_lib.h"

int buffer_changed = 0;


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

/*!
 * Refreshing the buffer
 */
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

/*!
 * Setting the foreground
 * \param p_buffer_point pointer to the buffer point.
 * \param r the red value
 * \param g the green value
 * \param b the blue value
 * \sa set_background()
 */
void set_foreground(struct buffer_point *p_buffer_point, int r, int g, int b) {
    p_buffer_point->r = r;
    p_buffer_point->g = g;
    p_buffer_point->b = b;
}

/*!
 * Setting the background
 * \param p_buffer_point pointer to the buffer point.
 * \param r the red value
 * \param g the green value
 * \param b the blue value
 * \sa set_foreground()
 */
void set_background(struct buffer_point *p_buffer_point, int r, int g, int b) {
    p_buffer_point->br = r;
    p_buffer_point->bg = g;
    p_buffer_point->bb = b;
}

void draw_circle() {

}

// void
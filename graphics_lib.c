#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include <time.h>

struct winsize old_w;
struct winsize w;
// char buffer[500][500]; // Change it to dynamic allocation according to the window size in the future...
int buffer_changed = 0;

FILE* log_file;

typedef double(*two_dim_implicit)(double, double);
struct int_coordinate
{
	int x, y;
};
struct real_coordinate
{
	double x, y;
};


struct buffer_point
{
	char character;
	int r, g, b; // 216 color
	int br, bg, bb;
};
struct buffer_point buffer[500][500];

void plot(two_dim_implicit func, struct real_coordinate origin, double scope, double tolerance);
void init();
void init_buffer();
void refresh();
static struct int_coordinate get_screen_size();
void set_foreground(struct buffer_point *p_buffer_point, int r, int g, int b);
void set_background(struct buffer_point *p_buffer_point, int r, int g, int b);


static inline double abs_d(double x)
{
    return (x >= 0) ? x : -x;
}

static inline struct int_coordinate get_screen_size()
{
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	struct int_coordinate screen = {(int)w.ws_col, (int)w.ws_row};
	return screen;
}
// TODO: implement a coordinate converter that allows us to set arbitrary direction of the axises?



void plot(two_dim_implicit func, struct real_coordinate origin, double horizontal_scope, double tolerance)
{
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
            fprintf(log_file, "coordinate on screen: %d, %d, real coordinate %lf, %lf, value %lf\n", i, j, plane.x, plane.y, (func(plane.x, plane.y)));

            if (func_result <= tolerance)
            {

                buffer[i][j].character = "@%#*+=-:."[(int)(func_result / tolerance * 9.0)];
            }
            else
            {
                buffer[i][j].character = ' ';
            }
        }
    }

    refresh();
}

void init() {
	old_w.ws_row = 0;
	old_w.ws_col = 0;
}

void init_buffer() {
	srand(time(NULL));
	for (int i = 0; i < 500; ++i)
	{
		for (int j = 0; j < 500; ++j)
		{
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
	int i;
	for (i = 0; i < w.ws_row - 1; ++i)
	{
		for (int j = 0; j < w.ws_col ; ++j)
		{
			printf("\e[38;5;%dm\e[48;5;%dm%c\e[0m",buffer[i][j].b * 36 + buffer[i][j].g * 6 + buffer[i][j].r + 16, buffer[i][j].bb * 36 + buffer[i][j].bg * 6 + buffer[i][j].br + 16, buffer[i][j].character);
			// printf("3");
		}
		printf("\n");
	}
	for (int j = 0; j < w.ws_col ; ++j)
	{
		printf("\e[38;5;%dm\e[48;5;%dm%c\e[0m",buffer[i][j].b * 36 + buffer[i][j].g * 6 + buffer[i][j].r + 16, buffer[i][j].bb * 36 + buffer[i][j].bg * 6 + buffer[i][j].br + 16, buffer[i][j].character);
		// printf("%c", buffer[i][j]);
		// printf("4");
	}
	fflush(stdout);
	// printf("Fuck you");
}

void set_foreground(struct buffer_point *p_buffer_point, int r, int g, int b)
{
	p_buffer_point->r = r;
	p_buffer_point->g = g;
	p_buffer_point->b = b;
}

void set_background(struct buffer_point *p_buffer_point, int r, int g, int b)
{
	p_buffer_point->br = r;
	p_buffer_point->bg = g;
	p_buffer_point->bb = b;
}

void draw_circle()
{

}

// void 

double test(double x, double y)
{
    return x * x + y * y - 9;
}

int main (int argc, char **argv)
{
    log_file = fopen("./log_file.txt", "w+");
	init();
    init_buffer();
    refresh();
    struct real_coordinate origin = {-4.0, -4.0};
    plot(test, origin, 8, 5);
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
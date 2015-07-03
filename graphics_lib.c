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

struct buffer_point
{
	char character;
	int r, g, b; // 216 color
	int br, bg, bb;
};
struct buffer_point buffer[500][500];


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
			buffer[i][j].character = 65;
			buffer[i][j].r = rand() % 6;
			buffer[i][j].g = rand() % 6;
			buffer[i][j].b = rand() % 6;
			buffer[i][j].br = rand() % 6;
			buffer[i][j].bg = rand() % 6;
			buffer[i][j].bb = rand() % 6;
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

int main (int argc, char **argv)
{
    
	init();
    init_buffer();
    refresh();
    // ioctl(STDERR_FILENO, TIOCGWINSZ, &w);
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
    
    return 0;  // make sure your main returns int
}
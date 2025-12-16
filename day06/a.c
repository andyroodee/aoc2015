#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define GRID_SIZE 1000

static const char *delim = " ,\n";
static char grid[GRID_SIZE][GRID_SIZE] = {0};
static int lights = 0;

typedef struct {
	int x_1, y_1, x_2, y_2;
} Rectangle;

static void parse_rectangle(char *x, Rectangle *r) {
	x = strtok(NULL, delim); r->x_1 = atoi(x);							
	x = strtok(NULL, delim); r->y_1 = atoi(x);

	// "through"
	x = strtok(NULL, delim);

	x = strtok(NULL, delim); r->x_2 = atoi(x);							
	x = strtok(NULL, delim); r->y_2 = atoi(x);
}

static void toggle(Rectangle r) {
	for (int y = r.y_1; y <= r.y_2; y++) {
		for (int x = r.x_1; x <= r.x_2; x++) {
			if (grid[y][x]) {
				grid[y][x] = 0;
				--lights;
			} else {
				grid[y][x] = 1;
				++lights;
			}			
		}
	}
}

static void set(Rectangle r, bool on) {
	for (int y = r.y_1; y <= r.y_2; y++) {
		for (int x = r.x_1; x <= r.x_2; x++) {
			if (on) {
				if (!grid[y][x]) {
					++lights;
				}
				grid[y][x] = 1;
			} else {
				if (grid[y][x]) {
					--lights;
				}
				grid[y][x] = 0;
			}	
		}
	}
}

void a() {
	FILE *in = fopen("input.txt", "r");
	char buffer[64] = {0};
	
	while (fgets(buffer, sizeof(buffer), in) != NULL) {
		char* x = strtok(buffer, delim);
		while (x != NULL) {
			Rectangle r;
			memset(&r, 0, sizeof(Rectangle));
			if (strcmp("toggle", x) == 0) {
				parse_rectangle(x, &r);
				toggle(r);		
			} else if (strcmp("on", x) == 0) {
				parse_rectangle(x, &r);
				set(r, true);
			} else if (strcmp("off", x) == 0) {
				parse_rectangle(x, &r);
				set(r, false);
			}
			x = strtok(NULL, delim);
		}
	}
	fclose(in);
	printf("%d\n", lights);
}

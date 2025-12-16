#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define GRID_SIZE 1000

static const char *delim = " ,\n";
static int grid[GRID_SIZE][GRID_SIZE] = {0};
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
			grid[y][x] += 2;
			lights += 2;
		}
	}
}

static void set(Rectangle r, bool on) {
	for (int y = r.y_1; y <= r.y_2; y++) {
		for (int x = r.x_1; x <= r.x_2; x++) {
			if (on) {
				++grid[y][x];
				++lights;
			} else {
				if (grid[y][x]) {
					--grid[y][x];
					--lights;
				}
			}	
		}
	}
}

void b() {
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

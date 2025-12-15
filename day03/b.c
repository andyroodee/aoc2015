#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 8192

typedef struct Location {
	int row;
	int col;
} Location;

static int loc_compare(const void *a_ptr, const void *b_ptr) {
	Location a = *((Location *)a_ptr);
	Location b = *((Location *)b_ptr);
	int r = a.row - b.row;
	if (r != 0) {
		return r;
	}
	return a.col - b.col;
}

static bool loc_equal(const Location *a, const Location *b) {
	return a->row == b->row && a->col == b->col;
}

static void visit(const char *buffer, Location *locations, int start) {
	int r = 0, c = 0, ind = 0;
	for (int i = start; i < SIZE; i += 2) {
		switch (buffer[i]) {
			case '>':
				c++;
			break;
			case '<':
				c--;
			break;
			case '^':
				r--;
			break;
			case 'v':
				r++;
			break;
			default:
				continue;
		}
		locations[i] = (Location){r, c};
	}
}

void b() {
	FILE *in = fopen("input.txt", "r");
	char buffer[SIZE+1] = {0};
	fgets(buffer, sizeof(buffer), in);
	fclose(in);

	Location locations[SIZE] = {0};
	visit(buffer, locations, 0);
	visit(buffer, locations, 1);
	qsort(locations, SIZE, sizeof(Location), loc_compare);
	Location x = locations[0];
	int visited = 1;
	for (int i = 1; i < SIZE; i++) {
		if (loc_equal(&x, &locations[i])) {
			continue;
		}
		visited++;
		x = locations[i];
	}
	printf("%d\n", visited);
}
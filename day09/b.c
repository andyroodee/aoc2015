#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define PLACES 8

static char *places[PLACES] = {0};
static int distances[PLACES][PLACES] = {0};
static int longest = 0;
static bool visited[PLACES];

static int get_place_id(const char *place) {
	int next_id = -1;
	for (int i = 0; i < PLACES; i++) {
		if (places[i] != NULL && strcmp(places[i], place) == 0) {
			return i;
		}
		if (next_id == -1 && places[i] == NULL) {
			next_id = i;
		}
	}
	size_t len = strlen(place) + 1;
	places[next_id] = malloc(len * sizeof(char));
	strcpy(places[next_id], place);
	return next_id;
}

static void tsp(int where, int d, int n) {
	if (n == PLACES - 1) {
		if (d > longest) {
			longest = d;
		}
		return;
	}
	visited[where] = true;
	for (int i = 0; i < PLACES; i++) {
		if (visited[i]) {
			continue;
		}
		visited[i] = true;
		tsp(i, d + distances[where][i], n+1);
		visited[i] = false;
	}
}

void b() {
	FILE *in = fopen("input.txt", "r");
	char buffer[64] = {0};
	char from[32] = {0};
	char to[32] = {0};

	while (fgets(buffer, sizeof(buffer), in) != NULL) {
		int distance = 0;
		sscanf(buffer, "%s to %s = %d", from, to, &distance);
		int from_id = get_place_id(from);
		int to_id = get_place_id(to);
		distances[from_id][to_id] = distance;
		distances[to_id][from_id] = distance;
	}
	fclose(in);
	for (int i = 0; i < PLACES; i++) {
		tsp(i, 0, 0);
		memset(visited, 0, sizeof(visited));
	}
	
	printf("%d\n", longest);
}

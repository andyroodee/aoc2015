#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void parseInts(int* values, char *s, const char *delim) {
	char* x = strtok(s, delim);
	while (x != NULL) {
		*values++ = atoi(x);
		x = strtok(NULL, delim);
	}
}

void b() {
	FILE *in = fopen("input.txt", "r");
	
	char buffer[128];
	int v[3];
	int total = 0;
	while (fgets(buffer, sizeof(buffer), in) != NULL) {
		parseInts(v, buffer, "x\n");
		int volume = v[0] * v[1] * v[2];
		int extra = max(max(v[0], v[1]), v[2]);
		int perim = 2 * (v[0] + v[1] + v[2] - extra) + volume; 
		total += perim;
	}
	fclose(in);
	printf("%d\n", total);
}
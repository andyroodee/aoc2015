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

void a() {
	FILE *in = fopen("input.txt", "r");
	
	char buffer[128];
	int v[3];
	int total = 0;
	while (fgets(buffer, sizeof(buffer), in) != NULL) {
		parseInts(v, buffer, "x\n");
		int a = v[0] * v[1];
		int b = v[0] * v[2];
		int c = v[1] * v[2];
		int extra = min(min(a, b), c);
		int area = 2 * (a + b + c) + extra;
		total += area;
	}
	fclose(in);
	printf("%d\n", total);
}
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define ITER_COUNT 40
#define MAX_LEN 1024*1024

void a() {
	static char in[MAX_LEN] = {0};
	strcpy(in, "3113322113");
	static char out[MAX_LEN] = {0};

	for (int i = 0; i < ITER_COUNT; i++) {
		char a = in[0];
		int count = 1;
		int offset = 0;
		size_t len = strlen(in);
		for (int j = 1; j < len; j++) {
			if (in[j] == a) {
				count++;
			} else {
				offset += sprintf(out + offset, "%d%c", count, a);
				a = in[j];
				count = 1;
			}
		}
		sprintf(out + offset, "%d%c", count, a);
		strcpy(in, out);
	}
	printf("%zu\n", strlen(in));
}

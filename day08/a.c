#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

void a() {
	FILE *in = fopen("input.txt", "r");
	char buffer[64] = {0};
	
	int chars_of_code = 0;
	int chars_in_memory = 0;
	while (fgets(buffer, sizeof(buffer), in) != NULL) {
		size_t len = strlen(buffer);
		buffer[--len] = 0;
		chars_of_code += len;
		for (int i = 0; i < len; i++) {
			if (buffer[i] == '"') {
				continue;
			}
			if (buffer[i] == '\\') {
				++i;
				if (buffer[i] == '\\' || buffer[i] == '"') {
					chars_in_memory++;
					continue;
				}
				if (buffer[i] == 'x') {
					i += 2;
					chars_in_memory++;
					continue;
				}
			}
			chars_in_memory++;
		}
	}
	fclose(in);
	printf("%d\n", chars_of_code - chars_in_memory);
}

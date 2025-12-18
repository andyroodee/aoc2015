#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

void b() {
	FILE *in = fopen("input.txt", "r");
	char buffer[64] = {0};
	
	int chars_of_code = 0;
	int chars_in_memory = 0;
	while (fgets(buffer, sizeof(buffer), in) != NULL) {
		size_t len = strlen(buffer);
		buffer[--len] = 0;
		chars_of_code += len;
		int expanded = 2;
		for (int i = 0; i < len; i++) {
			if (buffer[i] == '"') {
				expanded += 2;
				continue;
			}
			if (buffer[i] == '\\') {
				++i;
				expanded += 2;
				if (buffer[i] == '\\' || buffer[i] == '"') {
					expanded += 2;
					continue;
				}
				if (buffer[i] == 'x') {
					i += 2;
					expanded += 3;
					continue;
				}
			}
			expanded++;
		}
		chars_in_memory += expanded;
	}
	fclose(in);
	printf("%d\n", chars_in_memory - chars_of_code);
}

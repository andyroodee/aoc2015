#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_LEN 16

static bool is_nice(const char* s) {
	bool repeats = false;
	bool doubles = false;
	char buff[3] = {0};
	for (int i = 0; i < STR_LEN; i++) {
		if (i+2 < STR_LEN) {
			if (s[i] == s[i+2]) {
				repeats = true;
			}			
			strncpy(buff, s+i, 2);
			if (strstr(s+i+2, buff) != NULL) {
				doubles = true;
			}
		}
	}

	return doubles && repeats;
}

void b() {
	FILE *in = fopen("input.txt", "r");
	char buffer[32] = {0};
	int count = 0;
	while (fgets(buffer, sizeof(buffer), in) != NULL) {
		if (is_nice(buffer)) {
			count++;
		}
	}
	fclose(in);
	printf("%d\n", count);
}

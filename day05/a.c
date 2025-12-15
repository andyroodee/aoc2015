#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_LEN 16

const char *vowels = "aeiou";
const char *bad[] = { "ab", "cd", "pq", "xy" };

static bool is_nice(const char* s) {
	int vowel_count = 0;
	bool doubles = false;
	for (int i = 0; i < STR_LEN; i++) {
		if (strchr(vowels, s[i]) != NULL) {
			vowel_count++;
		}
		if (i < STR_LEN - 1) {
			if (s[i] == s[i+1]) {
				doubles = true;
			}
			for (int j = 0; j < 4; j++) {
				if (s[i] == bad[j][0] && s[i+1] == bad[j][1]) {
					return false;
				}
			}
		}
	}

	return doubles && vowel_count > 2;
}

void a() {
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

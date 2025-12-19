#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

static const char *alphabet = "abcdefghjkmnpqrstuvwxyz";

static int get_index(char c) {
	int base = c - 'a';
	if (c < 'i') {
		return base;
	}
	if (c < 'l') {
		return base - 1; 
	}
	if (c < 'o') {
		return base - 2;
	}
	return base - 3;
}

static bool good(const char *pw) {
	size_t len = strlen(pw);
	bool straight = false;
	int doubles = 0;
	int dbl_index = 0;
	for (int i = 0; i < len - 1; i++) {
		if (!straight && i < len - 2) {
			int a = get_index(pw[i]);
			int b = get_index(pw[i+1]);
			int c = get_index(pw[i+2]);
			if (a == b - 1 && b == c - 1) {
				straight = true;
			}
		}
		if (doubles < 2) {
			int a = get_index(pw[i]);
			int b = get_index(pw[i+1]);
			if (i > dbl_index && a == b) {
				doubles++;
				dbl_index = i+1;
			}
		}
	}
	return straight && doubles == 2;
}

void a() {
	char pw[] = "cqjxjnds";
	const size_t pw_len = strlen(pw);
	const size_t alphabet_len = strlen(alphabet);
	while (true) {
		int carry = 1;
		for (int j = pw_len - 1; j >= 0; j--) {
			int sum = get_index(pw[j]) + carry;
			if (sum >= alphabet_len) {
				sum = 0;
				carry = 1;
			} else {
				carry = 0;
			}
			pw[j] = alphabet[sum];
			if (carry == 0) {
				break;
			}
		}
		if (good(pw)) {
			printf("%s\n", pw);
			break;
		}
	}
}

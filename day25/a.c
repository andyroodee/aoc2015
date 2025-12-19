#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// To continue, please consult the code grid in the manual.  Enter the code at row 2947, column 3029.

void a() {
	const int row = 2947;
	const int col = 3029;
	int b = row*(row-1)/2 + 1;
	int c = b + (col-1)*row + (col-1)*(col)/2;
	const uint64_t m = 252533;
	const uint64_t n = 33554393;
	uint64_t x = 20151125;
	for (int i = 1; i < c; i++) {
		x = (m * (x % n)) % n;
	}
	printf("%lld\n", x);
}

#include <stdio.h>
#include <string.h>

void a();
void b();

int main(int argc, char **argv) {
	if (strncmp(argv[1], "a", 1) == 0) {
		a();
	} else {
		b();
	}
}
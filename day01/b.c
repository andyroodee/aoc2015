#include <stdio.h>
#include <string.h>

void b() {
	FILE *in = fopen("input.txt", "r");

	char buffer[7001] = {0};
	fgets(buffer, sizeof(buffer), in);
	fclose(in);

	int floor = 0;
	for (int i = 0; i < strlen(buffer); i++) {
		if (buffer[i] == '(') {
			floor++;
		} else {
			floor--;
		}
		if (floor == -1) {
			printf("%d\n", i+1);
			return;
		}
	}
}
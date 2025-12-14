#include <stdio.h>
#include <string.h>

void a() {
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
	}

	printf("%d\n", floor);
}
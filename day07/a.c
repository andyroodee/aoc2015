#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

// wires can go from 'a' to 'zz'
#define WIRE_COUNT 26*26+26+1

enum operator {
	INVALID,
	AND,
	AND_LITERAL,
	OR,
	NOT,
	LSHIFT,
	RSHIFT,
	VALUE,
	REF
};

typedef struct {
	int w;
	int a;
	int b;
	int value;
	enum op operator;
} Wire;

static Wire wire_vals[WIRE_COUNT];

static int get_wire_index(const char *wire) {
	int index = wire[0] - 'a' + 1;
	if (strlen(wire) > 1) {
		index *= 26;
		index += wire[1] - 'a' + 1;
	}
	return index;
}

static int get_value_of_wire(int index) {
	Wire *w = &wire_vals[index];
	switch (w->operator) {
	case VALUE:
		return w->value;
	case OR:
		w->value = get_value_of_wire(w->a) | get_value_of_wire(w->b);
		w->operator = VALUE;
		return w->value;
	case AND_LITERAL:		
		w->value = get_value_of_wire(w->a) & w->b;
		w->operator = VALUE;
		return w->value;	
	case AND:
		w->value = get_value_of_wire(w->a) & get_value_of_wire(w->b);
		w->operator = VALUE;
		return w->value;
	case NOT:
		w->value = ~get_value_of_wire(w->a);
		w->operator = VALUE;
		return w->value;		
	case LSHIFT:
		w->value = get_value_of_wire(w->a) << w->b;
		w->operator = VALUE;
		return w->value;		
	case RSHIFT:
		w->value = get_value_of_wire(w->a) >> w->b;
		w->operator = VALUE;
		return w->value;
	case REF:		
		w->value = get_value_of_wire(w->a);
		w->operator = VALUE;
		return w->value;
	}
}

void a() {
	FILE *in = fopen("input.txt", "r");
	char buffer[64] = {0};
	char ignore[4];
	int value = 0;
	char a[3];
	char b[3];
	char oper[7];
	char wire[3];
	
	while (fgets(buffer, sizeof(buffer), in) != NULL) {
		if (isdigit(buffer[0])) {
			sscanf(buffer, "%d%s%s", &value, ignore, wire);
			if (strcmp("AND", ignore) == 0) {
				// Annoying. Why is '1' allowed? The problem specifies that they're wires, not literals.
				sscanf(buffer, "%s%s%s%s%s", a, oper, b, ignore, wire);
				int index = get_wire_index(wire);
				wire_vals[index].w = index;
				wire_vals[index].a = get_wire_index(b);
				wire_vals[index].b = atoi(a);
				wire_vals[index].operator = AND_LITERAL;
				continue;
			}
			int index = get_wire_index(wire);
			wire_vals[index].w = index;
			wire_vals[index].value = value;
			wire_vals[index].operator = VALUE;
		} else if (buffer[0] == 'N') {			
			sscanf(buffer, "%s%s%s%s", oper, a, ignore, wire);
			int index = get_wire_index(wire);
			wire_vals[index].w = index;
			wire_vals[index].a = get_wire_index(a);
			wire_vals[index].operator = NOT;
		} else {
			sscanf(buffer, "%s%s", a, oper);
			if (strcmp("->", oper) == 0) {				
				sscanf(buffer, "%s%s%s", a, ignore, wire);	
				int index = get_wire_index(wire);
				wire_vals[index].w = index;
				wire_vals[index].a = get_wire_index(a);
				wire_vals[index].operator = REF;
				continue;
			}
			sscanf(buffer, "%s%s%s%s%s", a, oper, b, ignore, wire);	
			int index = get_wire_index(wire);
			wire_vals[index].w = index;
			wire_vals[index].a = get_wire_index(a);
			wire_vals[index].b = get_wire_index(b);
			if (strcmp("AND", oper) == 0) {
				wire_vals[index].operator = AND;
			} else if (strcmp("OR", oper) == 0) {
				wire_vals[index].operator = OR;
			} else if (strcmp("LSHIFT", oper) == 0) {
				wire_vals[index].operator = LSHIFT;
				wire_vals[index].b = atoi(b);
			} else if (strcmp("RSHIFT", oper) == 0) {
				wire_vals[index].operator = RSHIFT;
				wire_vals[index].b = atoi(b);
			} else {
				printf("Unknown operand %s\n", oper);
				exit(0);
			}
		}
	}
	fclose(in);
	int a_value = get_value_of_wire(get_wire_index("a"));
	printf("%d\n", a_value);
}

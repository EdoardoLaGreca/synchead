#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verbose_output = 0;
char *name = NULL;

int parse_args(int argc, char **argv) {
	int i = 0;

	/* for each argument */
	for (i = 1; i < argc; i++) {

		if (argv[i][0] == '-') {
			int j;

			/* for each character */
			for (j = 1; j < (int) strlen(argv[i]); j++) {
				char opt = argv[i][j];

				/* option */
				switch (opt) {
				case 'v':
					verbose_output = 1;
					break;
				default:
					fprintf(stderr, "ERROR: unknown option '%c'.\n", opt);
					return 0;
					break;
				}
			}

		} else {
			name = argv[i];

			/* name is the last argument */
			break;
		}

	}

	return 1;
}

/* print only when verbose output is on */
void printv(char *msg) {
	if (msg && verbose_output) {
		puts(msg);
	}
}

/* read functions (except for static ones) from file fd and return them in the
   array of strings functions, together with the number of functions read
*/
int get_funcions(FILE *fd, char **functions) {
	/* rewrite better
	int func_c_idx = 0, func_p_idx = 0, func_c_len = 80, func_p_len = 1, func_n;
	char *curr_func = calloc(func_c_len, sizeof(char));
	functions = calloc(func_p_len, sizeof(char*));

	if (!fd) {
		return NULL;
	}

	while (1) {
		char c;
		int i = 0;

		if (func_p_len == func_n) {
			buffer_len *= 2;
			functions = realloc(functions, buffer_len);
		}

		c = fgetc(fd);

		switch (c) {
		case ' ':
		case '\n':
			continue;
			break;
		case '(':
			break;
		case ')':
			break;
		case '{':
			i = 1;
			while (i != 0) {
				c = fgetc(fd);
				if (c == '{') {
					i++;
					continue;
				}

				if (c == '}') {
					i--;
					continue;
				}
			}
			break;
		default:
			functions[buffer_idx++] = c;
			break;
		}
	}

	*/
}

int main() {
	FILE *sfd, *hfd;
	char *source_name, *header_name, **func_array;
	int i, func_n;

	if (!parse_args) {
		exit(EXIT_FAILURE);
	}

	if (!name) {
		fprintf(stderr, "ERROR: no name was provided.\n");
		exit(EXIT_FAILURE);
	}

	source_name = calloc(strlen(name) + 3, sizeof(char));
	
	/* read the source file and get the functions */
	sfd = fopen(source_name, "r");

	if (!sfd) {
		sprintf(stderr, "ERROR: file %s not found.", source_name);
		exit(EXIT_FAILURE);
	}

	func_n = get_funcions(sfd, func_array);

	for (i = 0; i < func_n; i++) {
		/* TODO */
	}

	return 0;
}

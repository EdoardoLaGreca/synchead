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
	/* func_c_len = function length in characters
	   func_n_len = number of functions
	   func_c_idx = current index of function characters
	   func_n_idx = current index of functions
	*/
	int func_c_len = 80, func_n_len = 1;
	int func_c_idx = 0, func_n_idx = 0;

	char *curr_func;

	if (!fd) return -1;

	curr_func = calloc(func_c_len, sizeof(char));
	functions = calloc(func_n_len, sizeof(char*));

	if (!curr_func || !functions) return -1;

	while (1) {
		char c = 0, prev_c = 0;

		if (func_c_idx == func_c_len) {
			/* resize string */
			func_c_len *= 1.5;
			curr_func = realloc(curr_func, func_c_len);

			if (!curr_func) return -1;
		}

		prev_c = c;
		c = fgetc(fd);

		if (prev_c == 0) {
			/* first iteration of loop */
			continue;
		}

		switch (c) {
		case ' ':
		case '\t':
		case '\n':
			/* remove extra spaces */
			if (prev_c == ' ' || prev_c == '\t' || prev_c == '\n') {
				continue;
			} else {
				curr_func[func_c_idx++] = ' ';
			}
			break;
		case '{':
			int i = 1;

			/* add new function */
			func_n_len++;
			functions = realloc(functions, func_n_len);
			if (!functions) return -1;
			functions[func_n_idx++] = curr_func;

			/* reset current function string */
			curr_func = calloc(func_c_len, sizeof(char));
			if (!curr_func) return -1;

			/* skip to the matching '}' */
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
			curr_func[func_c_idx++] = c;
			break;
		}
	}
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

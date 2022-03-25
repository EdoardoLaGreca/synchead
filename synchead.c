#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function parameter (list item) */
typedef struct func_param_s {
	char *type;
	char *name;
	func_param_s *next;
} func_param;

/* function */
typedef struct {
	char* name;
	int params_n;
	func_param *params;
} function;

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

/* read functions (except static ones) in file and return them as a list */
function *get_funcions(FILE *fd) {
	int buffer_idx = 0, buffer_len = 80;
	char *buffer = calloc(buffer_len, sizeof(char));

	if (!fd) {
		return NULL;
	}

	while (1) {
		char c;
		int i = 0;

		if (buffer_idx > buffer_len) {
			/* buffer has reached limit, expand */
			buffer_len *= 2;
			buffer = realloc(buffer, buffer_len);
		}

		c = fgetc(fd);

		switch (c) {
		case ' ':
		case '\n':
			/*TODO*/
			continue;
			break;
		case '(':
			/*TODO*/
			break;
		case ')':
			/*TODO*/
			break;
		case '{':
			/* skip to the corresponding '}' */
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
			buffer[buffer_idx++] = c;
			break;
		}
	}
}

int main() {
	FILE *sfd, *hfd;
	char *source_name, *header_name;

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



	return 0;
}

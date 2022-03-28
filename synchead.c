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

/* skip to next occurrence of string in a file, do nothing if the string is
   empty
*/
void skip_to_string(FILE *fd, char *str) {
	int chunk_size, buffer_size;
	char *buffer;

	chunk_size = strlen(str);
	buffer_size = chunk_size * 4;
	buffer = calloc(buffer_size, sizeof(char));
	if (!fd || !buffer) return;
	fgets(buffer, buffer_size, fd);

	while (strstr(buffer, str) == NULL) {
		/* last chunk of buffer */
		char *last_chunk;
		last_chunk = malloc(chunk_size);
		memcpy(last_chunk, buffer + buffer_size - chunk_size, chunk_size);

		/* put new data in buffer, the new first chunk is the previous last
		   chunk
		*/
		/*TODO*/
	}
}

/* skip to matching curly brace */
void skip_to_matching_cb(FILE *fd) {
	char c = 0, other;
	int i = 1;

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
		case '*': /* comments */
			if (prev_c == '/') {
				skip_to_string(fd, "*/");
			}
			break;
		case '#': /* preprocessor directives */
			while (c != '\n') {

			}
		case ' ':
		case '\t':
		case '\n': /* whitespace */
			/* remove extra spaces */
			if (prev_c == ' ' || prev_c == '\t' || prev_c == '\n') {
				continue;
			} else {
				curr_func[func_c_idx++] = ' ';
			}
			break;
		case '{': /* function body */
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
			skip_to_matching_cb(fd);
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
		func_array[i];
	}

	

	return 0;
}

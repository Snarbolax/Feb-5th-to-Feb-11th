#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABSTOP 10
#define BUFFLEN 100

char buf[BUFFLEN];
char temp[BUFFLEN];
char fold[BUFFLEN];
char* pointer;

int main(int argc, const char* argv[]) {
	FILE* fileIN = fopen(argv[1], "r");
	FILE* fileOUT = fopen(argv[2], "w");
	int stop = TABSTOP;
	int newline_count = 0;
	int point = 0;

	if (argc != 3 || argc != 4) {
		fprintf(stderr, "Usage: ./detab inputfile outputfile tabstops(optional)\n");
		exit(1);
	}
	if (fileIN == NULL) {
		fprintf(stderr, "no input file detected\n");
		exit(1);
	}
	else if (fileOUT == NULL) {
		fprintf(stderr, "no output file detected\n");
		exit(1);
	}

	if (argc == 4)
		stop = *argv[3];

	fgets(buf, BUFFLEN - 1, fileIN);
	strcpy(temp, buf);
	pointer = temp;
	while (strlen(fold)-newline_count != strlen(temp)) {
		if (!isspace(pointer + (stop - point))) {
			strncat(fold, pointer, stop - point);
			strcat(fold, "\n");
			++newline_count;

			pointer += (stop - point);
			point = 0;
		}
		else
			++point;
	}

	fputs(fold, fileOUT);

	fclose(fileIN);
	fclose(fileOUT);

	return 0;
}

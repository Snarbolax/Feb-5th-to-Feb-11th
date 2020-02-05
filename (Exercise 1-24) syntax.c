#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, const char* argv[]) {
	FILE* fileIN = fopen(argv[1], "r");

	int par_c, brack_c, brace_c, sq_c, dq_c, u_c = 0;

	if (argc != 2) {
		fprintf(stderr, "Usage: ./detab inputfile\n");
		exit(1);
	}
	if (fileIN == NULL) {
		fprintf(stderr, "no input file detected\n");
		exit(1);
	}

	char c = fgetc(fileIN);

	while (c != EOF) {
		switch (c) {
		case '(':
			++par_c;
			break;
		case ')':
			--par_c;
			break;
		case '[':
			++brack_c;
			break;
		case ']':
			--brack_c;
			break;
		case '{':
			++brace_c;
			break;
		case '}':
			--brace_c;
			break;
		case ''':
			++sq_c;
			break;
		case '"':
			++dq_c;
			break;
		default:
			break;
		}
		c = fgetc(fileIN);
	}

	if (par_c != 0)
		u_c += par_c;
	if (brack_c != 0)
		u_c += brack_c;
	if (brace_c != 0)
		u_c += brace_c;
	if (sq_c % 2 != 0)
		++u_c;
	if (dq_c % 2 != 0)
		++u_c;

	fprintf(stderr, "Error: Syntax error. \%d unbalanced separator(s) count.\n", u_c);

	/*
	if (par_c != 0)
		fprintf(stderr, "\%d Parenthesis error(s)\n", par_c);
	if (brack_c != 0)
		fprintf(stderr, "\%d Bracket error(s)\n", brack_c);
	if (brace_c != 0)
		fprintf(stderr, "\%d Brace error(s)\n", brace_c);
	if (sq_c % 2 != 0)
		fprintf(stderr, "\%d Single quote error(s)\n", sq_c % 2);
	if (dq_c % 2 != 0)
		fprintf(stderr, "\%d Double quote error(s)\n", dq_c % 2);
	*/

	fclose(fileIN);

	return 0;
}

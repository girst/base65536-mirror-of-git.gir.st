/* base65536 en- and decoder with usage similar to GNU's base64. 
(C) 2016 Tobias Girstmair, http://isticktoit.net/
Released under the GNU GPL v3. See LICENSE for details. */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base65536.h"

#define VERSION "0.1"

#define DEFAULT_WRAP 72
enum OPERATIONS {
	ENCODE,
	DECODE
};

void do_encode (FILE* in, FILE* out, int wrap_column);
void do_decode (FILE* in, FILE* out, int ignore_garbage);

int main (int argc, char** argv) {
	int operation = ENCODE;
	int wrap = DEFAULT_WRAP;
	int garb_ignore = 0;
	FILE* file_to_op = stdin;

	for (int i = 1; i < argc; i++) {
	//TODO: not efficient and ugly
		if (strcmp (argv[i], "-d") == 0 || strcmp (argv[i], "--decode") == 0) {
			operation = DECODE;
		} else if (strcmp (argv[i], "-i") == 0 || strcmp (argv[i], "--ignore-garbage") == 0) {
			garb_ignore = 1;
		} else if (strcmp (argv[i], "-w") == 0) {
			if (i == argc-1) {
				fputs ("option required for argument -w", stderr);
				return EXIT_FAILURE;
			} else {
				for (int j = 0; argv[i+1][j] != '\0'; j++)
					if (argv[i+1][j] < '0' || argv[i+1][j] > '9') {
						fputs ("option required for argument -w", stderr);
						return EXIT_FAILURE;
					}
						
				wrap = atoi (argv[++i]);
			}
		} else if (strcmp (argv[i], "--help") == 0) {
			fprintf (stderr, "help. ");
			return EXIT_SUCCESS;
		} else if (strcmp (argv[i], "--version") == 0) {
			fprintf (stderr, "base65536 version %s", VERSION);
			return EXIT_SUCCESS;
		} else {
			if (argv[i][0] == '-') {
				fprintf (stderr, "%s is not a valid argument.\n", argv[i]);
				return EXIT_FAILURE;
			} else if (file_to_op == stdin) {
				file_to_op = fopen (argv[i], "rb");
			} else {
				fputs ("cannot give more than one file.\n", stderr);
				return EXIT_FAILURE;
			}
		}
	}

	if (operation == DECODE) {
		do_decode (file_to_op, stdout, garb_ignore);
	} else {
		do_encode (file_to_op, stdout, wrap);
	}

	if (file_to_op != stdin) fclose (file_to_op);

	return 0;
}


void do_encode (FILE* in, FILE* out, int wrap_column) {
	int in_char[2];
	char out_utf8[5];
	int unicode_cp;
	long cnt = 0;

	while (1) {
		if ((in_char[0] = getc(in)) == EOF) break;
		in_char[1] = getc(in);

		unicode_cp = base65536_encode_char (in_char);
		codepoint_to_utf8 (unicode_cp, out_utf8);
		fprintf (out, "%s%s", wrap_column&&!(cnt%wrap_column)&&cnt?"\n":"", out_utf8);
		cnt++;
		if (in_char[1] == EOF) break;
	}
	printf ("\n");
}

void do_decode (FILE* in, FILE* out, int ignore_garbage) {
	int out_char[2];
	char in_utf8[5];
	int unicode_cp;

	while (1) {
		for (int i = 0; i < 5; i++) {
			int c = getc (in);
			if (c == EOF) {
				return;
			} else if (i != 0 && c < 0x80) { //start of new asciichar
				ungetc (c, in);
				in_utf8[i] = '\0';
				break;
			} else if (i != 0 && c >= 0xc0) { //start of new utf8char
				ungetc (c, in);
				in_utf8[i] = '\0';
				break;
			}
			in_utf8[i] = c;
		}
		unicode_cp = utf8_to_codepoint (in_utf8);
		//ignore ascii-chars, because base65k won't map to those (but
		//whitespace may be added by the encoder / medium)
		if (unicode_cp < 0x80) continue;

		if (base65536_decode_char (unicode_cp, out_char) > 0) {
			fputc (out_char[0], out);
			fputc (out_char[1], out);
		} else {
			if (!ignore_garbage) {
				fprintf (stderr, "Unrecognized glyph %s\n", in_utf8);
				return;
			}
		}
	}
}

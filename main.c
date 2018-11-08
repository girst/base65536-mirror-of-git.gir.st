/* base65536 en- and decoder with usage similar to GNU's base64. 
(C) 2016 Tobias Girstmair, http://isticktoit.net/
Released under the GNU GPL v3. See LICENSE for details. */

#define _XOPEN_SOURCE
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "base65536.h"

#define VERSION "0.2"

#define DEFAULT_WRAP 72

#define COPYRIGHT "(C) 2016 Tobias Girstmair, GPLv3"
#define HELP_TEXT \
	"Usage: %s [OPTION]... [FILE]\n"\
	"Options: -d (decode), -i (ignore-garbage), -w COLS (wrap, default %d) "\
	"-v (version) -h (help)\n"

struct ops {
	FILE* f;
	int d; /*decode*/
	int i; /*ignore-garbage*/
	int w; /*wrap*/
};

void do_encode (FILE* in, FILE* out, int wrap_column);
void do_decode (FILE* in, FILE* out, int ignore_garbage);

int main (int argc, char** argv) {
	struct ops op = {stdin, 0, 0, DEFAULT_WRAP};
	int opt;

	opterr=0; /* suppress default error messages */
	while ( (opt = getopt(argc, argv, "diw:vh")) != -1)  {
		switch (opt) {
		case 'd': op.d = 1; break;
		case 'i': op.i = 1; break;
		case 'w': op.w = atoi (optarg); break;
		case 'v':
			fprintf (stderr, "base65536 %s\n%s\n", VERSION, COPYRIGHT);
			return 0;
		case 'h':
			fprintf (stderr, HELP_TEXT, argv[0], DEFAULT_WRAP);
			return 0;
		default:
			fprintf (stderr, "unknown option '-%c'.\n", optopt);
			return 1;
		}
	}
	if (argc-optind > 1) {
		fprintf (stderr, "%s: extra operand '%s'. \n", argv[0], argv[argc-1]);
		return 1;
	} else if (optind < argc) {
		if (strcmp (argv [optind], "-") != 0) {
			op.f = fopen (argv[optind], "rb");
			if (op.f == NULL) {
				fprintf (stderr, "%s: %s: %s\n", argv[0], argv[optind], strerror(errno));
				return 1;
			}
		}
        }

	if (op.d) {
		do_decode (op.f, stdout, op.i);
	} else {
		do_encode (op.f, stdout, op.w);
	}

	if (op.f != stdin) fclose (op.f);

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
	int chars_written;

	while (1) {
		for (int i = 0; i < 5; i++) {
			int c = getc (in);
			if (c == EOF) {
				return;
			} else if (i != 0 && c < 0x80) { /* start of new asciichar */
				ungetc (c, in);
				in_utf8[i] = '\0';
				break;
			} else if (i != 0 && c >= 0xc0) { /* start of new utf8char */
				ungetc (c, in);
				in_utf8[i] = '\0';
				break;
			}
			in_utf8[i] = c;
		}
		unicode_cp = utf8_to_codepoint (in_utf8);
		/* ignore ascii-chars, because base65k won't map to those (but
		whitespace may be added by the encoder / medium) */
		if (unicode_cp < 0x80) continue;

		chars_written = base65536_decode_char (unicode_cp, out_char);
		if (chars_written > 0) {
			fputc (out_char[0], out);
			if (chars_written ==2) fputc (out_char[1], out);
		} else {
			if (!ignore_garbage) {
				fprintf (stderr, "Unrecognized glyph %s\n", in_utf8);
				return;
			}
		}
	}
}

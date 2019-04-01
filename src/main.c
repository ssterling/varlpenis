/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "draw.h"
#include "options.h"
#include "strings.h"

int main(int argc, char *argv[])
{
	unsigned int length, distance;
	enum DRAW_FLAGS_E flags;
	struct OPTIONS_S options;

	/* Stuff for getopt */
	int index;
	int ch;
	
	/* Seed random number generator */
	srand((unsigned)time(NULL));
	
	/* Initialise length and distance to random numbers, override-able
	 * via program arguments */
	length =
	  rand() % (RAND_LENGTH_MAX - RAND_LENGTH_MIN) + RAND_LENGTH_MIN;
	distance =
	  rand() % (RAND_DISTANCE_MAX - RAND_DISTANCE_MIN) + RAND_DISTANCE_MIN;

	flags = NO_FLAGS;

	options.flags = NO_OPTS;
	options.error_code = ERR_OK;
	options.length = 0;
	options.distance = 0;
	options.error_char = '!'; /* placeholder */

	opterr = 0;
#ifdef VP_USE_COLOR
	while ((ch = getopt(argc, argv, "ce:hl:v")) != -1)
#else /* VP_USE_COLOR */
	while ((ch = getopt(argc, argv, "e:hl:v")) != -1)
#endif /* VP_USE_COLOR */
		switch (ch) {
#ifdef VP_USE_COLOR
			case 'c':
				flags |= COLOR;
				break;
#endif /* VP_USE_COLOR */
			case 'e':
				if (atoi(optarg) < 1) {
					options.error_code = ERR_NOTINT;
					options.error_char = 'e';
					goto BREAK_FROM_GETOPT;
				}
				options.flags |= OPT_DISTANCE;
				options.distance = (unsigned)atoi(optarg);
				break;
			case 'h':
				options.flags |= OPT_HELP;
				break;
			case 'l':
				if (atoi(optarg) < 1) {
					options.error_code = ERR_NOTINT;
					options.error_char = 'l';
					goto BREAK_FROM_GETOPT;
				}
				options.flags |= OPT_LENGTH;
				options.length = (unsigned)atoi(optarg);
				break;
			case 'v':
				options.flags |= OPT_VERSION;
				break;
			case '?':
				if (optopt == 'e' || optopt == 'l') {
					options.error_code = ERR_NOARG;
					options.error_char = (char)optopt;
				} else {
					options.error_code = ERR_UNKNOWNCHAR;
					options.error_char = (char)optopt;
				}
				goto BREAK_FROM_GETOPT;
			default:
				/* Nothing happened...? */
				break;
		};
	BREAK_FROM_GETOPT:

	switch (options.error_code) {
		case ERR_OK:
			break;
		case ERR_NOARG:
			fprintf(stderr, "Error: option `-%c' requires a "
			                "positive integer as an argument\n",
					options.error_char);
			return 1;
		case ERR_NOTINT:
			fprintf(stderr, "Error: argument to option `-%c' "
			                "must be a positive integer\n",
			                options.error_char);
			return 1;
		case ERR_UNKNOWNCHAR:
			if (isprint(options.error_char))
				fprintf(stderr, "Error: unknown option `-%c'\n",
						options.error_char);
			else
				fprintf(stderr, "Error: unknown option char "
						"`\\x%x'\n",
						(int)options.error_char);
			return 1;
		default:
			fprintf(stderr, "Error: bogus error code received "
			                "from options parser\n");
			return 1;
	}

	/* The code here is a bit clunky, but the intention is to print both
	 * version and help information if requested.  -- If `return 0' was
	 * included in the `if' blocks, calling `varlpenis -vh' would print
	 * version info and exit before printing the help message. */
	if (options.flags & OPT_VERSION)
		printf("%1$s v%2$s - %3$s\n%4$s\n",
		       VP_PROGRAM_NAME, VP_VERSION_STR, VP_PROGRAM_DESC,
		       VP_COPYRIGHT);
	if (options.flags & OPT_HELP)
#ifdef VP_USE_COLOR
		printf("usage: %s [options]\n"
		       "  options:\n"
		       "    -c       output color\n"
		       "    -e num   set length of semen string\n"
		       "    -h       show this message\n"
		       "    -l num   set length of shaft\n"
		       "    -v       show copyright and version info\n",
		       VP_PROGRAM_NAME);
#else /* VP_USE_COLOR */
		printf("usage: %s [options]\n"
		       "  options:\n"
		       "    -e num   set length of semen string\n"
		       "    -h       show this message\n"
		       "    -l num   set length of shaft\n"
		       "    -v       show copyright and version info\n",
		       VP_PROGRAM_NAME);
#endif /* VP_USE_COLOR */
	if (options.flags & OPT_HELP || options.flags & OPT_VERSION)
		return 0;

	/* If these flags are set, length/distance are user-specified */
	if (options.flags & OPT_LENGTH)
		length = options.length;
	if (options.flags & OPT_DISTANCE)
		distance = options.distance;

	/* `draw_penis()' prints to stdout and returns nothing */
	draw_penis(length, distance, flags);

	return 0;
}

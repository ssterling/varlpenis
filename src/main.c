/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#ifdef VP_USE_POSIXTIME
#include <sys/time.h>
#endif /* VP_USE_POSIXTIME */

#include "draw.h"
#include "options.h"
#include "strings.h"
#include "exits.h"
#include "i18n.h"

int main(int argc, char *argv[])
{
	unsigned int length, distance;
	enum DRAW_FLAGS_E flags;
	struct OPTIONS_S options;

	/* Stuff for getopt */
	int index;
	int ch;

	/* For the `strtol()` shenanigans below */
	long int strtol_tmp;

#ifdef VP_USE_POSIXTIME
	struct timeval current_time;
#endif /* VP_USE_POSIXTIME */

#ifdef VP_USE_GETTEXT
	/* Get locale from environment */
	setlocale(LC_ALL, "");
	bindtextdomain(VP_TEXTDOMAIN, VP_LOCALE_DIR);
	textdomain(VP_TEXTDOMAIN);
#endif /* VP_USE_GETTEXT */
	
	/* Seed random number generator */
#ifdef VP_USE_POSIXTIME
	gettimeofday(&current_time, NULL);
	srand((unsigned)current_time.tv_usec);
#else /* VP_USE_POSIXTIME */
	srand((unsigned)time(NULL));
#endif /* VP_USE_POSIXTIME */
	
	/* Initialise length and distance to random numbers, override-able
	 * via program arguments */
	length =
	  (rand() / 100) % (RAND_LENGTH_MAX - RAND_LENGTH_MIN)
	  + RAND_LENGTH_MIN;
	distance =
	  (rand() / 100) % (RAND_DISTANCE_MAX - RAND_DISTANCE_MIN)
	  + RAND_DISTANCE_MIN;

	flags = NO_FLAGS;

	options.flags = NO_OPTS;
	options.error_code = ERR_OK;
	options.length = 0;
	options.distance = 0;
	options.error_char = '!'; /* placeholder */

	opterr = 0;
	while ((ch = getopt(argc, argv, GETOPT_OPTIONS_STRING)) != -1)
		switch (ch) {
#ifdef VP_USE_COLOR
			case 'c':
				flags |= COLOR;
				break;
#endif /* VP_USE_COLOR */
			case 'd': /* Undocumented alias for `-e' */
			case 'e':
				errno = 0;
				strtol_tmp = 0;
				strtol_tmp = strtol(optarg, NULL, 0);
				if ((strtol_tmp == LONG_MAX && errno == ERANGE)
				    || (strtol_tmp > UINT_MAX)) {
					options.error_code = ERR_BIGUINT;
					options.error_char = 'e';
					goto BREAK_FROM_GETOPT;
				} else if (strtol_tmp < 0) {
					options.error_code = ERR_NOTINT;
					options.error_char = 'e';
					goto BREAK_FROM_GETOPT;
				}
				options.flags |= OPT_DISTANCE;
				options.distance = (unsigned int)strtol_tmp;
				break;
#ifdef VP_USE_FULLWIDTH
			case 'f':
				flags |= FULLWIDTH;
				break;
#endif /* VP_USE_FULLWIDTH */
			case 'h':
				options.flags |= OPT_HELP;
				break;
			case 'l':
				errno = 0;
				strtol_tmp = 0;
				strtol_tmp = strtol(optarg, NULL, 0);
				if ((strtol_tmp == LONG_MAX && errno == ERANGE)
				    || (strtol_tmp > UINT_MAX)) {
					options.error_code = ERR_BIGUINT;
					options.error_char = 'l';
					goto BREAK_FROM_GETOPT;
				} else if (strtol_tmp < 1) {
					options.error_code = ERR_NOTINT;
					options.error_char = 'l';
					goto BREAK_FROM_GETOPT;
				}
				options.flags |= OPT_LENGTH;
				options.length = (unsigned int)strtol_tmp;
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
			fprintf(stderr, _("Error: option `-%c' requires a "
			                  "positive integer as an argument\n"),
					options.error_char);
			return EX_USAGE;
		case ERR_NOTINT:
			fprintf(stderr, _("Error: argument to option `-%c' "
			                  "must be a positive integer\n"),
			                options.error_char);
			return EX_USAGE;
		case ERR_NOTINTORZERO:
			fprintf(stderr, _("Error: argument to option `-%c' "
			                  "must be zero or a positive integer\n"),
			                options.error_char);
			return EX_USAGE;
		case ERR_BIGUINT:
			fprintf(stderr, _("Error: argument to option `-%c' "
			                  "is too large (above `UINT_MAX').\n"),
			                options.error_char);
			return EX_USAGE;
		case ERR_UNKNOWNCHAR:
			if (isprint(options.error_char))
				fprintf(stderr, _("Error: unknown option `-%c'\n"),
						options.error_char);
			else
				fprintf(stderr, _("Error: unknown option char "
						  "`\\x%x'\n"),
						(int)options.error_char);
			return EX_USAGE;
		default:
			fprintf(stderr, _("Error: bogus error code received "
			                  "from options parser\n"));
			return EX_SOFTWARE;
	}

	/* The code here is a bit clunky, but the intention is to print both
	 * version and help information if requested.  -- If `return' was
	 * included in the `if' blocks, calling `varlpenis -vh' would print
	 * version info and exit before printing the help message. */
	if (options.flags & OPT_VERSION)
		printf("%s v%s - %s\n%s\n",
		       VP_PROGRAM_NAME, VP_VERSION_STR, VP_PROGRAM_DESC,
		       VP_COPYRIGHT);
	if (options.flags & OPT_HELP) {
	/* XXX This is a very weird way to implement a dynamically compiled
	       help message, but it's the only working one I could think of */
		printf(_("usage: %s [options]\n"
		         "  options:\n"),
		       VP_PROGRAM_NAME);
#ifdef VP_USE_COLOR
		printf(_("    -c       output color\n"));
#endif /* VP_USE_COLOR */
		printf(_("    -e num   set length of semen string\n"));
#ifdef VP_USE_FULLWIDTH
		printf(_("    -f       output fullwidth characters\n"));
#endif /* VP_USE_FULLWIDTH */
		printf(_("    -h       show this message\n"));
		printf(_("    -l num   set length of shaft\n"));
		printf(_("    -v       show copyright and version info\n"));
	}
	if (options.flags & OPT_HELP || options.flags & OPT_VERSION)
		return EX_OK;

	/* If these flags are set, length/distance are user-specified */
	if (options.flags & OPT_LENGTH)
		length = options.length;
	if (options.flags & OPT_DISTANCE)
		distance = options.distance;

	/* `draw_penis()' prints to stdout and returns nothing */
	draw_penis(length, distance, flags);

	return EX_OK;
}

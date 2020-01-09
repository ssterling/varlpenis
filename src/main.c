
/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>

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

#ifdef VP_USE_POSIXTIME
	struct timeval current_time;
#endif /* VP_USE_POSIXTIME */

#ifdef VP_NO_ARGV
	char options_input[MAX_LINE];
#endif /* VP_NO_ARGV */

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

	/* If system doesn't use argv, get options via user input */
#ifdef VP_NO_ARGV
	printf("Options line (-h for help): ");
	fgets(options_input, MAX_LINE, stdin);
	parse_options_line(options_input, &options);
#else /* VP_NO_ARGV */
	parse_options(argc, argv, &options);
#endif /* VP_NO_ARGV */

	if (options.flags & OPT_COLOR) { flags |= COLOR; }
	if (options.flags & OPT_FULLWIDTH) { flags |= FULLWIDTH; }

	switch (options.error_code) {
		case ERR_OK:
			break;
		case ERR_NOARG:
			fprintf(stderr, _("Error: option `%c%c' requires a "
			                  "positive integer as an argument\n"),
					OPTION_CHAR, options.error_char);
			return EX_USAGE;
		case ERR_NOTINT:
			fprintf(stderr, _("Error: argument to option `%c%c' "
			                  "must be a positive integer\n"),
			                OPTION_CHAR, options.error_char);
			return EX_USAGE;
		case ERR_NOTINTORZERO:
			fprintf(stderr, _("Error: argument to option `%c%c' "
			                  "must be zero or a positive integer\n"),
			                OPTION_CHAR, options.error_char);
			return EX_USAGE;
		case ERR_BIGUINT:
			fprintf(stderr, _("Error: argument to option `%c%c' "
			                  "is too large (above `UINT_MAX').\n"),
			                OPTION_CHAR, options.error_char);
			return EX_USAGE;
		case ERR_UNKNOWNCHAR:
			if (isprint(options.error_char))
				fprintf(stderr, _("Error: unknown option `%c%c'\n"),
						OPTION_CHAR, options.error_char);
			else
				fprintf(stderr, _("Error: unknown option char "
						  "`\\x%X'\n"),
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
		printf(_("    %cc       output color\n"), OPTION_CHAR);
#endif /* VP_USE_COLOR */
		printf(_("    %ce num   set length of semen string\n"),
		       OPTION_CHAR);
#ifdef VP_USE_FULLWIDTH
		printf(_("    %cf       output fullwidth characters\n"),
		       OPTION_CHAR);
#endif /* VP_USE_FULLWIDTH */
		printf(_("    %ch       show this message\n"), OPTION_CHAR);
		printf(_("    %cl num   set length of shaft\n"), OPTION_CHAR);
		printf(_("    %cv       show copyright and version info\n"),
		       OPTION_CHAR);
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


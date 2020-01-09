/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

#include <ctype.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#ifdef VP_NO_ARGV
#include <stdio.h>
#endif /* VP_NO_ARGV */

/* For use on non-POSIX systems with some
 * sort of separate getopt implementation */
#ifdef VP_USE_GETOPT_H
#include <getopt.h>
#else /* VP_USE_GETOPT_H */
#include <unistd.h>
#endif /* VP_USE_GETOPT_H */

#include "options.h"

void parse_options(int argc, char *argv[], struct OPTIONS_S *options)
{ 
	int index;
	int ch;

	/* For the `strtol()` shenanigans below */
	long int strtol_tmp;

	options->flags = NO_OPTS;
	options->error_code = ERR_OK;
	options->length = 0;
	options->distance = 0;
	options->error_char = '!'; /* placeholder */

	opterr = 0;
	while ((ch = getopt(argc, argv, GETOPT_OPTIONS_STRING)) != -1)
		switch (ch) {
#ifdef VP_USE_COLOR
			case 'c':
				options->flags |= OPT_COLOR;
				break;
#endif /* VP_USE_COLOR */
			case 'd': /* Alias for `-e' */
			case 'e':
				errno = 0;
				strtol_tmp = 0;
				strtol_tmp = strtol(optarg, NULL, 0);
				if ((strtol_tmp == LONG_MAX && errno == ERANGE)
				    || (strtol_tmp > UINT_MAX)) {
					options->error_code = ERR_BIGUINT;
					options->error_char = 'e';
					return;
				} else if (strtol_tmp < 0) {
					options->error_code = ERR_NOTINT;
					options->error_char = 'e';
					return;
				}
				options->flags |= OPT_DISTANCE;
				options->distance = (unsigned int)strtol_tmp;
				break;
#ifdef VP_USE_FULLWIDTH
			case 'f':
				options->flags |= OPT_FULLWIDTH;
				break;
#endif /* VP_USE_FULLWIDTH */
			case 'h':
				options->flags |= OPT_HELP;
				break;
			case 'l':
				errno = 0;
				strtol_tmp = 0;
				strtol_tmp = strtol(optarg, NULL, 0);
				if ((strtol_tmp == LONG_MAX && errno == ERANGE)
				    || (strtol_tmp > UINT_MAX)) {
					options->error_code = ERR_BIGUINT;
					options->error_char = 'l';
					return;
				} else if (strtol_tmp < 1) {
					options->error_code = ERR_NOTINT;
					options->error_char = 'l';
					return;
				}
				options->flags |= OPT_LENGTH;
				options->length = (unsigned int)strtol_tmp;
				break;
			case 'v':
				options->flags |= OPT_VERSION;
				break;
			case '?':
				if (optopt == 'e' || optopt == 'l') {
					options->error_code = ERR_NOARG;
					options->error_char = (char)optopt;
				} else {
					options->error_code = ERR_UNKNOWNCHAR;
					options->error_char = (char)optopt;
				}
				return;
			default:
				/* Nothing happened...? */
				break;
		};
	
	return;
}

#ifdef VP_NO_ARGV
void parse_options_line(char input[MAX_LINE], struct OPTIONS_S *options)
{
	int argc;
	char *argv[MAX_ARGS];
	char *tmp;

	/* I don't understand how it works either, but I did it */
	argc = 1;
	tmp = strtok(input, " \n");
	while (tmp != NULL && argc < MAX_ARGS) {
		argv[argc] = tmp;
		argc++;
		tmp = strtok(NULL, " \n");
	}
	argv[argc] = 0;

	parse_options(argc, argv, options);

	return;
}
#endif /* VP_NO_ARGV */

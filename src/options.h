/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

#ifndef VP_OPTIONS_H
#define VP_OPTIONS_H

/* Winblows and M$-DOS like `/' as an option prefix for some reason; if you
 * really insist on using that instead of `-', change it here. */
#define OPTIONS_PREFIX_CHAR '-'

enum OPTIONS_E {
	NO_OPTS      = 0,
	OPT_HELP     = 1,  /* Print help message to stdout */
	OPT_VERSION  = 2,  /* Print version info */
	OPT_LENGTH   = 4,  /* The length was specified */
	OPT_DISTANCE = 8   /* The distance was specified */
};

enum OPTIONS_ERROR_E {
	ERR_OK          = 0,
	ERR_NOARG       = 1,
	ERR_NOTINT      = 2,
	ERR_UNKNOWNCHAR = 3
};

struct OPTIONS_S {
	enum OPTIONS_E flags;

	/* Only evaluated for error-handling */
	enum OPTIONS_ERROR_E error_code;
	char error_char;

	/* If the LENGTH and/or DISTANCE flags are set, `main()' will use
	 * the respective of these numbers instead of a random value */
	unsigned int length;
	unsigned int distance;
};

static int is_positive_int(const char *val_str);
struct OPTIONS_S parse_options(int argc, char *argv[]);

#endif /* ! VP_OPTIONS_H */

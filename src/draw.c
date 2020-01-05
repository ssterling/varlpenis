/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "draw.h"

/* The `main()' function is 99% options-parsing and error-handling;
 * this file itself (and the corresponding `draw.h') can be utilised
 * independently inside another program or whatnot if desired. */

static char *repeat_string(const char *str, unsigned int count)
{
	char *ret;
	int str_length;

	if (count == 0) {
		ret = "\0";
		return ret;
	}

	str_length = strlen(str) + 1;

	ret = malloc(str_length * count + 1);
	strncpy(ret, str, str_length);

	while (--count > 0)
		strncat(ret, str, str_length);

	return ret;
}

void draw_penis(const unsigned int length, const unsigned int distance,
                const enum DRAW_FLAGS_E flags)
{
#if defined(VP_USE_FULLWIDTH) && defined(VP_USE_COLOR_ANSI)
	if ((flags & FULLWIDTH) && (flags & COLOR)) {
		printf("%s%s%s%s%s%s%s%s%s\n",
		       SCROTUM_COLOR_ANSI, SCROTUM_CHAR_UTF8,
		       SHAFT_COLOR_ANSI,
		       repeat_string(SHAFT_CHAR_UTF8, length),
		       HEAD_COLOR_ANSI, HEAD_CHAR_UTF8,
		       EJAC_COLOR_ANSI,
		       repeat_string(EJAC_CHAR_UTF8, distance),
		       RESET_CODE_ANSI);
		return;
	}
#endif /* VP_USE_FULLWIDTH && VP_USE_COLOR_ANSI */

#ifdef VP_USE_FULLWIDTH
	if (flags & FULLWIDTH) {
		printf("%s%s%s%s\n",
		       SCROTUM_CHAR_UTF8,
		       repeat_string(SHAFT_CHAR_UTF8, length),
		       HEAD_CHAR_UTF8,
		       repeat_string(EJAC_CHAR_UTF8, distance));
		return;
	}
#endif /* VP_USE_FULLWIDTH */

#ifdef VP_USE_COLOR_ANSI
	if (flags & COLOR) {
		printf("%s%s%s%s%s%s%s%s%s\n",
		       SCROTUM_COLOR_ANSI, SCROTUM_CHAR,
		       SHAFT_COLOR_ANSI,
		       repeat_string(SHAFT_CHAR, length),
		       HEAD_COLOR_ANSI, HEAD_CHAR,
		       EJAC_COLOR_ANSI,
		       repeat_string(EJAC_CHAR, distance),
		       RESET_CODE_ANSI);
		return;
	}
#endif /* VP_USE_COLOR_ANSI */

	/* No flags */
	printf("%s%s%s%s\n",
	       SCROTUM_CHAR, repeat_string(SHAFT_CHAR, length),
	       HEAD_CHAR, repeat_string(EJAC_CHAR, distance));
	return;
}

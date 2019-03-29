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
 * independently inside another program or whatnot if desired */

static char *repeat_char(const char ch, unsigned int count)
{
	char *ret;

	ret = malloc(count + 1);
	strncpy(ret, &ch, 1);

	while (--count > 0)
		strncat(ret, &ch, 1);

	return ret;
}

void draw_penis(const unsigned int length, const unsigned int distance,
                const enum DRAW_FLAGS_E flags)
{
	printf("%c%s%c%s\n",
	       SCROTUM_CHAR, repeat_char(SHAFT_CHAR, length),
	       HEAD_CHAR, repeat_char(EJAC_CHAR, distance));
}

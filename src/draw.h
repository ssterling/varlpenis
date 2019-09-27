/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

/* Needed to get RAND_MIN and RAND_MAX */
#include <stdlib.h>

#ifndef VP_DRAW_H
#define VP_DRAW_H

#define LENGTH_MIN          1
#define LENGTH_MAX          RAND_MAX
#define DISTANCE_MIN        0
#define DISTANCE_MAX        RAND_MAX

/* These are arbitrary */
#define RAND_LENGTH_MIN     LENGTH_MIN
#define RAND_LENGTH_MAX     50
#define RAND_DISTANCE_MIN   DISTANCE_MIN
#define RAND_DISTANCE_MAX   12

#define SCROTUM_CHAR        '8'
#define SHAFT_CHAR          '='
#define HEAD_CHAR           'D'
#define EJAC_CHAR           '~'

#ifdef VP_USE_COLOR
#define SCROTUM_COLOR_ANSI  "\33[33m"       /* yellow */
#define SHAFT_COLOR_ANSI    "\33[1m\33[33m" /* bright yellow */
#define HEAD_COLOR_ANSI     "\33[1m\33[31m" /* bright red */
#define EJAC_COLOR_ANSI     "\33[1m\33[37m" /* bright white */
#define RESET_CODE_ANSI     "\33[0m"
#endif /* VP_USE_COLOR */

/* To avoid changing numbers in potential future expansion,
 * all flags will be compiled regardless of enabled features */
enum DRAW_FLAGS_E {
	NO_FLAGS = 0,
	COLOR = 1
};

static char *repeat_char(const char ch, unsigned int count);
void draw_penis(const unsigned int length, const unsigned int distance,
                const enum DRAW_FLAGS_E flags);

#endif /* ! VP_DRAW_H */

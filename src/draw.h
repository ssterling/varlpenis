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

/* Just in case it wasn't already explicitly defined,
 * `VP_USE_COLOR_<type>' should implicitly define `VP_USE_COLOR' */
#if (defined VP_USE_COLOR_ANSI || defined VP_USE_COLOR_WOE32) && \
  !defined VP_USE_COLOR
#warning `VP_USE_COLOR_<type>' is defined, but not `VP_USE_COLOR'; \
	`VP_USE_COLOR' will be implicitly defined for now
#define VP_USE_COLOR
#endif /* VP_USE_COLOR_<type> && ! VP_USE_COLOR */

/* And, if for some reason, `VP_USE_COLOR` is defined but no
 * `VP_USE_COLOR_<type>', throw an error */
#if defined VP_USE_COLOR && \
  !(defined VP_USE_COLOR_ANSI || defined VP_USE_COLOR_WOE32)
#warning `VP_USE_COLOR' is defined but no `VP_USE_COLOR_<type>'; \
	assuming `VP_USE_COLOR_ANSI'
#define VP_USE_COLOR_ANSI
#endif /* VP_USE_COLOR && ! VP_USE_COLOR_<type> */

#define LENGTH_MIN          1
#define LENGTH_MAX          RAND_MAX
#define DISTANCE_MIN        1
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

#ifdef VP_USE_COLOR_ANSI
#define SCROTUM_COLOR_ANSI  "\33[33m"       /* yellow */
#define SHAFT_COLOR_ANSI    "\33[1m\33[33m" /* bright yellow */
#define HEAD_COLOR_ANSI     "\33[1m\33[31m" /* bright red */
#define EJAC_COLOR_ANSI     "\33[1m\33[37m" /* bright white */
#define RESET_CODE_ANSI     "\33[0m"
#endif /* VP_USE_COLOR_ANSI */

#ifdef VP_USE_COLOR_WOE32
#define SCROTUM_COLOR_WOE32 6  /* yellow */
#define SHAFT_COLOR_WOE32   14 /* bright yellow */
#define HEAD_COLOR_WOE32    12 /* bright red */
#define EJAC_COLOR_WOE32    15 /* bright white */
#endif /* VP_USE_COLOR_WOE32 */

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

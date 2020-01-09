/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

/* Needed to get RAND_MIN and RAND_MAX */
#include <stdlib.h>

/* For colour definitions */
#ifdef VP_USE_COLOR_WOE32
#include <windows.h>
#endif /* VP_USE_COLOR_WOE32 */

#ifndef VP_DRAW_H
#define VP_DRAW_H

/* Fallback in case the user is using old Makefiles/docs/etc. */
#if defined(VP_USE_COLOR) && \
    (!defined(VP_USE_COLOR_ANSI) && !defined(VP_USE_COLOR_WOE32) && \
     !defined(VP_USE_COLOR_CONIO))
#warning "Using `VP_USE_COLOR' as a feature flag is deprecated.  " \
         "Assuming you meant `VP_USE_COLOR_ANSI'."
#define VP_USE_COLOR_ANSI
#endif /* VP_USE_COLOR && ! VP_USE_COLOR_[...] */

/* For `#if' directives which do not depend on the type of
 * colour output enabled (i.e. the usage message) */
#if !defined(VP_USE_COLOR) && \
    (defined(VP_USE_COLOR_ANSI) || defined(VP_USE_COLOR_WOE32) || \
     defined(VP_USE_COLOR_CONIO))
#define VP_USE_COLOR
#endif /* ! VP_USE_COLOR && VP_USE_COLOR_[...] */

/* TODO: check for more than one `VP_USE_COLOR_[...]' being defined */

#define LENGTH_MIN          1
#define LENGTH_MAX          RAND_MAX
#define DISTANCE_MIN        0
#define DISTANCE_MAX        RAND_MAX

/* These are arbitrary */
#define RAND_LENGTH_MIN     LENGTH_MIN
#define RAND_LENGTH_MAX     50
#define RAND_DISTANCE_MIN   DISTANCE_MIN
#define RAND_DISTANCE_MAX   12

#define SCROTUM_CHAR        "8"
#define SHAFT_CHAR          "="
#define HEAD_CHAR           "D"
#define EJAC_CHAR           "~"

#if defined(VP_USE_COLOR_ANSI)
#define SCROTUM_COLOR_ANSI  "\33[33m"       /* yellow */
#define SHAFT_COLOR_ANSI    "\33[1m\33[33m" /* bright yellow */
#define HEAD_COLOR_ANSI     "\33[1m\33[31m" /* bright red */
#define EJAC_COLOR_ANSI     "\33[1m\33[37m" /* bright white */
#define RESET_CODE_ANSI     "\33[0m"
#elif defined(VP_USE_COLOR_CONIO)

/* Accounting for Commodore colors in cc65 `conio.h' */
#if defined(__VIC20__)
#define SCROTUM_COLOR_CONIO 0x9 /* orange */
#define SHAFT_COLOR_CONIO   0x7 /* yellow */
#define HEAD_COLOR_CONIO    0xC /* light red */
#define EJAC_COLOR_CONIO    0x1 /* white */
#elif defined(__C64__) || defined(__C128__)
#define SCROTUM_COLOR_CONIO 0x8 /* orange */
#define SHAFT_COLOR_CONIO   0x8 /* yellow */
#define HEAD_COLOR_CONIO    0x2 /* red */
#define EJAC_COLOR_CONIO    0x1 /* white */
#else /* __VIC20__ || (__C64__ || __C128__)*/
/* Assume MS-DOS `conio.h' and/or VGA colour codes */
#define SCROTUM_COLOR_CONIO 0x6 /* yellow */
#define SHAFT_COLOR_CONIO   0xE /* bright yellow */
#define HEAD_COLOR_CONIO    0xC /* bright red */
#define EJAC_COLOR_CONIO    0xF /* bright white */
#endif /* __C64__ */

#elif defined(VP_USE_COLOR_WOE32)
#define SCROTUM_COLOR_WOE32 FOREGROUND_RED | FOREGROUND_GREEN
#define SHAFT_COLOR_WOE32   FOREGROUND_RED | FOREGROUND_GREEN | \
                            FOREGROUND_INTENSITY
#define HEAD_COLOR_WOE32    FOREGROUND_RED | FOREGROUND_INTENSITY
#define EJAC_COLOR_WOE32    FOREGROUND_RED | FOREGROUND_GREEN | \
			    FOREGROUND_BLUE | FOREGROUND_INTENSITY
#endif /* VP_USE_COLOR_[...] */

#ifdef VP_USE_FULLWIDTH
#define SCROTUM_CHAR_UTF8   "８"
#define SHAFT_CHAR_UTF8     "＝"
#define HEAD_CHAR_UTF8      "Ｄ"
#define EJAC_CHAR_UTF8      "～"
#endif /* VP_USE_FULLWIDTH */

/* To avoid changing numbers in potential future expansion,
 * all flags will be compiled regardless of enabled features */
enum DRAW_FLAGS_E {
	NO_FLAGS = 0,
	COLOR = 1,
	FULLWIDTH = 2
};

static char *repeat_string(const char *str, unsigned int count);
void draw_penis(const unsigned int length, const unsigned int distance,
                const enum DRAW_FLAGS_E flags);

#endif /* ! VP_DRAW_H */

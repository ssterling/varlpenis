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

#if defined VP_USE_COLOR && defined _WIN32
#include <windows.h>
#endif /* _VP_USE_COLOR && _WIN32 */

/* The `main()' function is 99% options-parsing and error-handling;
 * this file itself (and the corresponding `draw.h') can be utilised
 * independently inside another program or whatnot if desired */

static char *repeat_char(const char ch, unsigned int count)
{
	char *ret;

	if (count == 0) {
		ret = "\0";
		return ret;
	}

	ret = malloc(count + 1);
	strncpy(ret, &ch, 1);

	while (--count > 0)
		strncat(ret, &ch, 1);

	return ret;
}

void draw_penis(const unsigned int length, const unsigned int distance,
                const enum DRAW_FLAGS_E flags)
{
	/* Global variables for Winblows (when using color) */
#if defined VP_USE_COLOR && _WIN32
	HANDLE console;
	CONSOLE_SCREEN_BUFFER_INFO console_info;
	WORD original_attribs;
#endif /* VP_USE_COLOR && _WIN32 */

#ifdef VP_USE_COLOR_ANSI
	if (flags & COLOR)
		/* ANSI codes are indeed supported in the new Woe10 console,
		 * but they need to be enabled with a specific command first */
#ifdef _WIN32
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleMode(console, ENABLE_VIRTUAL_TERMINAL_PROCESSING);
#endif /* _WIN32 */

		printf("%s%c%s%s%s%c%s%s%s\n",
		       SCROTUM_COLOR_ANSI, SCROTUM_CHAR,
		       SHAFT_COLOR_ANSI, repeat_char(SHAFT_CHAR, length),
		       HEAD_COLOR_ANSI, HEAD_CHAR,
		       EJAC_COLOR_ANSI, repeat_char(EJAC_CHAR, distance),
		       RESET_CODE_ANSI);
	else
		printf("%c%s%c%s\n",
		       SCROTUM_CHAR, repeat_char(SHAFT_CHAR, length),
		       HEAD_CHAR, repeat_char(EJAC_CHAR, distance));
#elif defined VP_USE_COLOR_WOE32
	if (flags & COLOR)
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(console, &console_info);
		original_attribs = console_info.wAttributes;

		SetConsoleTextAttribute(console, SCROTUM_COLOR_WOE32);
		  printf("%s", SCROTUM_CHAR);
		SetConsoleTextAttribute(console, SHAFT_COLOR_WOE32);
		  printf("%s", repeat_char(SHAFT_CHAR, length));
		SetConsoleTextAttribute(console, HEAD_COLOR_WOE32);
		  printf("%s", HEAD_CHAR);
		SetConsoleTextAttribute(console, EJAC_COLOR_WOE32);
		  printf("%s", repeat_char(EJAC_CHAR, distance));
		SetConsoleTextAttribute(console, original_attribs);
		  printf("\n");
	else
		printf("%c%s%c%s\n",
		       SCROTUM_CHAR, repeat_char(SHAFT_CHAR, length),
		       HEAD_CHAR, repeat_char(EJAC_CHAR, distance));
#else /* VP_USE_COLOR_<type> */
	printf("%c%s%c%s\n",
	       SCROTUM_CHAR, repeat_char(SHAFT_CHAR, length),
	       HEAD_CHAR, repeat_char(EJAC_CHAR, distance));
#endif /* VP_USE_COLOR_<type> */
}

/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef VP_USE_COLOR_CONIO
#include <conio.h>
#endif /* VP_USE_COLOR_CONIO */

#ifdef VP_USE_COLOR_WOE32
#include <windows.h>
#endif /* VP_USE_COLOR_WOE32 */

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
#ifdef VP_USE_COLOR_CONIO
	struct text_info old_text_info;
#endif /* VP_USE_COLOR_CONIO */

#ifdef VP_USE_COLOR_WOE32
	HANDLE console;
	WORD old_console_attrs;
	CONSOLE_SCREEN_BUFFER_INFO csbi_info;

	console = GetStdHandle(STD_OUTPUT_HANDLE);
#endif /* VP_USE_COLOR_WOE32 */

#ifdef VP_USE_FULLWIDTH
#if defined(VP_USE_COLOR_ANSI)
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
#elif defined(VP_USE_COLOR_CONIO)
	if ((flags & FULLWIDTH) && (flags & COLOR)) {
		gettextinfo(&old_text_info);

		textcolor(SCROTUM_COLOR_CONIO);
		cprintf("%s", SCROTUM_CHAR_UTF8);
		textcolor(SHAFT_COLOR_CONIO);
		cprintf("%s", repeat_string(SHAFT_CHAR_UTF8, length));
		textcolor(HEAD_COLOR_CONIO);
		cprintf("%s", HEAD_CHAR_UTF8);
		textcolor(EJAC_COLOR_CONIO);
		cprintf("%s", repeat_string(EJAC_CHAR_UTF8, length));
		textcolor(old_text_info.attribute);
		return;
	}
#elif defined(VP_USE_COLOR_WOE32)
	if ((flags & FULLWIDTH) && (flags & COLOR)) {
		GetConsoleScreenBufferInfo(console, &csbi_info);
		old_console_attrs = csbi_info.wAttributes;

		SetConsoleTextAttribute(console, SCROTUM_COLOR_WOE32);
		printf("%s", SCROTUM_CHAR_UTF8);
		SetConsoleTextAttribute(console, SHAFT_COLOR_WOE32);
		printf("%s", repeat_string(SHAFT_CHAR_UTF8, length));
		SetConsoleTextAttribute(console, HEAD_COLOR_WOE32);
		printf("%s", HEAD_CHAR_UTF8);
		SetConsoleTextAttribute(console, EJAC_COLOR_WOE32);
		printf("%s", repeat_string(EJAC_CHAR_UTF8, length));
		SetConsoleTextAttribute(console, old_console_attrs);
		return;
	}
#endif /* VP_USE_COLOR_[...] */

	if (flags & FULLWIDTH) {
		printf("%s%s%s%s\n",
		       SCROTUM_CHAR_UTF8,
		       repeat_string(SHAFT_CHAR_UTF8, length),
		       HEAD_CHAR_UTF8,
		       repeat_string(EJAC_CHAR_UTF8, distance));
		return;
	}
#endif /* VP_USE_FULLWIDTH */

#if defined(VP_USE_COLOR_ANSI)
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
#elif defined(VP_USE_COLOR_CONIO)
	if (flags & COLOR) {
		gettextinfo(&old_text_info);

		textcolor(SCROTUM_COLOR_CONIO);
		cprintf("%s", SCROTUM_CHAR);
		textcolor(SHAFT_COLOR_CONIO);
		cprintf("%s", repeat_string(SHAFT_CHAR, length));
		textcolor(HEAD_COLOR_CONIO);
		cprintf("%s", HEAD_CHAR);
		textcolor(EJAC_COLOR_CONIO);
		cprintf("%s", repeat_string(EJAC_CHAR, length));
		textcolor(old_text_info.attribute);
		return;
	}
#elif defined(VP_USE_COLOR_WOE32)
	if (flags & COLOR) {
		GetConsoleScreenBufferInfo(console, &csbi_info);
		old_console_attrs = csbi_info.wAttributes;

		SetConsoleTextAttribute(console, SCROTUM_COLOR_WOE32);
		printf("%s", SCROTUM_CHAR);
		SetConsoleTextAttribute(console, SHAFT_COLOR_WOE32);
		printf("%s", repeat_string(SHAFT_CHAR, length));
		SetConsoleTextAttribute(console, HEAD_COLOR_WOE32);
		printf("%s", HEAD_CHAR);
		SetConsoleTextAttribute(console, EJAC_COLOR_WOE32);
		printf("%s", repeat_string(EJAC_CHAR, length));
		SetConsoleTextAttribute(console, old_console_attrs);
		return;
	}
#endif /* VP_USE_COLOR_[...] */

	/* No flags */
	printf("%s%s%s%s\n",
	       SCROTUM_CHAR, repeat_string(SHAFT_CHAR, length),
	       HEAD_CHAR, repeat_string(EJAC_CHAR, distance));
	return;
}

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
	char *scrotum_char;
	char *shaft_char;
	char *head_char;
	char *ejac_char;

#ifdef VP_USE_COLOR_CONIO
#if defined(__TURBOC__) || defined(__BORLANDC__)
	struct text_info old_text_info;
#endif /* __TURBOC__ || __BORLANDC__ */
	int old_text_color;
#endif /* VP_USE_COLOR_CONIO */

#ifdef VP_USE_COLOR_WOE32
	HANDLE console;
	WORD old_console_attrs;
	CONSOLE_SCREEN_BUFFER_INFO csbi_info;

	console = GetStdHandle(STD_OUTPUT_HANDLE);
#endif /* VP_USE_COLOR_WOE32 */

	/* Processing fullwidth independently of color
	 * prevents ungodly nested conditionals */
#ifdef VP_USE_FULLWIDTH
	if (flags & FULLWIDTH) {
		scrotum_char = SCROTUM_CHAR_UTF8;
		shaft_char = SHAFT_CHAR_UTF8;
		head_char = HEAD_CHAR_UTF8;
		ejac_char = EJAC_CHAR_UTF8;
	} else {
#endif /* VP_USE_FULLWIDTH */
		scrotum_char = SCROTUM_CHAR;
		shaft_char = SHAFT_CHAR;
		head_char = HEAD_CHAR;
		ejac_char = EJAC_CHAR;
#ifdef VP_USE_FULLWIDTH
	}
#endif /* VP_USE_FULLWIDTH */

#if defined(VP_USE_COLOR_ANSI)
	if (flags & COLOR) {
		printf("%s%s%s%s%s%s%s%s%s\n",
		       SCROTUM_COLOR_ANSI, scrotum_char,
		       SHAFT_COLOR_ANSI,
		       repeat_string(shaft_char, length),
		       HEAD_COLOR_ANSI, head_char,
		       EJAC_COLOR_ANSI,
		       repeat_string(ejac_char, distance),
		       RESET_CODE_ANSI);
		return;
	}
#elif defined(VP_USE_COLOR_CONIO)
	if (flags & COLOR) {
		/* Save current text color */
#if defined(__TURBOC__) || defined(__BORLANDC__)
		gettextinfo(&old_text_info);
		old_text_color = old_text_info.attribute;
#elif defined(__CC65__)
		old_text_color = (int)cpeekcolor(); /* at current cursor pos */
#endif /* (__TURBOC__ || __BORLANDC__) || __CC65__ */

		textcolor(SCROTUM_COLOR_CONIO);
		cprintf("%s", scrotum_char);
		textcolor(SHAFT_COLOR_CONIO);
		cprintf("%s", repeat_string(shaft_char, length));
		textcolor(HEAD_COLOR_CONIO);
		cprintf("%s", head_char);
		textcolor(EJAC_COLOR_CONIO);
		cprintf("%s", repeat_string(ejac_char, length));
		textcolor(old_text_color);
		return;
	}
#elif defined(VP_USE_COLOR_WOE32)
	if (flags & COLOR) {
		GetConsoleScreenBufferInfo(console, &csbi_info);
		old_console_attrs = csbi_info.wAttributes;

		SetConsoleTextAttribute(console, SCROTUM_COLOR_WOE32);
		printf("%s", scrotum_char);
		SetConsoleTextAttribute(console, SHAFT_COLOR_WOE32);
		printf("%s", repeat_string(shaft_char, length));
		SetConsoleTextAttribute(console, HEAD_COLOR_WOE32);
		printf("%s", head_char);
		SetConsoleTextAttribute(console, EJAC_COLOR_WOE32);
		printf("%s", repeat_string(ejac_char, length));
		SetConsoleTextAttribute(console, old_console_attrs);
		return;
	}
#endif /* VP_USE_COLOR_[...] */

	/* No flags */
	printf("%s%s%s%s\n",
	       scrotum_char, repeat_string(shaft_char, length),
	       head_char, repeat_string(ejac_char, distance));
	return;
}

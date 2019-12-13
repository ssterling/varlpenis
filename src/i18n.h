/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

#ifndef VP_I18N_H
#define VP_I18N_H

#ifdef VP_USE_GETTEXT

#include <libintl.h>
#include <locale.h>

#define _(STRING) gettext(STRING)

#define VP_TEXTDOMAIN "varlpenis"

/* Should be defined in Makefile, but this is here
 * as a backup to avoid compiler errors */
#ifndef VP_LOCALE_DIR
#define VP_LOCALE_DIR "/usr/local/share/locale"
#endif /* ! VP_LOCALE_DIR */

#else /* VP_USE_GETTEXT */

#define _(STRING) STRING

#endif /* VP_USE_GETTEXT */

#endif /* ! VP_I18N_H */

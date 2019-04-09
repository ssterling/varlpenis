/**
 * varlpenis - Generate ASCII-art penis of arbitrary length
 * Seth Price <https://www.gitlab.com/ssterling/varlpenis>
 *
 * See `LICENSE' file for copyright information.
 */

#ifndef VP_EXITS_H
#define VP_EXITS_H

/* If `sysexits.h' is available (and `VP_USE_SYSEXITS' is defined),
 * its exit values will be implemented.  Otherwise, standard
 * `0' on success and `1' on failure is used. */
#ifdef VP_USE_SYSEXITS

#include <sysexits.h>

#else /* ! VP_USE_SYSEXITS */

#define EX_OK       0
#define EX_USAGE    1      
#define EX_SOFTWARE 1

#endif /* ! VP_USE_SYSEXITS */

#endif /* ! VP_EXITS_H */

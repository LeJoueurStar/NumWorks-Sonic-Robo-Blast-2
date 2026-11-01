/* SRB2 pour NumWorks : configuration du build.
 * Complété au fur et à mesure, d'après les erreurs de compilation. */
#ifndef NW_CONFIG_H
#define NW_CONFIG_H

#define NOEXECINFO 1

/* newlib (la libc de la calculatrice) déclare strupr et strlwr en char *,
 * alors que SRB2 les déclare en int (doomtype.h). On charge newlib d'abord,
 * puis on renomme les deux fonctions de SRB2 pour éviter le conflit. */
#include <string.h>
#define strupr nw_strupr
#define strlwr nw_strlwr

/* stricmp et strnicmp (Windows/BSD) sont appelées sous ces noms par SRB2,
 * newlib les appelle strcasecmp et strncasecmp. */
#include <strings.h>
#define stricmp strcasecmp
#define strnicmp strncasecmp

#endif

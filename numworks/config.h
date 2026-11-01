/* SRB2 pour NumWorks : configuration du build.
 * Complété au fur et à mesure, d'après les erreurs de compilation. */
#ifndef NW_CONFIG_H
#define NW_CONFIG_H

#define NOEXECINFO 1

/* newlib (la libc de la calculatrice) déclare strupr et strlwr en char *,
 * alors que SRB2 les déclare en int (doomtype.h). On charge newlib d'abord,
 * puis on renomme les deux fonctions de SRB2 pour éviter le conflit.
 * La définition de string.c devient alors nw_strupr et nw_strlwr. */
#include <string.h>
#define strupr nw_strupr
#define strlwr nw_strlwr

#endif

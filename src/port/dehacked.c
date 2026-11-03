// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Port NumWorks : DEHACKED désactivé (fonctions vides)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//-----------------------------------------------------------------------------
/// \file  dehacked.c
/// \brief Stubs DEHACKED pour la calculatrice (les mods .soc ne sont pas chargés)

#include <stdarg.h>
#include <string.h>

#include "../doomdef.h"
#include "../dehacked.h"

boolean deh_loaded = false;

boolean gamedataadded = false;
boolean titlechanged = false;
boolean introchanged = false;
boolean bootmapchanged = false;

const char *luaactions[MAX_ACTION_RECURSION];
UINT8 luaactionstack = 0;

void DEH_LoadDehackedLump(lumpnum_t lumpnum)
{
	(void)lumpnum;
}

void DEH_LoadDehackedLumpPwad(UINT16 wad, UINT16 lump, boolean mainfile)
{
	(void)wad;
	(void)lump;
	(void)mainfile;
}

fixed_t get_number(const char *word)
{
	(void)word;
	return 0;
}

void deh_warning(const char *first, ...)
{
	(void)first;
}

void deh_strlcpy(char *dst, const char *src, size_t size, const char *warntext)
{
	(void)warntext;
	if (size == 0)
		return;
	strncpy(dst, src, size - 1);
	dst[size - 1] = '\0';
}

char *myfgets(char *buf, size_t bufsize, MYFILE *f)
{
	size_t n = 0;

	if (myfeof(f))
		return NULL;

	while (n + 1 < bufsize && !myfeof(f))
	{
		char c = *f->curpos++;
		buf[n++] = c;
		if (c == '\n')
			break;
	}
	buf[n] = '\0';
	return buf;
}

char *myhashfgets(char *buf, size_t bufsize, MYFILE *f)
{
	return myfgets(buf, bufsize, f);
}

void ignorelinesuntilhash(MYFILE *f)
{
	while (!myfeof(f))
	{
		char c = *f->curpos++;
		if (c == '\n' && !myfeof(f) && *f->curpos == '#')
			break;
	}
}

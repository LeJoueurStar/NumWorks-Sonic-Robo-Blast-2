// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Port NumWorks : recherche de fichiers (stubs)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//-----------------------------------------------------------------------------
/// \file  filesrch.c
/// \brief Recherche de fichiers : la calculatrice n'a pas de dossiers à parcourir

#include <string.h>

#include "../doomdef.h"
#include "../filesrch.h"

// Variables de menu des addons : aucune donnée, le menu reste vide
consvar_t cv_addons_option, cv_addons_folder, cv_addons_md5,
	cv_addons_showall, cv_addons_search_case, cv_addons_search_type;

#ifndef AVOID_ERRNO
int direrror = 0;
#endif

char menupath[1024] = "";
size_t menupathindex[menudepth];
size_t menudepthleft = 0;

char menusearch[MAXSTRINGLENGTH+1] = "";

char **dirmenu = NULL;
size_t sizedirmenu = 0;
size_t dir_on[menudepth];
UINT8 refreshdirmenu = 0;
char *refreshdirname = NULL;

filestatus_t filesearch(char *filename, const char *startpath, const UINT8 *wantedmd5sum,
	boolean completepath, int maxsearchdepth)
{
	(void)filename;
	(void)startpath;
	(void)wantedmd5sum;
	(void)completepath;
	(void)maxsearchdepth;
	return FS_NOTFOUND;
}

INT32 pathisdirectory(const char *path)
{
	(void)path;
	return 0;
}

INT32 samepaths(const char *path1, const char *path2)
{
	return strcmp(path1, path2) == 0;
}

INT32 concatpaths(const char *path, const char *startpath)
{
	(void)path;
	(void)startpath;
	return 0;
}

lumpinfo_t *getdirectoryfiles(const char *path, UINT16 *nlmp, UINT16 *nfolders)
{
	(void)path;
	if (nlmp) *nlmp = 0;
	if (nfolders) *nfolders = 0;
	return NULL;
}

void closefilemenu(boolean validsize)
{
	(void)validsize;
}

void searchfilemenu(char *tempname)
{
	(void)tempname;
}

boolean preparefilemenu(boolean samedepth)
{
	(void)samedepth;
	return false;
}

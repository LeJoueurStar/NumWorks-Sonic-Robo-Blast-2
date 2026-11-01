// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Port NumWorks : système (sans SDL)
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//-----------------------------------------------------------------------------
/// \file  i_system.c
/// \brief Système NumWorks : sortie, erreurs, fin de programme, mémoire, environnement

#include <setjmp.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <eadk.h>

#include "../doomdef.h"
#include "../d_main.h"
#include "../g_game.h"
#include "../i_sound.h"
#include "../i_system.h"
#include "../i_threads.h"
#include "../i_video.h"
#include "../m_misc.h"
#include "../netcode/d_net.h"
#include "../netcode/commands.h"
#include "../w_wad.h"
#include "epsilon_app.h"

/* Table des fonctions de sortie (dans la version SDL, elle est dans i_system.c) */
#define MAX_QUIT_FUNCS 16
static void (*quit_funcs[MAX_QUIT_FUNCS])(void);

/* Fonctions définies ailleurs dans le moteur, déclarées ici pour le compilateur */
void CL_AbortDownloadResume(void);
void M_FreePlayerSetupColors(void);
void I_ShutdownInput(void);

// Défini dans src/port/i_main.c : retour propre vers main() (voir plus bas)
extern jmp_buf np_quit_jmp;

// Budget de RAM d'une app NumWorks (environ 130 Ko, voir le Makefile)
#define NW_RAM_BUDGET (130 * 1024)

// Affichage du texte : à écrire dans i_video.c. Version vide par défaut,
// pour que le lien réussisse.
__attribute__((weak)) void NW_Print(const char *txt)
{
	(void)txt;
}

//
// Sortie de messages
//
void I_OutputMsg(const char *fmt, ...)
{
	char txt[256];
	va_list ap;

	va_start(ap, fmt);
	vsnprintf(txt, sizeof txt, fmt, ap);
	va_end(ap);

	NW_Print(txt);
}

//
// Démarrage et arrêt
//
INT32 I_StartupSystem(void)
{
	I_start_threads();
	I_AddExitFunc(I_stop_threads);
	return 0;
}

void I_ShutdownSystem(void)
{
	INT32 c;

	for (c = MAX_QUIT_FUNCS - 1; c >= 0; c--)
		if (quit_funcs[c])
			(*quit_funcs[c])();
}

void I_AddExitFunc(void (*func)())
{
	INT32 c;

	for (c = 0; c < MAX_QUIT_FUNCS; c++)
	{
		if (!quit_funcs[c])
		{
			quit_funcs[c] = func;
			break;
		}
	}
}

void I_RemoveExitFunc(void (*func)())
{
	INT32 c;

	for (c = 0; c < MAX_QUIT_FUNCS; c++)
	{
		if (quit_funcs[c] == func)
		{
			while (c < MAX_QUIT_FUNCS - 1)
			{
				quit_funcs[c] = quit_funcs[c + 1];
				c++;
			}
			quit_funcs[MAX_QUIT_FUNCS - 1] = NULL;
			break;
		}
	}
}

// Enregistre tout ce qui doit être sauvegardé, puis revient à main()
static void NW_ShutdownGame(void)
{
	M_SaveConfig(NULL);
	D_SaveBan();
	G_SaveGameData(clientGamedata);

	if (demorecording)
		G_CheckDemoStatus();
	if (metalrecording)
		G_StopMetalRecording(false);

	D_QuitNetGame();
	CL_AbortDownloadResume();
	M_FreePlayerSetupColors();
	I_ShutdownMusic();
	I_ShutdownSound();
	I_ShutdownGraphics();
	I_ShutdownInput();
	I_ShutdownSystem();
	W_Shutdown();
}

//
// Fin normale : revient à main(), qui appelle np_app_end()
//
void I_Quit(void)
{
	static boolean quiting = false;

	if (!quiting)
	{
		quiting = true;
		NW_ShutdownGame();
	}
	longjmp(np_quit_jmp, 1);
}

//
// Erreur fatale : affiche le message, sauvegarde, puis revient à main()
//
void I_Error(const char *error, ...)
{
	static boolean shutdowning = false;
	char buffer[256];
	va_list ap;

	va_start(ap, error);
	vsnprintf(buffer, sizeof buffer, error, ap);
	va_end(ap);

	I_OutputMsg("\nI_Error(): %s\n", buffer);

	if (!shutdowning)
	{
		shutdowning = true;
		NW_ShutdownGame();
	}
	longjmp(np_quit_jmp, 2);
}

//
// Fichiers et chemins : pas de système de fichiers hôte sur la calculatrice
//
void I_GetDiskFreeSpace(INT64 *freespace)
{
	*freespace = 1024 * 1024; // valeur indicative
}

INT32 I_mkdir(const char *dirname, INT32 unixright)
{
	(void)dirname;
	(void)unixright;
	return -1;
}

// Les données du jeu viennent de la flash (src/nw/data.S du portage Doom),
// pas d'un fichier srb2.pk3 cherché sur un disque. À adapter plus tard.
const char *I_LocateWad(void)
{
	return NULL;
}

//
// Environnement et utilisateur
//
char *I_GetUserName(void)
{
	return NULL;
}

char *I_GetEnv(const char *name)
{
	(void)name;
	return NULL;
}

INT32 I_PutEnv(char *variable)
{
	(void)variable;
	return -1;
}

const char *I_GetSysName(void)
{
	return "NumWorks";
}

//
// Presse-papiers : absent
//
INT32 I_ClipboardCopy(const char *data, size_t size)
{
	(void)data;
	(void)size;
	return -1;
}

const char *I_ClipboardPaste(void)
{
	return NULL;
}

//
// Aléatoire : générateur xorshift, graine tirée de l'horloge.
// Ce n'est pas un générateur cryptographique, mais le jeu n'en a pas besoin.
//
size_t I_GetRandomBytes(char *destination, size_t count)
{
	static UINT32 state = 0;
	size_t i;

	if (state == 0)
		state = (UINT32)eadk_timing_millis() | 1;

	for (i = 0; i < count; i++)
	{
		state ^= state << 13;
		state ^= state >> 17;
		state ^= state << 5;
		destination[i] = (char)(state & 0xFF);
	}
	return count;
}

//
// Mémoire : valeur fixe pour l'instant. À remplacer par une vraie mesure
// quand le tas du portage sera en place (étape 3).
//
size_t I_GetFreeMem(size_t *total)
{
	if (total)
		*total = NW_RAM_BUDGET;
	return NW_RAM_BUDGET;
}

const CPUInfoFlags *I_CPUInfo(void)
{
	return NULL;
}

//
// Divers
//
void I_RegisterSysCommands(void) {}
void I_BeginRead(void) {}
void I_EndRead(void) {}
void I_GetConsoleEvents(void) {}

void I_SetTextInputMode(boolean active)
{
	(void)active;
}

boolean I_GetTextInputMode(void)
{
	return false;
}

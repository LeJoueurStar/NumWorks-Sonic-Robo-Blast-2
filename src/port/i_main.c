// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Port NumWorks : point d'entrée du programme
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//-----------------------------------------------------------------------------
/// \file  i_main.c
/// \brief Point d'entrée NumWorks : protection Epsilon, puis D_SRB2Main et D_SRB2Loop

#include <setjmp.h>

#include "../doomdef.h"
#include "../m_argv.h"
#include "../d_main.h"
#include "../i_system.h"
#include "epsilon_app.h"

// Défini ici, utilisé par i_system.c pour revenir ici à la fin du jeu
jmp_buf np_quit_jmp;

int main(int argc, char **argv)
{
	myargc = argc;
	myargv = argv;

	np_app_begin();

	if (setjmp(np_quit_jmp) == 0)
	{
		CONS_Printf("Setting up SRB2...\n");
		D_SRB2Main();
		CONS_Printf("Entering main game loop...\n");
		D_SRB2Loop();
	}

	return np_app_end();
}

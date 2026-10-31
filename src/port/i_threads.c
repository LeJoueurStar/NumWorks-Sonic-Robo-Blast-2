// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Port NumWorks : un seul thread (stubs)
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  i_threads.c
/// \brief Threading stubs (single-threaded on NumWorks)

#include "doomtype.h"
#include "i_threads.h"

int  I_can_thread(void) { return 0; }
void I_start_threads(void) {}
void I_stop_threads(void) {}

int  I_spawn_thread(const char *name, I_thread_fn fn, void *userdata) { return 0; }
int  I_thread_is_stopped(void) { return 0; }

void I_lock_mutex(I_mutex *m) {}
void I_unlock_mutex(I_mutex m) {}

void I_hold_cond(I_cond *c, I_mutex m) {}
void I_wake_one_cond(I_cond *c) {}
void I_wake_all_cond(I_cond *c) {}

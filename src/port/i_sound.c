// SONIC ROBO BLAST 2
//-----------------------------------------------------------------------------
// Port NumWorks : son et musique désactivés (stubs)
//
// This program is free software distributed under the
// terms of the GNU General Public License, version 2.
// See the 'LICENSE' file for more details.
//-----------------------------------------------------------------------------
/// \file  i_sound.c
/// \brief Sound and music stubs (no audio on NumWorks)

#include "doomdef.h"
#include "i_sound.h"
#include "sounds.h"

UINT8 sound_started = 0;

// depuis src/sdl/i_sound.c (c'est une ligne consvar_t).

void *I_GetSfx(sfxinfo_t *sfx) { return NULL; }
void I_FreeSfx(sfxinfo_t *sfx) {}

void I_StartupSound(void) { sound_started = 0; }
void I_ShutdownSound(void) {}

INT32 I_StartSound(sfxenum_t id, UINT8 vol, UINT8 sep, UINT8 pitch, UINT8 priority, INT32 channel) { return -1; }
void I_StopSound(INT32 handle) {}
void I_UpdateSound(void) {}
boolean I_SoundIsPlaying(INT32 handle) { return false; }
void I_UpdateSoundParams(INT32 handle, UINT8 vol, UINT8 sep, UINT8 pitch) {}
void I_SetSfxVolume(UINT8 volume) {}

void I_InitMusic(void) {}
void I_ShutdownMusic(void) {}

musictype_t I_SongType(void) { return MU_NONE; }
boolean I_SongPlaying(void) { return false; }
boolean I_SongPaused(void) { return false; }

boolean I_SetSongSpeed(float speed) { return false; }

UINT32 I_GetSongLength(void) { return 0; }
boolean I_SetSongLoopPoint(UINT32 looppoint) { return false; }
UINT32 I_GetSongLoopPoint(void) { return 0; }
boolean I_SetSongPosition(UINT32 position) { return false; }
UINT32 I_GetSongPosition(void) { return 0; }

boolean I_LoadSong(char *data, size_t len) { return false; }
void I_UnloadSong(void) {}
boolean I_PlaySong(boolean looping) { return false; }
void I_StopSong(void) {}
void I_PauseSong(void) {}
void I_ResumeSong(void) {}
void I_SetMusicVolume(UINT8 volume) {}
boolean I_SetSongTrack(INT32 track) { return false; }

void I_SetInternalMusicVolume(UINT8 volume) {}
void I_StopFadingSong(void) {}
boolean I_FadeSongFromVolume(UINT8 target_volume, UINT8 source_volume, UINT32 ms, void (*callback)(void)) { return false; }
boolean I_FadeSong(UINT8 target_volume, UINT32 ms, void (*callback)(void)) { return false; }
boolean I_FadeOutStopSong(UINT32 ms) { return false; }
boolean I_FadeInPlaySong(UINT32 ms, boolean looping) { return false; }

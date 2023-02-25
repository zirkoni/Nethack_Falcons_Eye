#ifndef ALSOUND_H
#define ALSOUND_H

void al_sound_init();

void al_sound_play_midi(char*);
void al_sound_stop_midi();
int al_sound_is_music_playing();

void al_sound_load_wave(char *);
void al_sound_play_wave(char *);

#endif

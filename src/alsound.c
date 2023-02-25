#include "alsound.h"
#include <allegro.h>
#include <stdio.h>

#define DEFAULT_DIGI_VOLUME 250
#define DEFAULT_MIDI_VOLUME 120

MIDI* midi_music = 0;
extern volatile long midi_pos;

SAMPLE* the_sample;

void read_cfg(int* digi_vol, int* midi_vol)
{
    const char* filename = "./CONFIG/ALLEGRO.CFG";
    printf("Sound CFG file: %s\n", filename);
    FILE* fd = fopen(filename, "r");

    if(fd)
    {
        fscanf(fd, "%d", digi_vol);
        fscanf(fd, "%d", midi_vol);
        fclose(fd);
    } else
    {
        fd = fopen(filename, "w");
        if(fd)
        {
            fprintf(fd, "%d %d", *digi_vol, *midi_vol);
            fclose(fd);
        }
    }
}

void al_sound_init()
{
    int digi_volume = DEFAULT_DIGI_VOLUME;
    int midi_volume = DEFAULT_MIDI_VOLUME;
    allegro_init();

    if(install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0)
    {
        allegro_message("Error initialising sound system\n%s\n", allegro_error);
        exit(1);
    }

    read_cfg(&digi_volume, &midi_volume);
    printf("Sfx volume: %d\n", digi_volume);
    printf("Music volume: %d\n", midi_volume);
    set_volume(digi_volume, midi_volume);
}

void al_sound_play_midi(char* midifilename)
{
    midi_music = load_midi(midifilename);

    if(midi_music)
    {
        static const int loop = FALSE;
        play_midi(midi_music, loop);
    }
}

void al_sound_stop_midi()
{
    destroy_midi(midi_music);
    midi_music = 0;
}

int al_sound_is_music_playing()
{
    return (midi_pos > 0);
}

void al_sound_load_wave(char* wavefilename)
{
    // Load and store all samples. ???
}

void al_sound_play_wave(char* wavefilename)
{
    static const int vol = 255;
    static const int pan = 128;
    static const int pitch = 1000;
    static const int loop = FALSE;

    destroy_sample(the_sample); // we have to do this here to avoid memory leaks
    the_sample = load_sample(wavefilename);

    if(the_sample)
    {
        play_sample(the_sample, vol, pan, pitch, loop);
    }
}

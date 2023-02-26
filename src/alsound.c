#include "alsound.h"
#include <allegro.h>
#include <stdio.h>

#define DEFAULT_DIGI_VOLUME 250
#define DEFAULT_MIDI_VOLUME 120
#define MAX_NUM_SAMPLES     16

MIDI* midi_music = 0;
extern volatile long midi_pos;

SAMPLE* samples[MAX_NUM_SAMPLES];
int num_wave_files = 0;

// Linked list
struct file_node
{
    char* filename;
    struct file_node* next;
};

struct file_node* first_node = NULL;


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

void load_new_wavefile(char* wavefilename)
{
    samples[num_wave_files] = load_sample(wavefilename);

    int len = strlen(wavefilename);
    struct file_node* new_node = malloc(sizeof(struct file_node));
    new_node->filename = malloc(len);
    strcpy(new_node->filename, wavefilename);
    new_node->next = NULL;

    // Insert at the end of linked list
    if(first_node == NULL)
    {
        first_node = new_node;
    } else
    {
        struct file_node* last_node = first_node;
        while(last_node->next != NULL)
        {
            last_node = last_node->next;
        }

        last_node->next = new_node;
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

void al_sound_close()
{
    int i;
    for(i = 0; i < num_wave_files; ++i)
    {
        destroy_sample(samples[i]);
    }
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

void al_sound_load_wave(char* wavefilename, int* index)
{
    if(num_wave_files < MAX_NUM_SAMPLES)
    {
        int i;
        struct file_node* node = first_node;
        for(i = 0; i < num_wave_files; ++i)
        {
            // Do not load again same files
            if(strcmp(wavefilename, node->filename) == 0)
            {
                *index = i;
                return;
            }

            node = node->next;
        }

        *index = num_wave_files;
        load_new_wavefile(wavefilename);
        ++num_wave_files;
    } else
    {
        printf("ERROR: Max %d samples supported. Exiting...\n", MAX_NUM_SAMPLES);
        exit(1);
    }
}

void al_sound_load_wave_finish()
{
    // File list can be freed after all samples are loaded in samples[]
    /*struct file_node* to_remove;
    while(first_node)
    {
        to_remove = first_node;
        first_node = to_remove->next;
        free(to_remove->filename);
        free(to_remove);
    }*/
}

void al_sound_play_wave(char* wavefilename, int index)
{
    static const int vol = 255;
    static const int pan = 128;
    static const int pitch = 1000;
    static const int loop = FALSE;

    if(index < MAX_NUM_SAMPLES && samples[index]) // sanity checks
    {
        play_sample(samples[index], vol, pan, pitch, loop);
    }
}

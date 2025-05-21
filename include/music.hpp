#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <list>
#include <string>
#include "sound.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/**
 * @class Music
 * 
 * @brief represents a sound in a more complex way, 
 * with pause and playback methods with fade-in and fade-out systems.
 */

class Music : public Sound {
private:
    ALLEGRO_SAMPLE_INSTANCE* music_sample;      // Music object (more complex than the sample)

    float ballast_volume;                       // Save the default volume
    float volume;                               // Reference volume at which the system follows
    float current_volume;                       // Real-time volume

    unsigned int current_music_position;        // Position at which the music was paused

    float fade_speed;                           // Fade-in and fade-out speed

    static std::list <Music*> music_address;    // Music addresses to have their volumes updated, with fade-in and fade-out

public:
    Music(const char* sound_address, float ballast_volume_parameter=4.0, float fade_speed_parameter=0.4);        
    ~Music() override;                          // If the destroyer of music is called, the destroyer of sound will not be called
    
    void play();                                // Method of playing music
    void pause();                               // Method to pause music

    static void update_fade_in_fade_out();      // Method to do fade-in and fade-out
};

#endif

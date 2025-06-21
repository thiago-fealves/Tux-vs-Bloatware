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
    ALLEGRO_SAMPLE_INSTANCE* music_sample = nullptr;      // Music object (more complex than the sample)

    float ballast_volume;                       // Save the default volume
    float volume = 0;                               // Reference volume at which the system follows
    float current_volume = 0;                       // Real-time volume

    unsigned int current_music_position = 0;        // Position at which the music was paused

    float fade_speed;                           // Fade-in and fade-out speed

    static std::list <Music*> music_address;    // Music addresses to have their volumes updated, with fade-in and fade-out

    static Music* lastMusicPlayed;

public:
    Music(const char* sound_address, float volume_parameter=0.6f, float fade_speed_parameter=2.0f);        
    ~Music() override;                          // If the destroyer of music is called, the destroyer of sound will not be called
    
    void play();                                // Method of playing music
    void pause();                               // Method to pause music

    static void update_fade_in_fade_out();      // Method to do fade-in and fade-out
    static void muteMusic();
    static void unMuteMusic();
};

#endif

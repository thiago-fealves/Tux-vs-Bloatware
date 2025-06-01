#ifndef SOUND_HPP
#define SOUND_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/** 
 * @class Sound
 * @brief class that represents a simple sound, with a musical object, ALLEGRO_SAMPLE,
 * and a play method.
 * 
*/

class Sound {
    
protected:
    ALLEGRO_SAMPLE* sound_sample = nullptr;     // Simple music object

public:
    Sound(const char* sound_address);           // Build the sound
    virtual ~Sound();                           // Destroy the sound
    void play(float gain=4.0);                  // Play the sound
};


#endif
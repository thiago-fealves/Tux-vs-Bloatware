#include "sound.hpp"
#include <iostream>

/** 
 * @class Sound
 * @brief class that represents a simple sound, with a musical object, ALLEGRO_SAMPLE,
 * and a play method.
 * 
*/

/**
 * @brief Starts and checks the allegro audio systems and reserves an audio channel.
 * 
 * @return Returns whether the initializations were successful.
 */
//era aqui o 

/**
 * @brief Construct a sound.
 * 
 * @param sound_address The address of the sound.
*/
Sound::Sound(const char* sound_address) {

    // Creates an ALLEGRO_SAMPLE and inserts it into sound_sample
    sound_sample = al_load_sample(sound_address);

    // Check if sound_sample was created
    if(sound_sample == nullptr) std::cout << "There was a problem reading the sound address\n";

}

/**
 * @brief Destroys the sound.
 */
Sound::~Sound() {
    // Check if the sound exists
    if(sound_sample == nullptr) return;

    // Destroy the ALLEGRO_SAMPLE
    al_destroy_sample(sound_sample);
}

/**
 * @brief Create and play a new sound.
 * 
 * @param volume Volume at which the new sound will play.
 */
void Sound::play(float volume) {

    // Check if the sound exists
    if(sound_sample == nullptr) {  
        std::cout << "The sound was not loaded successfully\n";
        return;
    }

    // Create and play a new sound
    al_play_sample(sound_sample, volume, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
}

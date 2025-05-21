#include "sound.hpp"
#include <iostream>

/** 
 * @class Sound
 * @brief class that represents a simple sound, with a musical object, ALLEGRO_SAMPLE,
 * and a play method.
 * 
*/

bool Sound::audio_sys_has_been_initialized = false;

bool Sound::file_exists(const char* path) {
    return (access(path, F_OK) == 0);
}

/**
 * @brief Starts and checks the allegro audio systems and reserves an audio channel.
 * 
 * @return Returns whether the initializations were successful.
 */
bool Sound::initialize_sys_sound() {

    // Install and check the allegro audio system
    if(al_install_audio() == false) {
        std::cout << "The Allegro audio system could not be installed\n";
        return false;
    }

    // Loads and checks, the audio file handlers (e. g., .ogg)
    if(al_init_acodec_addon() == false) {
        std::cout << "Unable to load audio handlers\n";
        return false;
    }

    // Reserves and checks 32 audio channels for ALLEGRO
    if(al_reserve_samples(32) == false) {
        std::cout << "Unable to reserve audio channels\n";
        return false;
    }

    // If everything goes well
    Sound::audio_sys_has_been_initialized = true;
    return true;
}

/**
 * @brief Construct a sound.
 * 
 * @param sound_address The address of the sound.
*/
Sound::Sound(const char* sound_address) : sound_sample(nullptr) {

    // Check if the audio system has been started
    if(Sound::audio_sys_has_been_initialized == false) { // If it wasn't, then it is initialized
        if(Sound::initialize_sys_sound() == true) { 
            Sound::audio_sys_has_been_initialized = true;
        } else {
            std::cout << "The audio sys could not be initialized\n"; 
            return;
        }
    }

    // Check if the audio file exists
    if(Sound::file_exists(sound_address) == false) {
        std::cout << "This file do not exist, " << sound_address << std::endl;
        return;
    } 

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

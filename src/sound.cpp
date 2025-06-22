#include "sound.hpp"
#include "bootstrap.hpp"
#include <iostream>

bool Sound::isSoundMuted = false;
float Sound::volumeMester = 1.0f;

/** 
 * @class Sound
 * @brief class that represents a simple sound, with a musical object, ALLEGRO_SAMPLE,
 * and a play method.
 * 
*/

/**
 * @brief Construct a sound.
 * 
 * @param sound_address The address of the sound.
*/
Sound::Sound(const char* sound_address) {
    
    if(!Bootstrap::file_exists(sound_address)) {
        std::cout << "Arquivo de som/musica nao encontrado: " << sound_address << "\n";
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

    if(Sound::isSoundMuted==true) return;

    // Create and play a new sound
    al_play_sample(sound_sample, volume*Sound::volumeMester, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, nullptr);
}

/**
 * @brief Disables sounds and mutes music.
 */
void Sound::muteSounds() {
    Sound::isSoundMuted = true; // Does not allow sounds to play
    Music::muteMusic(); // Make the current music stop playing
}

/**
 * @brief Enables sounds and plays music.
 */
void Sound::unmuteSounds() {
    Sound::isSoundMuted = false; // Enable sounds
    Music::unMuteMusic(); // Play the last song you tried or played
}
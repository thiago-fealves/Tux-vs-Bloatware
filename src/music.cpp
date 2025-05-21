#include "music.hpp"
#include <iostream>

/**
 * @class Music
 * 
 * @brief represents a sound in a more complex way, 
 * with pause and playback methods with fade-in and fade-out systems.
 */

std::list<Music*> Music::music_address; // Initialize the music list

/**
 * @brief Construct a music.
 * 
 * @param sound_address The address of the music.
 * @param ballast_volume_parameter Initializes the ballast_volume of the object.
 * @param fade_speed_parameter Initializes the fade_speed of the object.
 */
Music::Music(const char* sound_address, float ballast_volume_parameter, float fade_speed_parameter) : Sound(sound_address), music_sample(nullptr), 
        ballast_volume(ballast_volume_parameter), volume(0.0), current_volume(0.0), current_music_position(0), fade_speed(fade_speed_parameter) {
    
    // Check if sound_sample, of Sound, has been started
    if(sound_sample == nullptr) {
        std::cout << "The sound sample does not exist, problem in the sound builder\n";
        return;
    }

    // Transform an ALLEGRO SAMPLE into an ALLEGRO SAMPLE INSTANCE (a more complex form of sample)
    music_sample = al_create_sample_instance(sound_sample);

    // Check if music_sample has been started
    if(music_sample == nullptr) {
        std::cout << "There is a problem with creating the music sample, in 'al_create_sample_instance'\n";
        return;
    }

    al_set_sample_instance_gain(music_sample, 0.0);                             // Set the volume to 0.0
    al_set_sample_instance_playmode(music_sample, ALLEGRO_PLAYMODE_LOOP);       // Set the play mode to lool
    al_attach_sample_instance_to_mixer(music_sample, al_get_default_mixer());   // Couples music_sample to an automatic mixer
    al_set_sample_instance_playing(music_sample, false);                        // Stops the music, because the mixer plays music

    //Add the song to the end of the song list
    Music::music_address.push_back(this); 
}


/**
 * @brief Destroy the music. (If the destroyer of music is called, the destroyer of sound will not be called,
 * because ALLEGRO SAMPLE INSTANCE is just a more robust ALLEGRO SAMPLE, when we destroy ALLEGRO SAMPLE INSTANCE
 * the ALLEGRO SAMPLE is destroyed together.)
 */
Music::~Music() {

    // Check if the music exists
    if(music_sample == nullptr) return; 

    // Destroy the ALLEGRO_SAMPLE_INSTANCE
    al_destroy_sample_instance(music_sample);

    // Remove it from the song list
    Music::music_address.remove(this);
}

/**
 * @brief Pause the music, setting the volume to zero.
 */
void Music::pause() {

    // Check if the music exists and if the music is playing
    if(music_sample == nullptr && al_get_sample_instance_playing(music_sample) == false) return;

    volume = 0.0;
}

/**
 * @brief Play the music, starting where it left off.
 */
void Music::play() {
    volume = ballast_volume;                                                // Return the volume to the original value  
    al_set_sample_instance_position(music_sample, current_music_position);  // Put the music back on the instant it stopped
    al_set_sample_instance_playing(music_sample, true);                     // Play the music
}

/**
 * @brief Performs fade-in and fade-out (this method must be called cyclically to work correctly)
 */
void Music::update_fade_in_fade_out() {
    // Enter each active song
    for(auto it : Music::music_address) {
        // Check if the music is nullptr OR already has a stable volume
        if (it==nullptr || it->volume == it->current_volume) continue; 

        // Check if it is a case of a fade-in
        if(it->volume > it->current_volume) {
            it->current_volume += it->fade_speed;                                   // Increases the current_volume by one unit of fade_speed

            // Checks whether the current volume has already reached the ballast volume
            if(it->current_volume>=it->volume) {
                it->current_volume = it->volume; // Set the current volume to the ballast volume, as the current volume may be larger
            }

        
        }
        // Check if it is a case of a fade-out
         else if (it->volume == 0.0) { 
            it->current_volume -= it->fade_speed;  // Decrease the current_volume by one unit of fade_speed

            // Checks whether the current volume has already reached the ballast volume(zero in this case)
            if(it->current_volume<=0) {
                al_set_sample_instance_gain(it->music_sample, 0.0);                             // Set the music volume to zero
                it->current_music_position = al_get_sample_instance_position(it->music_sample); // Saves the current position of the song
                al_set_sample_instance_playing(it->music_sample, false);                        // Makes the music stop playing
                it->current_volume = 0.0;                                                       // Set the current volume to the zero, as the current volume may be smaller
            }
        }

        al_set_sample_instance_gain(it->music_sample, it->current_volume); // Set the music volume to the current volume (increased or decrease)

    }
}

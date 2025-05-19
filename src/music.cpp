#include "music.hpp"
#include <iostream>

bool Sound::audio_sys_has_been_initialized = false;

bool Sound::initialize_sys_sound() {
    //CONFERIR AQUI A EXISTEMCIA DOS AUDIOS NAS PASTAS
    // Inicia e verifica os sistemas de audio do allegro E reserva um canal de audio 
    
    if(al_install_audio() && al_init_acodec_addon() && al_reserve_samples(16)) {
        Sound::audio_sys_has_been_initialized = true;
        return true;
    } else {
        std::cout << "An error occurred with the initialization of the ALLEGRO audio systems" << std::endl;
        Sound::audio_sys_has_been_initialized = false;
        return false;
    } 
}

Sound::Sound(std::string sound_address, float gain) {
    if(!Sound::audio_sys_has_been_initialized) {
        std::cout << "The audio system has not been initialized" << std::endl;
        return;
    }

    stream = al_load_audio_stream(sound_address.c_str(), 4, 2048);
    al_set_audio_stream_playmode(stream, ALLEGRO_PLAYMODE_ONCE);
    al_set_audio_stream_gain(stream, gain);
}

Sound::~Sound() {
    al_detach_audio_stream(stream); //Desacopla o voice, junto com a sua liberacao
    al_destroy_audio_stream(stream); //Destroi o stream
}

void Sound::play() {
    if(!stream) {
        std::cout << "Stream esta vazia" << std::endl;
        return;
    }
    // Starts the music
    al_attach_audio_stream_to_mixer(stream,al_get_default_mixer());
}

Music::Music(std::string sound_address, float gain_param) : Sound(sound_address, 0.0), gain(gain_param), standart_gain(gain_param), current_gain(0.0) {
    if(!stream) std::cout << "Falha na inicializacao do ALLEGRO_AUDIO_STREAM" << std::endl;
    else {
        // Define the play mode as loop
        al_set_audio_stream_playmode(stream, ALLEGRO_PLAYMODE_LOOP);
    }
}

Music::~Music() {
    al_detach_audio_stream(stream); //Desacopla o voice, junto com a sua liberacao
    al_destroy_audio_stream(stream); //Destroi o stream
}

void Music::pause() {
    gain = 0.0;
}

void Music::resume() {
    gain = standart_gain;
    al_set_audio_stream_playing(stream, true);
}

void Music::set_gain(float gain) {
    if (gain<7.0) {
        this->gain = gain;
        standart_gain = gain;
    } else std::cout << "The gain is greater than 7.0" << std::endl;
}

void Music::fade_in(float rate) {
    current_gain += rate;
    if(current_gain>=gain) {
        current_gain = gain;
        al_set_audio_stream_gain(stream, current_gain);
        return;
    }
    al_set_audio_stream_gain(stream, current_gain);
}

void Music::fade_out(float rate) {
    current_gain -= rate;
    if(current_gain<=0) {
        current_gain = 0.0;
        al_set_audio_stream_gain(stream, current_gain);
        al_set_audio_stream_playing(stream, false);
        return;
    }
    al_set_audio_stream_gain(stream, current_gain);
}

void Music::music_update() {
    if (!stream || gain==current_gain) return;

    float t = 0.085;

    if(gain > current_gain) fade_in(t);
    else if (gain < current_gain) fade_out(t); 
}

#include "sound.hpp"
#include <iostream>

bool Sound::file_exists(const std::string& caminho) {
    return (access(caminho.c_str(), F_OK) == 0);
}

std::list<ALLEGRO_AUDIO_STREAM*> Sound::active_sounds;

bool Sound::audio_sys_has_been_initialized = false;

bool Sound::initialize_sys_sound() {
    //CONFERIR AQUI A EXISTEMCIA DOS AUDIOS NAS PASTAS
    // Inicia e verifica os sistemas de audio do allegro E reserva um canal de audio 
    
    if(al_install_audio() && al_init_acodec_addon() && al_reserve_samples(16)) {
        Sound::audio_sys_has_been_initialized = true;
        return true;
    } else {
        std::cout << "An error occurred with the initialization of the ALLEGRO audio systems" << std::endl;
        return false;
    } 
}

Sound::Sound(std::string sound_address_param) : sound_address(sound_address_param) {

    if(!Sound::audio_sys_has_been_initialized) {
        std::cout << "The audio system has not been initialized" << std::endl;
        return;
    }

    if(!Sound::file_exists(sound_address)) {
        std::cout << "This file do not exist, " << sound_address << std::endl;
        return;
    } 
}

void Sound::play(float gain) {
    ALLEGRO_AUDIO_STREAM* new_stream = al_load_audio_stream(sound_address.c_str(), 4, 2048);

    if(!new_stream) {
        std::cout << "Erro em carregar a nova stream paralela" << std::endl;
        return;
    }

    al_set_audio_stream_playmode(new_stream, ALLEGRO_PLAYMODE_ONCE);
    al_set_audio_stream_gain(new_stream, gain);
    al_attach_audio_stream_to_mixer(new_stream, al_get_default_mixer());

    Sound::active_sounds.push_back(new_stream);
}

void Sound::clean_sounds(bool cleanup_all) {
    ALLEGRO_AUDIO_STREAM *stream = nullptr;
    for(auto it = Sound::active_sounds.begin(); it != Sound::active_sounds.end();) {
        stream = *it;
        if (stream && (!al_get_audio_stream_playing(stream) || cleanup_all)) {
            al_drain_audio_stream(stream);
            al_detach_audio_stream(stream);
            al_destroy_audio_stream(stream);
            it = Sound::active_sounds.erase(it);  // remove e já aponta para o próximo
        } else ++it;  // só avança se nao removeu nada 
    }    
} 
    

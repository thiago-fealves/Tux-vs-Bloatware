#include "music.hpp"
#include <iostream>

Music::Music(std::string sound_address, float gain, size_t fragments, unsigned int samples) : stream(nullptr) {

    //Initialize the "music_exist" with false
    music_exist=false;

    //Initialize gain and current_gain
    this->gain = gain;
    standart_gain = gain;
    current_gain = 0.0;

    //Inicia e verifica os sistemas de audio do allegro
    if(!al_install_audio() || !al_init_acodec_addon()) std::cout << "Falha ao inicializar o sistema de audio" << std::endl;
    
    //Reserva um canal de audio 
    if(!al_reserve_samples(1)) std::cout << "Error reserving audio channel" << std::endl;

    //Inicializa o ALLEGRO_AUDIO_STREAM
    stream = al_load_audio_stream(sound_address.c_str(), fragments, samples);
    if(!stream) std::cout << "Falha na inicializacao do ALLEGRO_AUDIO_STREAM" << std::endl;
    
    //Vincula o stream a um mixer que o gerencia de forma automtica
    //Successfully linking, then "music_exist" becomes true
    if(al_attach_audio_stream_to_mixer(stream,al_get_default_mixer())) music_exist=true;
}

Music::~Music() {
    if(stream) { //Verifica se stream existe
        al_detach_audio_stream(stream); //Desacopla o voice, junto com a sua liberacao
        al_destroy_audio_stream(stream); //Destroi o stream
    }
}


void Music::play() {
    if(music_exist) {
        al_set_audio_stream_playmode(stream, ALLEGRO_PLAYMODE_LOOP);
        al_set_audio_stream_gain(stream, current_gain);
    }
}

void Music::pause() {
    if(!music_exist) return;
    gain = 0.0;
}

void Music::resume() {
    if(!music_exist) return;
    gain = standart_gain;
    al_set_audio_stream_playing(stream, true);
}

void Music::speed(float speed) {
    if (music_exist && speed) al_set_audio_stream_speed(stream, speed);
}

void Music::set_gain(float gain) {
    if (music_exist && gain<7.0) {
        this->gain = gain;
        standart_gain = gain;
    } else std::cout << "The stream does not exist OR the gain is greater than 7.0" << std::endl;
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
    
    if (!music_exist || gain==current_gain) return;
    float t = 0.085;

    if(gain > current_gain) fade_in(t);
    else if (gain < current_gain) fade_out(t); 


}

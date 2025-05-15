#include "music.hpp"
#include <iostream>

Music::Music(std::string sound_address, size_t fragments, unsigned int samples) : stream(nullptr) {
    //Inicia e verifica os sistemas de audio do allegro
    if(!al_install_audio() || !al_init_acodec_addon()) std::cout << "Falha ao inicializar o sistema de audio" << std::endl;
    
    //Reserva um canal de audio 
    al_reserve_samples(1); 

    //Inicializa o ALLEGRO_AUDIO_STREAM
    stream = al_load_audio_stream(sound_address.c_str(), fragments, samples);
    if(!stream) std::cout << "Falha na inicializacao do ALLEGRO_AUDIO_STREAM" << std::endl;

    //Vincula o stream a um mixer que o gerencia de forma automtica
    al_attach_audio_stream_to_mixer(stream,al_get_default_mixer());

}

Music::~Music() {
    if(stream) { //Verifica se stream existe
        al_detach_audio_stream(stream); //Desacopla o voice, junto com a sua liberacao
        al_destroy_audio_stream(stream); //Destroi o stream
    }
}

void Music::play() {
    if(stream) {
        al_set_audio_stream_playmode(stream, ALLEGRO_PLAYMODE_LOOP);
        al_set_audio_stream_gain(stream, 1.0);
    }
}

void Music::pause() {
    if(stream) {
        al_set_audio_stream_gain(stream, 0.0);
    }
}

#include "music.hpp"
#include <iostream>

std::list<Music*> Music::music_address;

Music::Music(std::string sound_address, float rate_param) : Sound(sound_address), gain(0.0), current_gain(0.0), rate(rate_param) {

    stream = al_load_audio_stream(sound_address.c_str(), 4, 2048);
    if(!stream) {
        std::cout << "Erro na inicialização da musica, provavelmente é o endereço. \n";
        return;
    }
    // Define the play mode as loop
    al_set_audio_stream_playmode(stream, ALLEGRO_PLAYMODE_LOOP);

    al_set_audio_stream_gain(stream, 0.0);//nao sei se precisa disso
    al_attach_audio_stream_to_mixer(stream,al_get_default_mixer());
    al_set_audio_stream_playing(stream, false);

    //Adiciona a musica no final da lista
    Music::music_address.push_back(this); 
}

Music::~Music() {
    if(!stream) return; 
    al_drain_audio_stream(stream); 
    al_detach_audio_stream(stream);
    al_destroy_audio_stream(stream); // Destroi o stream
    Music::music_address.remove(this);
}

void Music::pause() {
    gain = 0.0;
}

void Music::play(float gain) {
    standart_gain = gain;
    this->gain = gain;
    al_set_audio_stream_playing(stream, true);
}

void Music::music_update() {
    for(auto i : Music::music_address) {// Entrar em cada musica ativa
        if (!i || i->gain==i->current_gain) continue; // Não precisa fazer nada

        if(i->gain > i->current_gain) { // FADE-IN
            i->current_gain += i->rate;
            if(i->current_gain>=i->gain) {
                i->current_gain = i->gain;
                al_set_audio_stream_gain(i->stream, i->current_gain);
                return;
            }
            al_set_audio_stream_gain(i->stream, i->current_gain);

        } else if (i->gain < i->current_gain) { // FADE-OUT
            i->current_gain -= i->rate;
            if(i->current_gain<=0) {
                i->current_gain = 0.0;
                al_set_audio_stream_gain(i->stream, i->current_gain);
                al_set_audio_stream_playing(i->stream, false);
                return;
            }
            al_set_audio_stream_gain(i->stream, i->current_gain);
        }
    }
}
#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <list>
#include <string>
#include "sound.hpp"
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>


class Music : public Sound {
private:
    ALLEGRO_AUDIO_STREAM *stream;

    float gain;
    float standart_gain;
    float current_gain;
    float rate;

    static std::list <Music*> music_address;

public:
    Music(std::string sound_address, float rate=0.5);
    ~Music();
    

    static void music_update();
    void play(float gain=4.0) override;
    void pause();
};

#endif

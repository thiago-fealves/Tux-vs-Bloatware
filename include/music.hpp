#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Music {
private:
    std::string address;
    ALLEGRO_AUDIO_STREAM *stream;

    float standart_gain;
    float gain;
    float current_gain;

    Music(std::string sound_address, float gain=4.0);

    bool music_exist;

    void fade_in(float rate);
    void fade_out(float rate);

public:

    static Music* music_initialze(std::string sound_address);

    ~Music();

    void play();
    void pause();
    void resume();
    void speed(float speed);
    void set_gain(float gain);


    void music_update();
};

#endif

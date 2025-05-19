#ifndef SOM_HPP
#define SOM_HPP

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Sound {
protected:
    ALLEGRO_AUDIO_STREAM *stream;
    static bool audio_sys_has_been_initialized;

public:
    Sound(std::string sound_address, float gain=4.0);
    ~Sound();

    static bool initialize_sys_sound();
    void play();
};

class Music : public Sound {
private:
    float gain;
    float standart_gain;
    float current_gain;

    void fade_in(float rate);
    void fade_out(float rate);

public:
    Music(std::string sound_address, float gain=4.0);
    ~Music();

    void pause();
    void resume();
    void set_gain(float gain);
    void music_update();
};

#endif

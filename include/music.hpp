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

public:
    Music(std::string sound_address, size_t fragments=4, unsigned int samples=2048);
    ~Music();

    void play();
    void pause();
    
};

#endif

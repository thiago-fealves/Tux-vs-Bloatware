#ifndef SOUND_HPP
#define SOUND_HPP

#include <string>
#include <list>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class Sound {
private:
    std::string sound_address;

    static bool file_exists(const std::string& caminho);

    static std::list<ALLEGRO_AUDIO_STREAM*> active_sounds;

protected:
    static bool audio_sys_has_been_initialized;
    
public:
    Sound(std::string sound_address_param);
    
    static bool initialize_sys_sound();
    static void clean_sounds(bool cleanup_all=false);

    virtual void play(float gain=4.0);

};


#endif
#include "music.hpp"
#include <iostream>

Music::Music(std::string sound_address) {
    this->address = sound_address;
}


bool Music::start() {
    std::cout << "to aqui" << std::endl;
    return true;
}
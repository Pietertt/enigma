#include "main.h"

namespace enigma {

    Reflector::Reflector() {
        this->characters = new std::vector<Character*>();
    }

    void Reflector::addCharacter(Character* character) {
        this->characters->push_back(character);
    }

    std::vector<Character*>* Reflector::getCharacters() {
        return this->characters;
    }
}

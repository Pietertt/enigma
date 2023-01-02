#include "main.h"

namespace enigma {

    Plugboard::Plugboard() {

    }

    void Plugboard::addPair(char a, char b) {
        std::pair<char, char> pair;
        pair.first = a;
        pair.second = b;
        this->pairs.insert(pair);
    }

    std::map<char, char> Plugboard::getPairs() {
        return this->pairs;
    }
}

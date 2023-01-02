#include "main.h"

namespace enigma {

    Rotor::Rotor() {
        this->characters = new std::vector<Character*>();
    }

    int Rotor::getPosition() {
        return this->position;
    }

    void Rotor::setPosition(int position) {
        int difference = this->getPosition() - position;

        if (difference >= 0) {
            for (int i = 0; i < ROTOR_MAX_POSITIONS - difference; i++) {
                this->rotate();
            }
        } else {
            for (int i = 0; i < abs(difference); i++) {
                this->rotate();
            }
        }
    }

    void Rotor::addCharacter(Character* character) {
        this->characters->push_back(character);
    }

    std::vector<Character*>* Rotor::getCharacters() {
        return this->characters;
    }



    Character* Rotor::getCurrentCharacter() {
        return this->getCharacters()->at(this->getPosition());
    }

    void Rotor::rotate() {
        std::vector<Character*>* newvector = new std::vector<Character*>();
        newvector->push_back(this->getCharacters()->at(this->getCharacters()->size() - 1));

        for (int i = 0; i < ROTOR_MAX_POSITIONS - 1; i++) {
            newvector->push_back(this->getCharacters()->at(i));
        }

        delete this->getCharacters();
        this->characters = newvector;

        for (int i = 0; i < ROTOR_MAX_POSITIONS; i++) {
            this->characters->at(i)->setInput(i);
        }

        if (this->getPosition() == (ROTOR_MAX_POSITIONS - 1)) {
            this->position = 0;
            if (this->getNextRotor()) {
                this->getNextRotor()->rotate();
            }
            return;
        }

        this->position++;
    }

    Rotor* Rotor::getNextRotor() {
        return this->nextRotor;
    }

    void Rotor::setNextRotor(Rotor* rotor) {
        this->nextRotor = rotor;
    }

    std::map<int, int> Rotor::getMap() {
        return this->map;
    }

    void Rotor::setMap(std::map<int, int> map) {
        this->map = map;
    }

    Character* Rotor::findOutput(int number) {
        Character* character;

        for (Character* c : *this->getCharacters()) {
            if (c->getOutput() == number) {
                return c;
            }
        }

        return nullptr;
    }
}

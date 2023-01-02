#include "main.h"

namespace enigma {

    Character::Character() {

    }

    Character::Character(char character) {
        // this->setOutput(character);
    }

    int Character::getInput() {
        return this->input;
    }

    void Character::setInput(int input) {
        this->input = input;
    }

    int Character::getOutput() {
        return this->output;
    }

    void Character::setOutput(int output) {
        this->output = output;
    }
}

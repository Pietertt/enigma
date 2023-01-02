#include "main.h"

namespace enigma {

    Enigma::Enigma(
        std::vector<std::string> wiring,
        std::string reflector,
        std::map<char, char>* plugboard) {
        this->rotors = new std::vector<Rotor*>();

        Rotor* nextRotor = nullptr;
        std::vector<Rotor*> rotors;

        for (std::string wires : wiring) {
            Rotor* rotor = new Rotor();
            this->setWiring(wires, rotor);
            this->addRotor(rotor);
        }

        int index = 0;
        for (Rotor* rotor : *this->getRotors()) {
            try {
                Rotor* nextRotor = this->getRotors()->at(index + 1);
                rotor->setNextRotor(nextRotor);
            } catch (const std::out_of_range& e) {
                
            }
            index++;
        }

        this->setReflector(new Reflector());
        this->setWiring(reflector, this->getReflector());

        this->setPlugboard(new Plugboard());
        if (plugboard != nullptr) {
            for (std::pair<char, char> pair : *plugboard) {
                // this->getPlugboard()->addPair(std::pair());
            }
        }
    }

    void Enigma::addRotor(Rotor* rotor) {
        this->rotors->push_back(rotor);
    }

    std::vector<Rotor*>* Enigma::getRotors() {
        return this->rotors;
    }

    std::string Enigma::encode(std::string string) {
        std::string output;

        for (char& c : string) {
            char originalCharacter = c;

            std::vector<char> skippedElements {' ', '.', ','};

            if (std::find(skippedElements.begin(), skippedElements.end(), c) != skippedElements.end()) {
                output.push_back(c);
                continue;
            }

            for (std::pair<char, char> pair : this->getPlugboard()->getPairs()) {
                if (pair.first == c) {
                    c = pair.second;
                } else if (pair.second == c) {
                    c = pair.first;
                }
            }

            int in = 0;
            int out = 0;

            if (isupper(c)) {
                in = (c - 'A');
            } else {
                in = (c - 'a');
            }

            for (Rotor* rotor : *this->getRotors()) {
                out = rotor->getCharacters()->at(in)->getOutput();
                in = out;
            }

            in = this->reflector->getCharacters()->at(in)->getOutput();

            for (Rotor* rotor : *this->getRotors() | std::views::reverse) {
                out = rotor->findOutput(in)->getInput();
                in = out;
            }

            c = isupper(c) ? this->characters.at(in) : tolower(this->characters.at(in));

            for (std::pair<char, char> pair : this->getPlugboard()->getPairs()) {
                if (pair.first == c) {
                    c = pair.second;
                } else if (pair.second == c) {
                    c = pair.first;
                }
            }

            output.push_back(c);
            this->getRotors()->at(0)->rotate();
        }

        return output;
    }

    void Enigma::rotate() {
        this->getRotors()->at(0)->rotate();
    }

    void Enigma::reset() {
        for (Rotor* rotor : *this->getRotors()) {
            rotor->setPosition(0);
        }
    }

    Reflector* Enigma::getReflector() {
        return this->reflector;
    }

    void Enigma::setReflector(Reflector* reflector) {
        this->reflector = reflector;
    }

    Plugboard* Enigma::getPlugboard() {
        return this->plugboard;
    }

    void Enigma::setPlugboard(Plugboard* plugboard) {
        this->plugboard = plugboard;
    }

    void Enigma::setWiring(std::string input, IO* io) {
        std::vector<char> characters {
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
            'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
            'U', 'V', 'W', 'X', 'Y', 'Z'
        };

        for (char a : characters) {
            io->addCharacter(new Character(a));
        }

        int index = 0;
        for (char character : input) {
            int position = (character - 'A');
            io->getCharacters()->at(index)->setInput(index);
            io->getCharacters()->at(index)->setOutput(position);
            index++;
        }
    }
}

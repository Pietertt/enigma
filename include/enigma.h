#pragma once

namespace enigma {

    class Reflector;
    class IO;
    class Plugboard;
    class Rotor;

    class Enigma {
        public:
            Enigma(
                std::vector<std::string> wiring,
                std::string reflector,
                std::map<char, char>* plugboard = nullptr);
            void addRotor(Rotor* rotor);
            std::vector<Rotor*>* getRotors();
            std::string encode(std::string string);
            void rotate();
            void reset();
            void setWiring(std::string input, IO* io);

            Reflector* getReflector();
            void setReflector(Reflector* reflector);
            Plugboard* getPlugboard();
            void setPlugboard(Plugboard* plugboard);

        private:
            std::vector<Rotor*>* rotors;

            std::vector<char> characters {
                'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
                'U', 'V', 'W', 'X', 'Y', 'Z'
            };

            Reflector* reflector;
            Plugboard* plugboard;

        protected:

    };
}

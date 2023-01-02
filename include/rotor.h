#pragma once

#include "IO.h"

namespace enigma {

    class Character;

    class Rotor : public IO {
        public:
            Rotor();

            int getPosition();
            void setPosition(int position);

            virtual void addCharacter(Character* character);
            virtual std::vector<Character*>* getCharacters();

            
            Character* getCurrentCharacter();

            Rotor* getNextRotor();
            void setNextRotor(Rotor* nextRotor);
            void rotate();

            std::map<int, int> getMap();
            void setMap(std::map<int, int> map);
            Character* findOutput(int number);

        private:
            int position = 0;
            
            Rotor* nextRotor = nullptr;
            std::map<int, int> map;

        protected:

    };
}

#pragma once

namespace enigma {

    class Character;

    class IO {
        public:
            virtual void addCharacter(Character* character) = 0;
            virtual std::vector<Character*>* getCharacters() = 0;

            std::string initialCharacters;

        private:

        protected:
            std::vector<Character*>* characters;
            
    };
}

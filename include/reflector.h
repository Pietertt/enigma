#pragma once

#include "IO.h"

namespace enigma {

    class Reflector : public IO {
        public:
            Reflector();

            virtual void addCharacter(Character* character);
            virtual std::vector<Character*>* getCharacters();

        private:

        protected:

    };
}

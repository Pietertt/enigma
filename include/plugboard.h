#pragma once

namespace enigma {

    class Character;

    class Plugboard {
        public:
            Plugboard();
            void addPair(char a, char b);
            std::map<char, char> getPairs();

        private:
            std::map<char, char> pairs;
 
        protected:

    };
}

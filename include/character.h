#pragma once

namespace enigma {

    class Character {
        public:
            Character();
            Character(char character);

            int getInput();
            void setInput(int input);
            int getOutput();
            void setOutput(int output);

        private:
            int input;
            int output;

        protected:

    };
}

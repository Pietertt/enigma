#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING

#include <iostream>
#include <vector>

#include <catch2/catch_all.hpp>

#include "character.h"
#include "enigma.h"
#include "rotor.h"
#include "plugboard.h"

TEST_CASE ("Rotors can be added to the machine", "[rotor]") {
        enigma::Enigma* enigma = new enigma::Enigma(std::vector<std::string>{
        "JGDQOXUSCAMIFRVTPNEWKBLZYH",
        "NTZPSFBOKMWRCJDIVLAEYUXHGQ",
        "JVIUBHTCDYAKEQZPOSGXNRMWFL"},
        "QYHOGNECVPUZTFDJAXWMKISRBL");

    SECTION ("Rotating a rotor 27 times will cause a reset") {
        REQUIRE(enigma->getRotors()->at(0)->getPosition() == 0);
        for (int i = 0; i < 26; i++) {
            enigma->getRotors()->at(0)->rotate();
        }

        REQUIRE(enigma->getRotors()->at(0)->getPosition() == 0);
    }

    SECTION ("The last rotor is not chained") {
        REQUIRE(enigma->getRotors()->at(0)->getNextRotor() == enigma->getRotors()->at(1));
        REQUIRE(enigma->getRotors()->at(1)->getNextRotor() == enigma->getRotors()->at(2));
        REQUIRE(enigma->getRotors()->at(2)->getNextRotor() == nullptr);
    }

    SECTION ("Searching for an output in a rotor yields the correct results") {
        REQUIRE (enigma->getRotors()->at(0)->findOutput(25)->getInput() == 23);

        REQUIRE (enigma->getRotors()->at(0)->findOutput(8)->getInput() == 11);
    }
}

TEST_CASE ("The machine can be built", "[machine]") {
        enigma::Enigma* enigma = new enigma::Enigma(std::vector<std::string>{
        "JGDQOXUSCAMIFRVTPNEWKBLZYH",
        "NTZPSFBOKMWRCJDIVLAEYUXHGQ",
        "JVIUBHTCDYAKEQZPOSGXNRMWFL"},
        "QYHOGNECVPUZTFDJAXWMKISRBL");

    SECTION ("Rotating the first rotor will result in a different character on a specific position") {
        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 9);

        enigma->getRotors()->at(0)->rotate();

        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 7);
    }

    SECTION ("The first character will move one place when the first rotor is rotated") {
        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 9);

        enigma->getRotors()->at(0)->rotate();

        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(1)->getOutput() == 9);
    }

    SECTION ("The position of a rotor can be set backwards manually") {
        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 9);

        enigma->getRotors()->at(0)->rotate();

        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 7);

        enigma->getRotors()->at(0)->setPosition(0);

        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 9);
    }

    SECTION ("The position of a rotor can be set forwards manually") {
        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 9);

        enigma->getRotors()->at(0)->rotate();

        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 7);

        enigma->getRotors()->at(0)->setPosition(2);

        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 24);
    }

    SECTION ("The input characters don't change on a rotation") {
        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getInput() == 0);

        enigma->rotate();

        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getInput() == 0);

        for (int i = 0; i < 10; i++) {
            enigma->rotate();
        }

        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getInput() == 0);
    }

    SECTION ("A full rotation of a rotor will advance the next rotor") {
        REQUIRE (enigma->getRotors()->at(1)->getCharacters()->at(0)->getOutput() == 13);

        for (int i = 0; i < 26; i++) {
            enigma->getRotors()->at(0)->rotate();
        }

        REQUIRE (enigma->getRotors()->at(1)->getCharacters()->at(0)->getOutput() == 16);
    }

    SECTION ("Rotating the last rotor will result in a different input character") {
        REQUIRE (enigma->getRotors()->at(2)->getCharacters()->at(0)->getOutput() == 9);

        for (int i = 0; i < 27; i++) {
            for (int j = 0; j < 27; j++) {
                for (int k = 0; k < 5; k++) {
                    enigma->getRotors()->at(0)->rotate();
                }
            }
        }

        REQUIRE (enigma->getRotors()->at(2)->getCharacters()->at(0)->getOutput() == 17);
    }

    SECTION ("The internal wiring can be set") {
        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getOutput() == 9);
        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(0)->getInput() == 0);
        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(25)->getOutput() == 7);
        REQUIRE (enigma->getRotors()->at(0)->getCharacters()->at(25)->getInput() == 25);     
    }
}

TEST_CASE ("The enigma machine outputs the correct code", "[machine]") {
        enigma::Enigma* enigma = new enigma::Enigma(std::vector<std::string>{
        "JGDQOXUSCAMIFRVTPNEWKBLZYH",
        "NTZPSFBOKMWRCJDIVLAEYUXHGQ",
        "JVIUBHTCDYAKEQZPOSGXNRMWFL"},
        "QYHOGNECVPUZTFDJAXWMKISRBL");

    SECTION ("Single characters are correctly encoded") {
        REQUIRE (enigma->encode(std::string("T")) == "W");
    }

    SECTION ("Single characters are correctly decoded") {
        REQUIRE (enigma->encode(std::string("W")) == "T");
    }
    
    SECTION ("Words are correctly encoded") {
        REQUIRE (enigma->encode(std::string("TEST")) == "WWZA");
    }

    SECTION ("Words are correctly decoded") {
        REQUIRE (enigma->encode(std::string("WWZA")) == "TEST");
    }

    SECTION ("Both upper- and lowercase characters are allowed") {
        REQUIRE (enigma->encode(std::string("t")) == "w");

        enigma->reset();

        REQUIRE (enigma->encode(std::string("test")) == "wwza");

        enigma->reset();

        REQUIRE (enigma->encode(std::string("wwza")) == "test");
    }

    SECTION ("Spaces are ignored") {
        std::string output = enigma->encode(std::string("HELLO WORLD"));

        enigma->reset();

        REQUIRE (enigma->encode(output) == "HELLO WORLD");
    }

    SECTION ("Dots and commas are ignored") {
        std::string outputDot = enigma->encode(std::string("HELLO, WORLD"));
        enigma->reset();
        std::string outputComma = enigma->encode(std::string("HELLO. WORLD."));
        enigma->reset();

        REQUIRE (enigma->encode(outputDot) == "HELLO, WORLD");
        enigma->reset();
        REQUIRE (enigma->encode(outputComma) == "HELLO. WORLD.");
    }

    SECTION("Consecutive encoding will result in different outcomes") {
        REQUIRE (enigma->encode(std::string("TEST")) == "WWZA");

        REQUIRE (enigma->encode(std::string("TEST")) == "VNLM");
    }

    SECTION ("Inputting the encoded message with a reset will result in the original message") {
        REQUIRE (enigma->encode(std::string("TEST")) == "WWZA");

        enigma->reset();

        REQUIRE (enigma->encode(std::string("WWZA")) == "TEST");
    }

    SECTION ("Different settings will work as well") {
        enigma->getRotors()->at(0)->setPosition(13);
        enigma->getRotors()->at(1)->setPosition(21);
        enigma->getRotors()->at(2)->setPosition(9);

        REQUIRE (enigma->encode(std::string("TEST")) == "VZHI");

        enigma->reset();

        for (int i = 0; i < 26 * 26 * 9; i++) {
            enigma->getRotors()->at(0)->rotate();
        }

        for (int i = 0; i < 26 * 21; i++) {
            enigma->getRotors()->at(0)->rotate();
        }

        for (int i = 0; i < 13; i++) {
            enigma->getRotors()->at(0)->rotate();
        }

        REQUIRE (enigma->encode(std::string("VZHI")) == "TEST");
    }
}

TEST_CASE ("The plugboard works correctly", "[plugboard]") {
    enigma::Enigma* enigma = new enigma::Enigma(std::vector<std::string>{
        "JGDQOXUSCAMIFRVTPNEWKBLZYH",
        "NTZPSFBOKMWRCJDIVLAEYUXHGQ",
        "JVIUBHTCDYAKEQZPOSGXNRMWFL"},
        "QYHOGNECVPUZTFDJAXWMKISRBL"
    );

    SECTION ("Pairs can be added to the plugboard") {
        enigma->getPlugboard()->addPair('A', 'B');
        enigma->getPlugboard()->addPair('G', 'X');

        REQUIRE (enigma->getPlugboard()->getPairs().size() == 2);
    }

    SECTION ("A single character gives a different output when the plugboard is set up") {
        REQUIRE (enigma->encode(std::string("A")) == "S");
        
        enigma->reset();
        enigma->getPlugboard()->addPair('A', 'B');

        REQUIRE_FALSE (enigma->encode(std::string("A")) == "S");
    }

    SECTION ("Words give a different output when the plugboard is used") {
        REQUIRE (enigma->encode(std::string("TEST")) == "WWZA");

        enigma->reset();
        enigma->getPlugboard()->addPair('T', 'A');
        enigma->getPlugboard()->addPair('E', 'B');
        enigma->getPlugboard()->addPair('S', 'C');
        enigma->getPlugboard()->addPair('T', 'D');

        REQUIRE_FALSE (enigma->encode(std::string("A")) == "WWZA");
    }

    SECTION ("Decoding yields the correct output with a single character when the same plug is used") {
        enigma->getPlugboard()->addPair('A', 'B');

        REQUIRE (enigma->encode(std::string("A")) == "K");
        
        enigma->reset();

        REQUIRE (enigma->encode(std::string("K")) == "A");
    }

    SECTION ("Decoding yields the correct output with words when the same plug is used") {
        REQUIRE (enigma->encode(std::string("A")) == "S");
        
        enigma->reset();
        enigma->getPlugboard()->addPair('A', 'B');

        REQUIRE_FALSE (enigma->encode(std::string("A")) == "S");
    }
}

int main(int argc, char* argv[]) {
    Catch::Session session;

    int returnCode = session.applyCommandLine(argc, argv);

    if (returnCode != 0) {
        return returnCode;
    }

    int numFailed = session.run();
    return numFailed;
}

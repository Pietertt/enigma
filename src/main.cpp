#include "main.h"

int main() {
    
    enigma::Enigma* A = new enigma::Enigma(std::vector<std::string>{
        "PEZUOHXSCVFMTBGLRINQJWAYDK",
        "ZOUESYDKFWPCIQXHMVBLGNJRAT",
        "EHRVXGAOBQUSIMZFLYNWKTPDJC"},
        "IMETCGFRAYSQBZXWLHKDVUPOJN");

    enigma::Enigma* B = new enigma::Enigma(std::vector<std::string>{
        "PEZUOHXSCVFMTBGLRINQJWAYDK",
        "ZOUESYDKFWPCIQXHMVBLGNJRAT",
        "EHRVXGAOBQUSIMZFLYNWKTPDJC"},
        "IMETCGFRAYSQBZXWLHKDVUPOJN");

    A->getPlugboard()->addPair('H', 'F');
    A->getPlugboard()->addPair('Q', 'W');
    A->getPlugboard()->addPair('Z', 'D');
    A->getPlugboard()->addPair('U', 'G');
    A->getPlugboard()->addPair('Y', 'E');
    A->getPlugboard()->addPair('I', 'L');
    A->getPlugboard()->addPair('V', 'A');
    A->getPlugboard()->addPair('O', 'M');
    A->getPlugboard()->addPair('C', 'J');
    A->getPlugboard()->addPair('N', 'B');

    B->getPlugboard()->addPair('H', 'F');
    B->getPlugboard()->addPair('Q', 'W');
    B->getPlugboard()->addPair('Z', 'D');
    B->getPlugboard()->addPair('U', 'G');
    B->getPlugboard()->addPair('Y', 'E');
    B->getPlugboard()->addPair('I', 'L');
    B->getPlugboard()->addPair('V', 'A');
    B->getPlugboard()->addPair('O', 'M');
    B->getPlugboard()->addPair('C', 'J');
    B->getPlugboard()->addPair('N', 'B');

    std::string outputA = A->encode(std::string("HELLOWORLD"));
    std::string outputB = B->encode(outputA);

    std::cout << outputA << std::endl;
    std::cout << outputB << std::endl;

    return 0;
}

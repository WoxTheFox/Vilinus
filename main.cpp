#include <iostream>
#include <ostream>

#include "bitboard.h"
#include "types.h"

int main() {

    Bitboard bb = 0;
    setBit(bb, E4);
    setBit(bb, A1);
    setBit(bb, makeSquare(7, 7));

    std::cout << "E4: " << getBit(bb, E4) << std::endl;
    std::cout << "A2: " << getBit(bb, A2) << std::endl;
    std::cout << "Liczba bitów: " << popCount(bb) << std::endl;

    Bitboard tmp = bb;

    while(tmp) {
        std::cout << popLsb(tmp) << std::endl;
    }

    printBoard(bb);

    printBoard(tmp);
    return 0;
}
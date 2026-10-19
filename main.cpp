#include <iostream>
#include <ostream>

#include "bitboard.h"
#include "types.h"
#include "position.h"

int main() {

    Position pos;
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


    setBit(pos.pieces[WHITE][ROOK], G1);
    setBit(pos.pieces[BLACK][PAWN], A2);
    pos.updateOccupancy();
    printBoard(pos.occupancy[WHITE]);
    printBoard(pos.occupancy[BLACK]);
    printBoard(pos.occupancy[BOTH]);

    return 0;
}
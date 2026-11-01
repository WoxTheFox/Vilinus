#include <iostream>
#include <ostream>

#include "bitboard.h"
#include "types.h"
#include "position.h"
#include "attacks.h"

int main() {

    initAttacks();

    Bitboard test = {};
    setBit(test, D6);
    setBit(test, F4);
    setBit(test, F6);

    printBoard(rookAttacks(D4, 0));
    printBoard(rookAttacks(D4, test));
    printBoard(bishopAttacks(D4, 0));
    printBoard(bishopAttacks(D4, test));
    printBoard(queenAttacks(D4, 0));

    return 0;
}
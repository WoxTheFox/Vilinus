#include <iostream>
#include <ostream>

#include "bitboard.h"
#include "types.h"
#include "position.h"
#include "attacks.h"

int main() {

    Move move = makeMove(H7, H8, PROMOTION_QUEEN_CAPTURE);
    std::cout << getFrom(move) << " " << getTo(move) << " " << getFlag(move) << std::endl;

    return 0;
}
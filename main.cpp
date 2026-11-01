#include <iostream>
#include <ostream>

#include "bitboard.h"
#include "types.h"
#include "position.h"
#include "attacks.h"
#include "movegen.h"

int main() {

    initAttacks();

    Position pos;
    MoveList moveList;

    pos.loadFen("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R b KQkq - 0 1");

    generatePawnMoves(pos, moveList);

    std::cout << moveList.moveCount << std::endl;

    for (int i = 0; i < moveList.moveCount; i++)
    {
        std::cout << getFrom(moveList.moves[i]) << " "
                  << getTo(moveList.moves[i]) << " "
                  << getFlag(moveList.moves[i]) << std::endl;
    }

    return 0;
}
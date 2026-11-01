#include <iostream>
#include <ostream>

#include "bitboard.h"
#include "types.h"
#include "position.h"
#include "attacks.h"
#include "movegen.h"

#define START_MOVE = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
#define KIWIPETE = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
int main() {

    initAttacks();

    Position pos;
    MoveList moveList;

    pos.loadFen("rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq d6 0 3");

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
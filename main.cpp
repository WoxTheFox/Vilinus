#include <iostream>
#include <ostream>

#include "bitboard.h"
#include "types.h"
#include "position.h"

int main() {

    Position pos;

    std::string startFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    std::string kiwipete = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";

    Color color = BLACK;
    PieceType type = PAWN;

    pos.loadFen(startFen);

    printBoard(pos.pieces[WHITE][PAWN]);
    printBoard(pos.pieces[BLACK][KNIGHT]);
    printBoard(pos.occupancy[BOTH]);

    pos.loadFen(kiwipete);

    std::cout << pos.pieces[WHITE][PAWN] << std::endl;
    std::cout << pos.pieces[BLACK][KNIGHT] << std::endl;
    std::cout << pos.occupancy[BOTH] << std::endl;


    return 0;
}
#include <iostream>
#include <ostream>

#include "bitboard.h"
#include "types.h"
#include "position.h"

int main() {

    Position pos;

    Color color = BLACK;
    PieceType type = PAWN;

    std::cout << "N: " << fenToFigure('N', color, type) << " " << color << " " << type << std::endl;
    std::cout << "N: " << fenToFigure('q', color, type) << " " << color << " " << type << std::endl;
    std::cout << "N: " << fenToFigure('P', color, type) << " " << color << " " << type << std::endl;
    std::cout << "N: " << fenToFigure('x', color, type) << " " << color << " " << type << std::endl;

    return 0;
}
#pragma once

#include <iostream>

#include "types.h"


inline void printBoard(Bitboard bb)
{
    for (int y = 7; y >= 0; y--)
    {
        std::cout << y + 1 << "   ";
        for (int x = 0; x <= 7; x++)
        {
            if (getBit(bb, makeSquare(x, y)))
            {
                std::cout << "1" << " ";
            }
            else
            {
                std::cout << "." << " ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "    a b c d e f g h" << std::endl;
    std::cout << "Bity: " << popCount(bb) << std::endl;
    std::cout << std::hex << bb << std::dec << std::endl;
}

#pragma once

#include "position.h"
#include "attacks.h"
#include "types.h"

struct MoveList
{
    Move moves[256];
    int moveCount = 0;

    void addMove(Move mv) noexcept
    {
        moves[moveCount++] = mv;
    }
};

inline void generatePieceMoves(const Position& pos, MoveList& mvl, const PieceType type)
{

    const Color us = pos.onMove;
    const auto them = static_cast<Color>(us ^ 1);

    Bitboard pieces = pos.pieces[us][type];

    while (pieces)
    {
        const Square from = popLsb(pieces);
        const Bitboard target  = (pieceAttacks(type, from, pos.occupancy[BOTH]) & ~ pos.occupancy[us]);

        Bitboard captures = (target & pos.occupancy[them]);
        while (captures)
        {
            const Square to = popLsb(captures);
            const Move mv = makeMove(from, to, CAPTURE);
            mvl.addMove(mv);
        }

        Bitboard quiets = (target & ~pos.occupancy[BOTH]);
        while (quiets)
        {
            const Square to = popLsb(quiets);
            const Move mv = makeMove(from, to, MOVE);
            mvl.addMove(mv);
        }
    }
}

inline void generatePawnMoves(const Position& pos, MoveList& mvl)
{
    const Color us = pos.onMove;
    const auto them = static_cast<Color>(us ^ 1);

    Bitboard pawns = pos.pieces[us][PAWN];

    const int forward = us == WHITE ? 8 : -8;
    const Bitboard start = us == WHITE ? RANK_2 : RANK_7;

    while (pawns)
    {
        const Square from = popLsb(pawns);
        const auto to = static_cast<Square>(from + forward);

        if (!getBit(pos.occupancy[BOTH], to))
        {
            mvl.addMove(makeMove(from, to, MOVE));

            if (getBit(start, from))
            {
                const auto twoSquare = static_cast<Square>(from + forward*2);
                if (!getBit(pos.occupancy[BOTH], twoSquare))
                {
                    mvl.addMove(makeMove(from, twoSquare, TWO_SQUARE_ADVANCE));
                }
            }
        }
    }
}

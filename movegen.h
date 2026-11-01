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

inline void addPawnMoves(MoveList& mvl, Bitboard destination, int offset, MoveFlags mvf) noexcept
{
    while (destination)
    {
        const Square to = popLsb(destination);
        const auto from = static_cast<Square>(to - offset);
        mvl.addMove(makeMove(from, to, mvf));
    }
}

inline void addPawnPromotions(MoveList& mvl, Bitboard destination, int offset, bool isCapture) noexcept
{
    const int base = (isCapture ? (PROMOTION_KNIGHT_CAPTURE) : (PROMOTION_KNIGHT));

    while (destination)
    {
        const Square to = popLsb(destination);
        const auto from = static_cast<Square>(to - offset);
        for (int i = 0; i < 4; i++)
        {
            mvl.addMove(makeMove(from, to,  static_cast<MoveFlags>(base + i)));
        }
    }

}

inline void generatePawnMoves(const Position& pos, MoveList& mvl) noexcept
{
    const Color us = pos.onMove;
    const auto them = static_cast<Color>(us ^ 1);
    const Bitboard pawns = pos.pieces[us][PAWN];
    const Bitboard empty = ~ pos.occupancy[BOTH];
    const Bitboard thirdRank = us == WHITE ? RANK_3 : RANK_6;
    const Bitboard lastRank = us == WHITE ? RANK_8 : RANK_1;
    const int forward = us == WHITE ? 8 : -8;
    const int leftDelta = us == WHITE ? 7 : -9;
    const int rightDelta = us == WHITE ? 9 : -7;

    Bitboard singles = ((us == WHITE ? (pawns << 8) : (pawns >> 8)) & empty);
    Bitboard doubles = (us == WHITE ? (singles & thirdRank) << 8 : (singles & thirdRank) >> 8) & empty;
    Bitboard capturesLeft = ((us == WHITE ? (pawns << 7) : (pawns >> 9)) & pos.occupancy[them]) & NOT_H_FILE;
    Bitboard capturesRight = ((us == WHITE ? (pawns << 9) : (pawns >> 7)) & pos.occupancy[them]) & NOT_A_FILE;

    const Bitboard promotion = singles & lastRank;
    Bitboard promotionLeft = capturesLeft & lastRank;
    Bitboard promotionRight = capturesRight & lastRank;

    if (pos.enPassant != NO_SQUARE)
    {
        Bitboard epCapture = PAWN_ATTACKS[them][pos.enPassant] & pawns;

        while (epCapture)
        {
            const Square from = popLsb(epCapture);
            mvl.addMove(makeMove(from, pos.enPassant, EN_PASSANT));
        }
    }

    singles &= ~lastRank;
    capturesLeft &= ~lastRank;
    capturesRight &= ~lastRank;

    addPawnMoves(mvl, singles, forward, MOVE);
    addPawnMoves(mvl, doubles, 2 * forward, TWO_SQUARE_ADVANCE);
    addPawnMoves(mvl, capturesLeft, leftDelta, CAPTURE);
    addPawnMoves(mvl, capturesRight, rightDelta, CAPTURE);

    addPawnPromotions(mvl, promotion, forward, false);
    addPawnPromotions(mvl, promotionLeft, leftDelta, true);
    addPawnPromotions(mvl, promotionRight, rightDelta, true);
}


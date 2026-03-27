#pragma once

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

namespace boardgame::move::chess
{
    class SpecialMoveValidator
    {
    public:

        bool isPawnDoubleMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& pawn
        ) const;

        bool isCastlingMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& king
        ) const;

        bool isEnPassantMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& pawn
        ) const;

        bool isPromotionMoveValid(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move,
            const boardgame::piece::chess::IChessPiece& pawn
        ) const;
    };
}
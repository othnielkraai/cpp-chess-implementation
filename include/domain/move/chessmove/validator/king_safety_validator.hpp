#pragma once

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

namespace boardgame::move::chess
{
    class KingSafetyValidator : public IChessMoveValidator
    {
    public:
        virtual bool isValidMove(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const override;

    private: 
        bool leavesKingInCheck(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool isKingInCheck(
            const boardgame::board::chess::IChessBoard& board,
            boardgame::piece::chess::ChessPieceColor color
        ) const;

        bool isSquareAttacked(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::core::Position& square,
            boardgame::piece::chess::ChessPieceColor attackingColor
        ) const;

        bool simulateMoveOnBoard(
            boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;

        bool canPieceAttackSquare(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::core::Position& from,
            const boardgame::piece::chess::IChessPiece& piece,
            const boardgame::core::Position& target
        ) const;
    };
}
#pragma once

//STL
#include <vector>
#include <memory>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

//using declarations
using boardgame::board::chess::IChessBoard;
using boardgame::move::chess::IChessMove;
using boardgame::piece::chess::ChessPieceColor;
using boardgame::move::chess::IChessMoveValidator;
using boardgame::core::Position;

namespace boardgame::move::chess
{
    class KingSafetyValidator : public IChessMoveValidator
    {
    public:
        virtual bool isValidMove(
            const IChessBoard& board,
            const IChessMove& move
        ) const override;

    private: 
        bool leavesKingInCheck(
            const IChessBoard& board,
            const IChessMove& move
        ) const;

        bool isKingInCheck(
            const IChessBoard& board,
            ChessPieceColor color
        ) const;

        bool isSquareAttacked(
            const IChessBoard& board,
            const boardgame::core::Position& square,
            ChessPieceColor attackingColor
        ) const;

        bool simulateMoveOnBoard(
            IChessBoard& board,
            const IChessMove& move
        ) const;

        bool canPieceAttackSquare(
            const IChessBoard& board,
            const Position& from,
            const IChessPiece& piece,
            const Position& target
        ) const;
    };
}
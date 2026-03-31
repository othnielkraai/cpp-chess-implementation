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

//domain
#include "domain/move/chessmove/validator/chess_validation_utils.hpp"
#include "domain/move/chessmove/validator/king_safety_validator.hpp"
#include "domain/move/chessmove/validator/basic_move_validator.hpp"

//using declarations
using boardgame::board::chess::IChessBoard;
using boardgame::move::chess::IChessMove;
using boardgame::piece::chess::ChessPieceColor;
using boardgame::move::chess::IChessMoveValidator;
using boardgame::core::Position;

namespace boardgame::move::chess
{
    class SpecialMoveValidator : public IChessMoveValidator
    {
    public:
        virtual bool isValidMove(
            const IChessBoard& board,
            const IChessMove& move
        ) const override;
    private:
        bool isPawnDoubleMoveValid(
            const IChessBoard& board,
            const IChessMove& move,
            const IChessPiece& pawn
        ) const;

        bool isCastlingMoveValid(
            const IChessBoard& board,
            const IChessMove& move,
            const IChessPiece& king
        ) const;

        bool isEnPassantMoveValid(
            const IChessBoard& board,
            const IChessMove& move,
            const IChessPiece& pawn
        ) const;

        bool isPromotionMoveValid(
            const IChessBoard& board,
            const IChessMove& move,
            const IChessPiece& pawn
        ) const;
    };
}
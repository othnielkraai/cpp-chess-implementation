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
    class PieceMoveValidator : public IChessMoveValidator
    {
    public:
        PieceMoveValidator(std::unique_ptr<IChessMoveValidator> validator);

        virtual bool isValidMove(
            const IChessBoard& board,
            const IChessMove& move
        ) const override;

    private:
        bool isMoveShapeValid(
            const IChessBoard& board,
            const IChessMove& move,
            const IChessPiece& piece
        ) const;

        bool isPawnMoveValid(
            const IChessBoard& board,
            const IChessMove& move,
            const IChessPiece& piece
        ) const;

        bool isKnightMoveValid(
            const IChessMove& move
        ) const;

        bool isBishopMoveValid(
            const IChessBoard& board,
            const IChessMove& move
        ) const;

        bool isRookMoveValid(
            const IChessBoard& board,
            const IChessMove& move
        ) const;

        bool isQueenMoveValid(
            const IChessBoard& board,
            const IChessMove& move
        ) const;

        bool isKingMoveValid(
            const IChessBoard& board,
            const IChessMove& move
        ) const;

    private:
        std::unique_ptr<IChessMoveValidator> m_SpecialMoveValidator;
    };
}
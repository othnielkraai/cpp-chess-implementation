#pragma once

#include "domain/move/chessmove/validator/basic_move_validator.hpp"
#include "domain/move/chessmove/validator/king_safety_validator.hpp"
#include "domain/move/chessmove/validator/piece_move_validator.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

namespace boardgame::move::chess
{
    class ChessMoveValidator : public IChessMoveValidator
    {
    public:
        bool isValidMove(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const override;

    private:
        BasicMoveValidator m_BasicMoveValidator;
        PieceMoveValidator m_PieceMoveValidator;
        KingSafetyValidator m_KingSafetyValidator;
    };
}
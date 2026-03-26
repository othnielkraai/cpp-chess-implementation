#pragma once

#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

namespace boardgame::move::chess
{
    class ChessMoveValidator : public IChessMoveValidator
    {
    public:
        bool isValidMove(
            const boardgame::board::chess::IChessBoard &board,
            const boardgame::move::chess::IChessMove &move
        ) const override;
    };
}
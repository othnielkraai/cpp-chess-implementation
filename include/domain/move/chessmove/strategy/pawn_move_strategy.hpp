#pragma once

#include <vector>
#include <memory>

#include "interfaces/move/chessmove/IChessMoveStrategy.hpp"

namespace boardgame::move::chess
{
    class PawnMoveStrategy : public IChessMoveStrategy
    {
    public:
        std::vector<std::shared_ptr<IChessMove>> generateMoves(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::piece::chess::IChessPiece& piece,
            const boardgame::core::Position& from
        ) const override;
    };
}
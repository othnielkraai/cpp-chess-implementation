#pragma once

#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"

namespace boardgame::move::chess
{
    class ChessMoveGenerator : public IChessMoveGenerator
    {
    public:
        std::vector<std::shared_ptr<IChessMove>> generateMoves(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::piece::chess::IChessPiece& piece,
            const boardgame::core::Position& from
        ) const override;
    };
}
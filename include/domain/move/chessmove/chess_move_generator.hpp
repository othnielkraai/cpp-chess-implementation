#pragma once

#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"

namespace boardgame::move::chess
{
    class ChessMoveGenerator : public IChessMoveGenerator
    {
    public:
        std::vector<std::shared_ptr<IChessMove>> generateMoves(
            const boardgame::board::chess::IChessBoard& board,
            boardgame::piece::chess::ChessPieceColor color
        ) const override;
    };
}
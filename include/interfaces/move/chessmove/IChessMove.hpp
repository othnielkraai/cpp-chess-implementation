#pragma once

#include <memory>

#include "interfaces/move/IMove.hpp"

namespace boardgame::move::chess
{
    enum class ChessMoveType
    {
        Normal,
        Castling,
        EnPassant,
        Promotion,
        PawnDoubleMove,
    };

    class IChessMove : public boardgame::move::IMove
    {
    public:
        virtual ~IChessMove() = default;

        virtual ChessMoveType getMoveType() const = 0;
        virtual std::unique_ptr<IChessMove> clone() const = 0;
    };
}
#pragma once

#include "interfaces/move/IMove.hpp"

namespace boardgame::move::chess
{
    enum class ChessMoveType
    {
        Normal,
        Castling,
        EnPassant,
        Promotion
    };

    class IChessMove : public boardgame::move::IMove
    {
    public:
        virtual ~IChessMove() = default;

        virtual ChessMoveType getMoveType() const = 0;
    };
}
#pragma once

#include "interfaces/move/IMove.hpp"

namespace boardgame::move::chess
{
    class IChessMove : public boardgame::move::IMove
    {
    public:
        virtual ~IChessMove() = default;
    };
}
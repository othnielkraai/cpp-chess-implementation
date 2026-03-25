#pragma once

#include "core/common/position.hpp"
#include "interfaces/piece/IPiece.hpp"

namespace boardgame::board
{
    class IBoard
    {
    public:
        virtual ~IBoard() = default;
    };
}
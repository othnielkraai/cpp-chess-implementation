#pragma once

#include <vector>
#include <memory>   

#include "interfaces/move/chessmove/IChessMove.hpp"

using boardgame::move::chess::IChessMove;

namespace boardgame::history
{
    class IHistory
    {
    public:
        virtual ~IHistory() = default;
    };
}
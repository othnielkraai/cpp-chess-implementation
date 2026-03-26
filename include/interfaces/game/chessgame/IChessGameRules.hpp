#pragma once

#include "interfaces/game/IGameRules.hpp"

namespace boardgame::game::chess{
    class IChessGameRules : public boardgame::game::IGameRules
    {
    public:
        virtual ~IChessGameRules() = default;
    };
}
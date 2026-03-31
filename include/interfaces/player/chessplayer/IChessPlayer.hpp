#pragma once

// Interfaces
#include "interfaces/player/IPlayer.hpp"

namespace boardgame::player::chess
{
    class IChessPlayer : public IPlayer
    {
    public:
        // Virtual destructor to ensure proper cleanup of derived classes
        virtual ~IChessPlayer() = default;

        // Returns true if the player is playing as white, false if playing as black
        virtual bool isWhite() const = 0;
    };
}

#pragma once

namespace boardgame::game
{
    class IGame
    {
        virtual ~IGame() = default;
        virtual bool isGameOver() const = 0;
    };
}
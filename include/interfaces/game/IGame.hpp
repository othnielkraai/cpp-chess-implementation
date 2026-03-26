#pragma once

namespace boardgame::game
{
    class IGame
    {
        public:
        virtual ~IGame() = default;
        virtual bool isGameOver() const = 0;
    };
}
#pragma once
#include "core/common/position.hpp"

namespace boardgame::move
{
    class IMove
    {
    public:
        virtual ~IMove() = default;

        virtual boardgame::core::Position getFrom() const = 0;
        virtual boardgame::core::Position getTo() const = 0;
    };
}
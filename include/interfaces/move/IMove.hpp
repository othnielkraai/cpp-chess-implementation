#pragma once
#include "core/common/position.hpp"

namespace boardgame::move
{
    class IMove
    {
    public:
        /// @brief Virtual destructor for the move interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer
        virtual ~IMove() = default;

        /// @brief Gets the starting position of the move.
        /// @return The starting position of the move.
        virtual boardgame::core::Position getFrom() const = 0;

        /// @brief Gets the ending position of the move.
        /// @return The ending position of the move.
        virtual boardgame::core::Position getTo() const = 0;
    };
}
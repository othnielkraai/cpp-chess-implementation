#pragma once

// STL
#include <memory>

// Interfaces
#include "core/common/position.hpp"

namespace boardgame::move::chess
{
    /// @brief Enumeration for different types of chess moves.
    enum class ChessMoveType
    {
        Normal,
        Castling,
        EnPassant,
        Promotion,
        PawnDoubleMove,
    };

    class IChessMove
    {
    public:
        /// @brief Virtual destructor for the chess move interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer
        virtual ~IChessMove() = default;

        /// @brief Gets the starting position of the move.
        /// @return The starting position of the move.
        virtual boardgame::core::Position getFrom() const = 0;

        /// @brief Gets the ending position of the move.
        /// @return The ending position of the move.
        virtual boardgame::core::Position getTo() const = 0;

        /// @brief Gets the type of the chess move.
        /// @return The type of the chess move.
        virtual ChessMoveType getMoveType() const = 0;

        /// @brief Creates a deep copy of the chess move for cloning the board.
        /// @return A unique pointer to the cloned chess move.
        virtual std::unique_ptr<IChessMove> clone() const = 0;
    };
}
#pragma once

#include "interfaces/piece/IPiece.hpp"
#include "interfaces/move/chessmove/IChessMoveStrategy.hpp"


namespace boardgame::move::chess
{
    class IChessMoveStrategy;
}

namespace boardgame::piece::chess
{
    /// @brief Enumeration for the different types of chess pieces.
    enum class ChessPieceType
    {
        Pawn,
        Rook,
        Knight,
        Bishop,
        Queen,
        King
    };

    /// @brief Enumeration for the colors of chess pieces.
    enum class ChessPieceColor
    {
        White,
        Black
    };

    class IChessPiece : public IPiece
    {
    public:
        /// @brief Virtual destructor for the chess piece interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer to IChessPiece.
        virtual ~IChessPiece() = default;

        /// @brief Gets the type of the chess piece.
        /// @return The type of the chess piece.
        virtual ChessPieceType getType() const = 0;

        /// @brief Gets the color of the chess piece.
        /// @return The color of the chess piece.
        virtual ChessPieceColor getColor() const = 0;

        /// @brief Gets the move strategy associated with this chess piece.
        /// @return A reference to the move strategy for this chess piece.
        virtual const boardgame::move::chess::IChessMoveStrategy& getMoveStrategy() const = 0;

        /// @brief Checks if the chess piece has moved.
        /// @return True if the piece has moved, false otherwise.
        virtual bool hasMoved() const = 0;
        
        /// @brief Sets the moved status of the chess piece.
        /// @param hasMoved The moved status to set.
        virtual void setHasMoved(bool hasMoved) = 0;

        /// @brief Creates a deep copy of the chess piece for cloning the board.
        /// @return A unique pointer to the cloned chess piece.
        virtual std::unique_ptr<IChessPiece> clone() const = 0;
    };

}
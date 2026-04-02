#pragma once

// STL
#include <memory>
#include <optional>

// core
#include "core/common/position.hpp"

// interfaces
#include "interfaces/piece/chesspiece/IChessPiece.hpp"

//forward declaration
namespace boardgame::piece::chess
{
    class IChessPiece;
    enum class ChessPieceType;
    enum class ChessPieceColor;
}

//using declarations
using boardgame::core::Position;
using boardgame::piece::chess::ChessPieceType;



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

        /// @brief Gets the type of piece that a pawn is promoted to, if this move is a promotion.
        /// @return An optional containing the type of piece that a pawn is promoted to, or std::nullopt if this move is not a promotion.
        virtual std::optional<ChessPieceType> getPromotedPieceType() const = 0;

        /// @brief Sets the type of piece that a pawn is promoted to, if this move is a promotion.
        /// @param promotedPieceType The type of piece that a pawn is promoted to.
        virtual void setPromotedPieceType(ChessPieceType promotedPieceType) = 0;
    };
}
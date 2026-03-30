#pragma once

#include <vector>
#include <map>
#include <memory>
#include <optional>

#include "interfaces/board/IBoard.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

namespace boardgame::move::chess
{
    class IChessMove;
}

namespace boardgame::piece::chess
{
    class IChessPiece;
    enum class ChessPieceColor;
}

using namespace boardgame::core;
using namespace boardgame::move::chess;
using namespace boardgame::piece::chess;

namespace boardgame::board::chess
{
    class IChessBoard : public IBoard
    {
    public:
        /// @brief Virtual destructor for the chess board interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer to IChessBoard.
        virtual ~IChessBoard() = default;

        /// @brief Gets the chess piece at the specified position.
        /// @param pos The position to check.
        /// @return A pointer to the chess piece at the position, or nullptr if no piece is there.
        virtual IChessPiece *getPieceAt(const Position &pos) const = 0;

        /// @brief Places a chess piece at the specified position.
        /// @param pos The position to place the piece.
        /// @param piece The chess piece to place.
        virtual void placePiece(const Position &pos, std::unique_ptr<IChessPiece> piece) = 0;
        
        /// @brief Removes the chess piece at the specified position and returns it.
        /// @param pos The position to remove the piece from.
        /// @return A unique pointer to the removed chess piece, or nullptr if no piece is there.
        virtual std::unique_ptr<IChessPiece> removePiece(const Position &pos) = 0;

        /// @brief Moves a piece from one position to another.
        /// @param from The position to move the piece from.
        /// @param to The position to move the piece to.
        virtual void movePiece(const Position &from, const Position &to) = 0;

        /// @brief Gets all chess pieces on the board.
        /// @return A vector of pointers to all chess pieces.
        virtual std::vector<IChessPiece *> getAllPieces() const = 0;

        /// @brief Gets all chess pieces of a specific color on the board.
        /// @param color The color of the pieces to retrieve.
        /// @return A vector of pointers to the chess pieces of the specified color.
        virtual std::vector<IChessPiece *> getPieces(ChessPieceColor color) const = 0;

        /// @brief Checks if a position is within the bounds of the chess board.
        /// @param pos The position to check.
        /// @return True if the position is inside the board, false otherwise.
        virtual bool isInside(const Position &pos) const = 0;

        /// @brief Checks if a position on the board is empty (i.e., has no piece).
        /// @param pos The position to check.
        /// @return True if the position is empty, false otherwise.
        virtual bool isEmpty(const Position &pos) const = 0;

        /// @brief Checks if there is a piece at the specified position.
        /// @param pos The position to check.
        /// @return True if there is a piece at the position, false otherwise.
        virtual bool hasPiece(const Position &pos) const = 0;

        /// @brief Checks if there is an enemy piece at the specified position.
        /// @param pos The position to check.
        /// @param color The color of the piece to compare against.
        /// @return True if there is an enemy piece at the position, false otherwise.
        virtual bool hasEnemyPiece(const Position &pos, ChessPieceColor color) const = 0;

        /// @brief Checks if there is a friendly piece at the specified position.
        /// @param pos The position to check.
        /// @param color The color of the piece to compare against.
        /// @return True if there is a friendly piece at the position, false otherwise.
        virtual bool hasFriendlyPiece(const Position &pos, ChessPieceColor color) const = 0;

        /// @brief Finds the position of the king of the specified color.
        /// @param color The color of the king to find.
        /// @return The position of the king.
        virtual Position findKing(ChessPieceColor color) const = 0;

        /// @brief Sets the last move made on the board.
        /// @param move The move to set as the last move.
        virtual void setLastMove(const IChessMove &move) = 0;

        /// @brief Gets the last move made on the board.
        /// @return An optional containing the last move if it exists, or std::nullopt if no move has been made.
        virtual std::optional<IChessMove> getLastMove() const = 0;

        /// @brief Creates a deep copy of the chess board.
        /// @return A unique pointer to the cloned chess board.
        virtual std::unique_ptr<IChessBoard> cloneBoard() const = 0;
    };

}
#pragma once

#include <vector>
#include <memory>

#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"

using boardgame::core::Position;
using boardgame::move::chess::IChessMove;
using boardgame::piece::chess::ChessPieceColor;
using boardgame::piece::chess::ChessPieceType;

namespace boardgame::history::chess
{
    struct ChessRecord
    {
        std::unique_ptr<IChessMove> move;

        ChessPieceType movedPieceType;
        ChessPieceColor movedPieceColor;

        std::optional<ChessPieceType> capturedPieceType;
        std::optional<ChessPieceColor> capturedPieceColor;
        std::optional<Position> capturedPiecePosition;

        std::optional<ChessPieceType> promotionPieceType;

        std::optional<Position> rookFrom;
        std::optional<Position> rookTo;
    };

    class IChessHistory
    {
    public:
        virtual ~IChessHistory() = default;

        /// @brief Adds a record to the chess history
        /// @param record the chess record to add
        virtual void addRecord(std::unique_ptr<ChessRecord> record) = 0;

        /// @brief Gets the list of chess records in the history
        /// @return a reference to the vector of chess records
        virtual std::vector<std::unique_ptr<ChessRecord>> &getHistory() = 0;

        /// @brief Undoes the last move in the chess history and returns the move that was undone
        /// @return an optional containing the move that was undone, or std::nullopt if there are no moves to undo
        virtual std::optional<std::unique_ptr<ChessRecord>> undo() = 0;

        /// @brief Redoes the last undone move in the chess history and returns the move that was redone
        /// @return an optional containing the move that was redone, or std::nullopt
        virtual std::optional<std::unique_ptr<ChessRecord>> redo() = 0;
    };
}
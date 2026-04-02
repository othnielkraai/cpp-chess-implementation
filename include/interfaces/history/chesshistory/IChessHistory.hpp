#pragma once

#include <vector>
#include <memory>

#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/history/IHistory.hpp"

using boardgame::move::chess::IChessMove;
using boardgame::piece::chess::ChessPieceType;
using boardgame::piece::chess::ChessPieceColor;

namespace boardgame::history::chess
{
    struct ChessRecord
    {
        std::unique_ptr<IChessMove> move;
        ChessPieceType pieceType;        
        ChessPieceColor pieceColor;
        std::optional<ChessPieceType> capturedPiece;
        std::optional<ChessPieceType> promotionPiece;
    };

    class IChessHistory : public IHistory
    {
    public:
        virtual ~IChessHistory() = default;

        /// @brief Adds a record to the chess history
        /// @param record the chess record to add
        virtual void addRecord(std::unique_ptr<ChessRecord> record) = 0;

        /// @brief Gets the list of chess records in the history
        /// @return a const reference to the vector of chess records
        virtual const std::vector<std::unique_ptr<ChessRecord>>& getHistory() const = 0;
    };
}
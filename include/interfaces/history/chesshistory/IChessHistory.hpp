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
        ChessPieceType capturedPieceType;        
        ChessPieceColor capturedPieceColor;
        std::optional<ChessPieceType> capturedPiece;
        std::optional<ChessPieceType> promotionPiece;
    };

    class IChessHistory : public IHistory
    {
    public:
        virtual ~IChessHistory() = default;

        /// @brief Adds a move to the chess history
        /// @param move the chess move to add
        virtual void addMove(std::unique_ptr<ChessRecord> record) = 0;

        /// @brief Gets the list of chess moves in the history
        /// @return a const reference to the vector of chess moves
        virtual const std::vector<std::unique_ptr<ChessRecord>>& getHistory() const = 0;
    };
}
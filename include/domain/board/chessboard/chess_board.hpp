#pragma once

// STL
#include <map>
#include <memory>

// Core
#include "core/common/position.hpp"

// Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/piece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

namespace boardgame::board::chess
{
    class ChessBoard : public IChessBoard
    {
    public:
        // getters
        boardgame::piece::chess::IChessPiece* getPieceAt(boardgame::core::Position pos) const override;

        // modifiers
        bool placePiece(boardgame::core::Position pos,
                        std::unique_ptr<boardgame::piece::chess::IChessPiece> piece) override;

        bool removePiece(boardgame::core::Position pos) override;

        bool movePiece(boardgame::core::Position from,
                       boardgame::core::Position to) override;

        // queries
        bool isInside(boardgame::core::Position) const override;

        boardgame::core::Position findKing(
            boardgame::piece::chess::ChessPieceColor color
        ) const override;

        std::map<boardgame::core::Position,
                 boardgame::piece::chess::IChessPiece*> getAllPieces() const override;

        std::map<boardgame::core::Position,
                 boardgame::piece::chess::IChessPiece*> getPieces(
                     boardgame::piece::chess::ChessPieceColor color
                 ) const override;

        // last move
        void setLastMove(std::unique_ptr<boardgame::move::chess::IChessMove> move) override;
        const boardgame::move::chess::IChessMove* lastMove() const override;

        // copy
        std::unique_ptr<IChessBoard> clone() const override;

    private:
        std::map<boardgame::core::Position, std::unique_ptr<boardgame::piece::chess::IChessPiece>> m_Board;

        std::unique_ptr<boardgame::move::chess::IChessMove> m_LastMove;
    };
}
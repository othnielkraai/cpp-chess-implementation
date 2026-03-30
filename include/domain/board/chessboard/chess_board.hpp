#pragma once

// STL
#include <vector>
#include <map>
#include <memory>
#include <optional>

// Core
#include "core/common/position.hpp"

// Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/board/IBoard.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

using namespace boardgame::core;
using namespace boardgame::move::chess;
using namespace boardgame::piece::chess;

namespace boardgame::board::chess
{
    class ChessBoard : public IChessBoard
    {
    public:
        virtual IChessPiece* getPieceAt(const Position& pos) const override;

        virtual void placePiece(const Position& pos, std::unique_ptr<IChessPiece> piece) override;

        virtual std::unique_ptr<IChessPiece> removePiece(const Position &pos) override;

        virtual void movePiece(const Position &from, const Position &to) override;

        virtual const std::map<Position, std::unique_ptr<IChessPiece>>& getPieces() const override;

        virtual std::map<Position, std::unique_ptr<IChessPiece>> getPieces(ChessPieceColor color) const override;

        // queries
        virtual bool isInside(const Position& pos) const override;

        virtual bool isEmpty(const Position &pos) const override;

        virtual bool hasPiece(const Position &pos) const override;

        virtual bool hasEnemyPiece(const Position &pos, ChessPieceColor color) const override;

        virtual bool hasFriendlyPiece(const Position &pos, ChessPieceColor color) const override;

        virtual Position findKing(ChessPieceColor color) const override;

        virtual void setLastMove(const IChessMove &move) override;

        virtual std::optional<IChessMove> getLastMove() const override;

        virtual std::unique_ptr<IChessBoard> cloneBoard() const override;

    private:
        std::map<boardgame::core::Position, std::unique_ptr<boardgame::piece::chess::IChessPiece>> m_Board;
        IChessMove& m_LastMove;
    };
}
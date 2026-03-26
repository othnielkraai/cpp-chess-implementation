#pragma once

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include <map>
#include <memory>
#include "interfaces/piece/IChessPiece.hpp"
#include "core/common/position.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

namespace boardgame::board::chess
{
    class ChessBoard : public IChessBoard
    {
    public:
        virtual boardgame::piece::chess::IChessPiece *getPieceAt(boardgame::core::Position pos) const override;
        virtual bool placePiece(boardgame::core::Position pos, std::unique_ptr<boardgame::piece::chess::IChessPiece> piece) override;
        virtual bool removePiece(boardgame::core::Position pos) override;
        virtual bool movePiece(boardgame::core::Position from, boardgame::core::Position to) override;
        virtual bool isInside(boardgame::core::Position) const override;
        virtual boardgame::core::Position findKing(boardgame::piece::chess::ChessPieceColor color) const override;
        virtual std::map<boardgame::core::Position, boardgame::piece::chess::IChessPiece*> getAllPieces() const override;
        virtual std::map<boardgame::core::Position, boardgame::piece::chess::IChessPiece*> getPieces(boardgame::piece::chess::ChessPieceColor color) const override;
        virtual void setLastMove(std::unique_ptr<boardgame::move::chess::IChessMove> move) override;
        virtual const boardgame::move::chess::IChessMove* lastMove() const override;
        virtual std::unique_ptr<IChessBoard> clone() const override;
    private:
        std::map<boardgame::core::Position, std::unique_ptr<boardgame::piece::chess::IChessPiece>> m_Board;
        std::unique_ptr<boardgame::move::chess::IChessMove> m_LastMove;
    };
}
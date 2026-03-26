#pragma once

#include "interfaces/board/IBoard.hpp"
#include "interfaces/piece/IChessPiece.hpp"
#include <vector>
#include <map>
#include <memory>

namespace boardgame::board::chess
{
    class IChessBoard : public IBoard
    {
    public:
        virtual ~IChessBoard() = default;
        virtual boardgame::piece::chess::IChessPiece* getPieceAt(boardgame::core::Position pos) const = 0;
        virtual bool placePiece(boardgame::core::Position pos, std::unique_ptr<boardgame::piece::chess::IChessPiece> piece) = 0;
        virtual bool removePiece(boardgame::core::Position pos) = 0;
        virtual bool movePiece(boardgame::core::Position from, boardgame::core::Position to) = 0;
        virtual bool isInside(boardgame::core::Position) const = 0;
        virtual boardgame::core::Position findKing(boardgame::piece::chess::ChessPieceColor color) const = 0;
        virtual std::map<boardgame::core::Position, boardgame::piece::chess::IChessPiece*> getAllPieces() const = 0;
        virtual std::map<boardgame::core::Position, boardgame::piece::chess::IChessPiece*> getPieces(boardgame::piece::chess::ChessPieceColor color) const = 0;
        virtual void setLastMove(std::unique_ptr<boardgame::move::chess::IChessMove> move) = 0 ;
        virtual const boardgame::move::chess::IChessMove* lastMove() const = 0;
        virtual std::unique_ptr<IChessBoard> clone() const = 0;
    };
}
#pragma once

#include "interfaces/piece/IChessPiece.hpp"
#include "domain/move/chessmove/strategy/rook_move_strategy.hpp"

namespace boardgame::piece::chess
{
    class RookPiece : public IChessPiece
    {
    public:
        RookPiece(ChessPieceColor color);
        virtual ChessPieceType getType() const override;
        virtual ChessPieceColor getColor() const override;
        virtual const boardgame::move::chess::IChessMoveStrategy& getMoveStrategy() const override;
        virtual bool hasMoved() const override;
        virtual void setHasMoved(bool hasMoved) override;

    private:
        boardgame::move::chess::RookMoveStrategy m_MoveStrategy;
        ChessPieceType m_PieceType = ChessPieceType::Rook;
        ChessPieceColor m_PieceColor;
        bool m_HasMoved = false;
    };
}
#pragma once

#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "domain/move/chessmove/strategy/pawn_move_strategy.hpp"

namespace boardgame::piece::chess
{
    class PawnPiece : public IChessPiece
    {
    public:
        PawnPiece(ChessPieceColor color);
        virtual ChessPieceType getType() const override;
        virtual ChessPieceColor getColor() const override;
        virtual const boardgame::move::chess::IChessMoveStrategy& getMoveStrategy() const override;
        virtual bool hasMoved() const override;
        virtual void setHasMoved(bool hasMoved) override;
        virtual std::unique_ptr<IChessPiece> clone() const override;

    private:
        boardgame::move::chess::PawnMoveStrategy m_MoveStrategy;
        ChessPieceType m_PieceType = ChessPieceType::Pawn;
        ChessPieceColor m_PieceColor;
        bool m_HasMoved = false;
    };
}
#pragma once

#include "interfaces/piece/IChessPiece.hpp"
#include "domain/move/chessmove/strategy/bishop_move_strategy.hpp"


namespace boardgame::piece::chess
{
    class BishopPiece : public IChessPiece
    {
    public:
        BishopPiece(ChessPieceColor color);
        virtual ChessPieceType getType() const override;
        virtual ChessPieceColor getColor() const override;
        virtual const boardgame::move::chess::IChessMoveStrategy& getMoveStrategy() const override;
        virtual bool hasMoved() const override;
        virtual void setHasMoved(bool hasMoved) override;
        virtual std::unique_ptr<IChessPiece> clone() const override;

    private:
        boardgame::move::chess::BishopMoveStrategy m_MoveStrategy;
        ChessPieceType m_PieceType = ChessPieceType::Bishop;
        ChessPieceColor m_PieceColor;
        bool m_HasMoved = false;
    };
}
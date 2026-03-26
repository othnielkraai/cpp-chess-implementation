#pragma once

#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "domain/move/chessmove/strategy/king_move_strategy.hpp"

namespace boardgame::piece::chess
{
    class KingPiece : public IChessPiece
    {
    public:
        KingPiece(ChessPieceColor color);
        virtual ChessPieceType getType() const override;
        virtual ChessPieceColor getColor() const override;
        virtual const boardgame::move::chess::IChessMoveStrategy& getMoveStrategy() const override;
        virtual bool hasMoved() const override;
        virtual void setHasMoved(bool hasMoved) override;
        virtual std::unique_ptr<IChessPiece> clone() const override;

    private:
        boardgame::move::chess::KingMoveStrategy m_MoveStrategy;
        ChessPieceType m_PieceType = ChessPieceType::King;
        ChessPieceColor m_PieceColor;
        bool m_HasMoved = false;
    };
}
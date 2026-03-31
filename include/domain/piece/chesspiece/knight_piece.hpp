#pragma once

#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMoveStrategy.hpp"

namespace boardgame::piece::chess
{
    class KnightPiece : public IChessPiece
    {
    public:
        //constructor
        KnightPiece(std::unique_ptr<boardgame::move::chess::IChessMoveStrategy> moveStrategy, ChessPieceColor color);
        
        virtual ChessPieceType getType() const override;
        
        virtual ChessPieceColor getColor() const override;
        
        virtual const std::unique_ptr<boardgame::move::chess::IChessMoveStrategy>& getMoveStrategy() const override;
        
        virtual bool hasMoved() const override;
        
        virtual void setHasMoved(bool hasMoved) override;   
        
        virtual std::unique_ptr<IChessPiece> clone() const override;

    private:
        std::unique_ptr<boardgame::move::chess::IChessMoveStrategy> m_MoveStrategy;
        ChessPieceType m_PieceType = ChessPieceType::Knight;
        ChessPieceColor m_PieceColor;
        bool m_HasMoved = false;
    };
}
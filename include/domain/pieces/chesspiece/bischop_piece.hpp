#pragma once

#include "interfaces/piece/IChessPiece.hpp"

namespace boardgame::piece::chess
{
    class BischopPiece : public IChessPiece
    {
    public:
        BischopPiece(ChessPieceColor color);
        virtual ChessPieceType getType() const override;
        virtual ChessPieceColor getColor() const override;

    private:
        ChessPieceType m_PieceType = ChessPieceType::Bishop;
        ChessPieceColor m_PieceColor;
    };
}
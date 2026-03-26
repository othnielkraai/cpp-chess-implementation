#pragma once

#include "interfaces/piece/IPiece.hpp"
#include "interfaces/move/chessmove/IChessMoveStrategy.hpp"

namespace boardgame::piece::chess
{
    enum class ChessPieceType
    {
        Pawn,
        Rook,
        Knight,
        Bishop,
        Queen,
        King
    };

    enum class ChessPieceColor
    {
        White,
        Black
    };

    class IChessPiece : public IPiece
    {
    public:
        virtual ~IChessPiece() = default;
        virtual ChessPieceType getType() const = 0;
        virtual ChessPieceColor getColor() const = 0;
        virtual const boardgame::move::chess::IChessMoveStrategy& getMoveStrategy() const = 0;
        virtual bool hasMoved() const = 0;
        virtual void setHasMoved(bool hasMoved) = 0;
    };

}
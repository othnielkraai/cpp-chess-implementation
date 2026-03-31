#pragma once

#include <memory>

#include "interfaces/piece/chesspiece/IChessPiece.hpp"

//using declarations
using boardgame::piece::chess::ChessPieceType;
using boardgame::piece::chess::ChessPieceColor;
using boardgame::piece::chess::IChessPiece;

namespace boardgame::piece::chess
{
    class ChessPieceFactory
    {
    public:
        static std::unique_ptr<IChessPiece> create(
            ChessPieceType type,
            ChessPieceColor color
        );
    };
}
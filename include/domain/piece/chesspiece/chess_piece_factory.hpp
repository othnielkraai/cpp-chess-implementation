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
        /// @brief Creates a new chess piece based on its type and color
        /// @param type the type of chess piece to create (e.g., Pawn, Rook, Knight, etc.)
        /// @param color the color of the chess piece to create (e.g., White, Black)
        /// @return a unique pointer to the created chess piece
        static std::unique_ptr<IChessPiece> create(
            ChessPieceType type,
            ChessPieceColor color
        );
    };
}
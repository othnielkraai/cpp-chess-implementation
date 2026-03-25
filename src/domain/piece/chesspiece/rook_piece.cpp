#include "domain/pieces/chesspiece/rook_piece.hpp"

namespace boardgame::piece::chess{

    RookPiece::RookPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType RookPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor RookPiece::getColor() const{
        return m_PieceColor;
    }

}

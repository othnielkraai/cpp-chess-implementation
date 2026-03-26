#include "domain/piece/chesspiece/bishop_piece.hpp"

namespace boardgame::piece::chess{

    BishopPiece::BishopPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType BishopPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor BishopPiece::getColor() const{
        return m_PieceColor;
    }

}

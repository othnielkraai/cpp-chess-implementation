#include "domain/pieces/chesspiece/bischop_piece.hpp"

namespace boardgame::piece::chess{

    BischopPiece::BischopPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType BischopPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor BischopPiece::getColor() const{
        return m_PieceColor;
    }

}

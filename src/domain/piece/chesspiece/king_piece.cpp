#include "domain/pieces/chesspiece/king_piece.hpp"

namespace boardgame::piece::chess{

    KingPiece::KingPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType KingPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor KingPiece::getColor() const{
        return m_PieceColor;
    }

}

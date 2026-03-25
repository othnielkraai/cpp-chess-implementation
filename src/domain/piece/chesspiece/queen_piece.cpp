#include "domain/pieces/chesspiece/queen_piece.hpp"

namespace boardgame::piece::chess{

    QueenPiece::QueenPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType QueenPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor QueenPiece::getColor() const{
        return m_PieceColor;
    }

}

#include "domain/piece/chesspiece/rook_piece.hpp"

namespace boardgame::piece::chess{

    RookPiece::RookPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType RookPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor RookPiece::getColor() const{
        return m_PieceColor;
    }

    const boardgame::move::chess::IChessMoveStrategy& RookPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

    bool RookPiece::hasMoved() const {
        return m_HasMoved;
    }

    void RookPiece::setHasMoved(bool hasMoved) {
        m_HasMoved = hasMoved;
    }
}

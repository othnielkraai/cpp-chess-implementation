#include "domain/piece/chesspiece/bishop_piece.hpp"

namespace boardgame::piece::chess{

    BishopPiece::BishopPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType BishopPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor BishopPiece::getColor() const{
        return m_PieceColor;
    }

    const boardgame::move::chess::IChessMoveStrategy& BishopPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

    bool BishopPiece::hasMoved() const {
        return m_HasMoved;
    }

    void BishopPiece::setHasMoved(bool hasMoved) {
        m_HasMoved = hasMoved;
    }

}

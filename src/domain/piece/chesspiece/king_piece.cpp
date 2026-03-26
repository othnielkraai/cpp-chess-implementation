#include "domain/piece/chesspiece/king_piece.hpp"

namespace boardgame::piece::chess{

    KingPiece::KingPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType KingPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor KingPiece::getColor() const{
        return m_PieceColor;
    }

    const boardgame::move::chess::IChessMoveStrategy& KingPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

    bool KingPiece::hasMoved() const {
        return m_HasMoved;
    }

    void KingPiece::setHasMoved(bool hasMoved) {
        m_HasMoved = hasMoved;
    }
}
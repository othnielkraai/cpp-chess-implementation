#include "domain/piece/chesspiece/rook_piece.hpp"

namespace boardgame::piece::chess{

    RookPiece::RookPiece(std::unique_ptr<boardgame::move::chess::IChessMoveStrategy> moveStrategy, ChessPieceColor color)
        : m_MoveStrategy(std::move(moveStrategy)), m_PieceColor(color) {}

    ChessPieceType RookPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor RookPiece::getColor() const{
        return m_PieceColor;
    }

    const std::unique_ptr<boardgame::move::chess::IChessMoveStrategy>& RookPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

    bool RookPiece::hasMoved() const {
        return m_HasMoved;
    }

    void RookPiece::setHasMoved(bool hasMoved) {
        m_HasMoved = hasMoved;
    }

    std::unique_ptr<IChessPiece> RookPiece::clone() const
    {
        std::unique_ptr<IChessPiece> newPiece = std::make_unique<RookPiece>(m_MoveStrategy->clone(), m_PieceColor);
        newPiece->setHasMoved(m_HasMoved);
        return newPiece;
    }
}

#include "domain/piece/chesspiece/knight_piece.hpp"

namespace boardgame::piece::chess{
    KnightPiece::KnightPiece(std::unique_ptr<boardgame::move::chess::IChessMoveStrategy> moveStrategy, ChessPieceColor color)
        : m_MoveStrategy(std::move(moveStrategy)), m_PieceColor(color) {}

    ChessPieceType KnightPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor KnightPiece::getColor() const{
        return m_PieceColor;
    }

    const std::unique_ptr<boardgame::move::chess::IChessMoveStrategy>& KnightPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

    bool KnightPiece::hasMoved() const {
        return m_HasMoved;
    }

    void KnightPiece::setHasMoved(bool hasMoved) {
        m_HasMoved = hasMoved;
    }

    std::unique_ptr<IChessPiece> KnightPiece::clone() const
    {
        auto newPiece = std::make_unique<KnightPiece>(m_PieceColor);
        newPiece->setHasMoved(m_HasMoved);
        return newPiece;
    }

}

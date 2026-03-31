#include "domain/piece/chesspiece/king_piece.hpp"

namespace boardgame::piece::chess{

    KingPiece::KingPiece(std::unique_ptr<boardgame::move::chess::IChessMoveStrategy> moveStrategy, ChessPieceColor color)
        : m_MoveStrategy(std::move(moveStrategy)), m_PieceColor(color) {}

    ChessPieceType KingPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor KingPiece::getColor() const{
        return m_PieceColor;
    }

    const std::unique_ptr<boardgame::move::chess::IChessMoveStrategy>& KingPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

    bool KingPiece::hasMoved() const {
        return m_HasMoved;
    }

    void KingPiece::setHasMoved(bool hasMoved) {
        m_HasMoved = hasMoved;
    }

    std::unique_ptr<IChessPiece> KingPiece::clone() const
    {
        auto newPiece = std::make_unique<KingPiece>(m_PieceColor);
        newPiece->setHasMoved(m_HasMoved);
        return newPiece;
    }
}
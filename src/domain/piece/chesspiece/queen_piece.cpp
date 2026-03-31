#include "domain/piece/chesspiece/queen_piece.hpp"

namespace boardgame::piece::chess{

    QueenPiece::QueenPiece(std::unique_ptr<boardgame::move::chess::IChessMoveStrategy> moveStrategy, ChessPieceColor color)
        : m_MoveStrategy(std::move(moveStrategy)), m_PieceColor(color) {}

    ChessPieceType QueenPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor QueenPiece::getColor() const{
        return m_PieceColor;
    }

    const std::unique_ptr<boardgame::move::chess::IChessMoveStrategy>& QueenPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

    bool QueenPiece::hasMoved() const {
        return m_HasMoved;
    }

    void QueenPiece::setHasMoved(bool hasMoved) {
        m_HasMoved = hasMoved;
    }

    std::unique_ptr<IChessPiece> QueenPiece::clone() const
    {
        auto newPiece = std::make_unique<QueenPiece>(m_PieceColor);
        newPiece->setHasMoved(m_HasMoved);
        return newPiece;
    }
}

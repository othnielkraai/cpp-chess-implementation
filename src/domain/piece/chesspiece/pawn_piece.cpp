#include "domain/piece/chesspiece/pawn_piece.hpp"

namespace boardgame::piece::chess{

    PawnPiece::PawnPiece(std::unique_ptr<boardgame::move::chess::IChessMoveStrategy> moveStrategy, ChessPieceColor color)
        : m_MoveStrategy(std::move(moveStrategy)), m_PieceColor(color) {}

    ChessPieceType PawnPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor PawnPiece::getColor() const{
        return m_PieceColor;
    }

    const std::unique_ptr<boardgame::move::chess::IChessMoveStrategy>& PawnPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

    bool PawnPiece::hasMoved() const {
        return m_HasMoved;
    }

    void PawnPiece::setHasMoved(bool hasMoved) {
        m_HasMoved = hasMoved;
    }

    std::unique_ptr<IChessPiece> PawnPiece::clone() const
    {
        auto newPiece = std::make_unique<PawnPiece>(m_PieceColor);
        newPiece->setHasMoved(m_HasMoved);
        return newPiece;
    }
}

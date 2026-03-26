#include "domain/piece/chesspiece/knight_piece.hpp"

namespace boardgame::piece::chess{

    KnightPiece::KnightPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType KnightPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor KnightPiece::getColor() const{
        return m_PieceColor;
    }

    const boardgame::move::chess::IChessMoveStrategy& KnightPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

}

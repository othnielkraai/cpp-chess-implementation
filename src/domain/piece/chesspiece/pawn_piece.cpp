#include "domain/piece/chesspiece/pawn_piece.hpp"

namespace boardgame::piece::chess{

    PawnPiece::PawnPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType PawnPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor PawnPiece::getColor() const{
        return m_PieceColor;
    }

    const boardgame::move::chess::IChessMoveStrategy& PawnPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

}

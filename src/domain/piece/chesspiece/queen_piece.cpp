#include "domain/piece/chesspiece/queen_piece.hpp"

namespace boardgame::piece::chess{

    QueenPiece::QueenPiece(ChessPieceColor color) : m_PieceColor{color} {}

    ChessPieceType QueenPiece::getType() const {
        return m_PieceType;
    }

    ChessPieceColor QueenPiece::getColor() const{
        return m_PieceColor;
    }

    const boardgame::move::chess::IChessMoveStrategy& QueenPiece::getMoveStrategy() const {
        return m_MoveStrategy;
    }

}

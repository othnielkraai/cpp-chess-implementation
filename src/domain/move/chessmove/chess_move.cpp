#include "domain/move/chessmove/chess_move.hpp"
#include <memory>
namespace boardgame::move::chess
{
    ChessMove::ChessMove(
        const boardgame::core::Position& from,
        const boardgame::core::Position& to
    )
        : m_from(from), m_to(to)
    {
    }

    ChessMoveType ChessMove::getMoveType() const
    {
        return m_moveType;
    }

    boardgame::core::Position ChessMove::getFrom() const
    {
        return m_from;
    }

    boardgame::core::Position ChessMove::getTo() const
    {
        return m_to;
    }

    std::unique_ptr<IChessMove> ChessMove::clone() const
    {
        return std::make_unique<ChessMove>(m_from, m_to);
    }
}
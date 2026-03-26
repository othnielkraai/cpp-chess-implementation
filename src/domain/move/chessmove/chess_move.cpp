#include "domain/move/chessmove/chess_move.hpp"

namespace boardgame::move::chess
{
    ChessMove::ChessMove(
        const boardgame::core::Position& from,
        const boardgame::core::Position& to
    )
        : m_from(from), m_to(to)
    {
    }

    boardgame::core::Position ChessMove::getFrom() const
    {
        return m_from;
    }

    boardgame::core::Position ChessMove::getTo() const
    {
        return m_to;
    }
}
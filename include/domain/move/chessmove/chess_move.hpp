#pragma once

#include "interfaces/move/chessmove/IChessMove.hpp"
#include "core/common/position.hpp"

namespace boardgame::move::chess
{
    class ChessMove : public IChessMove
    {
    public:
        ChessMove(
            const boardgame::core::Position& from,
            const boardgame::core::Position& to
        );

        boardgame::core::Position getFrom() const override;
        boardgame::core::Position getTo() const override;

    private:
        boardgame::core::Position m_from;
        boardgame::core::Position m_to;
    };
}
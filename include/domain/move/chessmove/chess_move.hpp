#pragma once

//STL
#include <memory>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/move/IMove.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

namespace boardgame::move::chess
{
    class ChessMove : public IChessMove
    {
    public:
        // constructor
        ChessMove(
            const boardgame::core::Position &from,
            const boardgame::core::Position &to,
            ChessMoveType moveType = ChessMoveType::Normal);

        boardgame::core::Position getFrom() const override;

        boardgame::core::Position getTo() const override;

        ChessMoveType getMoveType() const override;

        std::unique_ptr<IChessMove> clone() const override;

    private:
        boardgame::core::Position m_from;
        boardgame::core::Position m_to;
        ChessMoveType m_moveType = ChessMoveType::Normal;
    };
}
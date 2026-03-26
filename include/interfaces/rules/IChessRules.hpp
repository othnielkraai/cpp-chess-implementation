#pragma once

#include "interfaces/rules/IRules.hpp"
#include "interfaces/board/IChessBoard.hpp"

namespace boardgame::rules::chess
{
    class IChessRules : public IRules
    {
    public:
        virtual ~IChessRules() = default;

        virtual bool isValidMove(
            const boardgame::board::chess::IChessBoard &board,
            boardgame::core::Position from,
            boardgame::core::Position to) const = 0;
    };
}
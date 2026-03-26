#pragma once

#include "interfaces/rules/IRules.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

namespace boardgame::rules::chess
{
    class IChessRules : public IRules
    {
    public:
        virtual ~IChessRules() = default;

        virtual bool isValidMove(const boardgame::board::chess::IChessBoard &board, const boardgame::move::chess::IChessMove &move) const = 0;
    };
}
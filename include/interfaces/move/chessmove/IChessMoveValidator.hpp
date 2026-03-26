#pragma once

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

namespace boardgame::move::chess
{
    class IChessMoveValidator
    {
    public:
        virtual ~IChessMoveValidator() = default;

        virtual bool isValidMove(const boardgame::board::chess::IChessBoard &board, const boardgame::move::chess::IChessMove &move) const = 0;
    };
}
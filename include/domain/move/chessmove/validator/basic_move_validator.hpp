#pragma once

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

namespace boardgame::move::chess
{
    class BasicMoveValidator
    {
    public:
        bool isValidMove(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::move::chess::IChessMove& move
        ) const;
    };
}
#pragma once

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/move/IMoveValidator.hpp"

namespace boardgame::move::chess
{
    class IChessMoveValidator : public boardgame::move::IMoveValidator
    {
    public:
        virtual ~IChessMoveValidator() = default;

        virtual bool isValidMove(const boardgame::board::chess::IChessBoard &board, const boardgame::move::chess::IChessMove &move) const = 0;
    };
}
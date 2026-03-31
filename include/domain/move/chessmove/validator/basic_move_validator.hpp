#pragma once

//STL
#include <vector>
#include <memory>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

//using declarations
using boardgame::board::chess::IChessBoard;
using boardgame::move::chess::IChessMove;
using boardgame::move::chess::IChessMoveValidator;

namespace boardgame::move::chess
{
    class BasicMoveValidator : public IChessMoveValidator
    {
    public:
        virtual bool isValidMove(
            const IChessBoard& board,
            const IChessMove& move
        ) const override;
    };
}
#pragma once

#include <vector>
#include <memory>
#include <array>

#include "interfaces/move/chessmove/IChessMoveStrategy.hpp"
#include "interfaces/move/IMoveStrategy.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"

#include "core/common/position.hpp"

using namespace boardgame::core;
using namespace boardgame::board::chess;
using namespace boardgame::piece::chess;

namespace boardgame::move::chess
{
    class KingMoveStrategy : public IChessMoveStrategy
    {
    public:
        std::vector<std::unique_ptr<IChessMove>> generateMoves(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::piece::chess::IChessPiece& piece,
            const boardgame::core::Position& from
        ) const override;
    };
}
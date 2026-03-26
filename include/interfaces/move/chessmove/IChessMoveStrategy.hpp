#pragma once

#include <vector>
#include <memory>

#include "interfaces/move/IMoveStrategy.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/IChessPiece.hpp"
#include "core/common/position.hpp"

namespace boardgame::move::chess
{
    class IChessMoveStrategy : public boardgame::move::IMoveStrategy
    {
    public:
        virtual ~IChessMoveStrategy() = default;

        virtual std::vector<std::shared_ptr<IChessMove>> generateMoves(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::piece::chess::IChessPiece& piece,
            const boardgame::core::Position& from
        ) const = 0;
    };
}
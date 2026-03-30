#pragma once

#include <vector>
#include <memory>

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
    class RookMoveStrategy : public IChessMoveStrategy
    {
    public:
        virtual std::vector<std::unique_ptr<IChessMove>> generateMoves( const IChessBoard& board, const IChessPiece& piece, const Position& from) const override;
    };
}
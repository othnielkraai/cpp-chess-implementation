#pragma once

//STL
#include <vector>
#include <memory>
#include <array>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/move/chessmove/IChessMoveStrategy.hpp"
#include "interfaces/move/IMoveStrategy.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"

//domain
#include "domain/move/chessmove/chess_move.hpp"

//using declarations for commonly used types
using namespace boardgame::core;
using namespace boardgame::board::chess;
using namespace boardgame::piece::chess;

namespace boardgame::move::chess
{
    class QueenMoveStrategy : public IChessMoveStrategy
    {
    public:
        virtual std::vector<std::unique_ptr<IChessMove>> generateMoves(
            const IChessBoard& board,
            const IChessPiece& piece,
            const Position& from
        ) const override;

        virtual std::unique_ptr<IChessMoveStrategy> clone() const override;
    };
}
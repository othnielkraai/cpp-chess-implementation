#pragma once

#include <vector>
#include <memory>

#include "interfaces/move/IMoveGenerator.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/IChessPiece.hpp"
#include "interfaces/piece/IChessPiece.hpp"

namespace boardgame::move::chess
{
    class IChessMoveGenerator : public boardgame::move::IMoveGenerator
    {
    public:
        virtual ~IChessMoveGenerator() = default;

        virtual std::vector<std::shared_ptr<IChessMove>> generateMoves(
            const boardgame::board::chess::IChessBoard& board,
            const boardgame::piece::chess::IChessPiece& piece,
            const boardgame::core::Position& from
        ) const = 0;
    };
}
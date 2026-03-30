#pragma once

#include <vector>
#include <memory>

#include "interfaces/move/IMoveStrategy.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "core/common/position.hpp"

namespace boardgame::board::chess
{
    class IChessBoard;
}

namespace boardgame::piece::chess
{
    class IChessPiece;
}

using namespace boardgame::core;
using namespace boardgame::board::chess;
using namespace boardgame::piece::chess;

namespace boardgame::move::chess
{
    class IChessMoveStrategy : public boardgame::move::IMoveStrategy
    {
    public:
        /// @brief Virtual destructor for the chess move strategy interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer
        virtual ~IChessMoveStrategy() = default;

        /// @brief Generates all legal moves for a given chess piece on the board.
        /// @param board The chess board to generate moves for.
        /// @param piece The chess piece to generate moves for.
        /// @param from The position from which to generate moves.
        /// @return A vector of unique pointers to the generated legal moves.
        virtual std::vector<std::unique_ptr<IChessMove>> generateMoves( const IChessBoard& board, const IChessPiece& piece, const Position& from
        ) const = 0;
    };
}
#pragma once

//STL
#include <vector>
#include <memory>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"

//forward declaration of IChessBoard
namespace boardgame::board::chess
{
    class IChessBoard;
}

//forward declaration of IChessPiece
namespace boardgame::piece::chess
{
    class IChessPiece;
}

//forward declaration of IChessMove
namespace boardgame::move::chess
{
    class IChessMove;
}

//using declarations for commonly used types
using namespace boardgame::core;
using namespace boardgame::board::chess;
using namespace boardgame::piece::chess;

namespace boardgame::move::chess
{
    class IChessMoveStrategy
    {
    public:
        /// @brief Virtual destructor for the chess move strategy interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer
        virtual ~IChessMoveStrategy() = default;

        /// @brief Generates all pseudolegal moves for a given chess piece on the board.
        /// @param board The chess board to generate moves for.
        /// @param piece The chess piece to generate moves for.
        /// @param from The position from which to generate moves.
        /// @return A vector of unique pointers to the generated legal moves.
        virtual std::vector<std::unique_ptr<IChessMove>> generateMoves( const IChessBoard& board, const IChessPiece& piece, const Position& from
        ) const = 0;

        /// @brief Creates a copy of the chess move strategy.
        /// @return A unique pointer to the cloned chess move strategy.
        virtual std::unique_ptr<IChessMoveStrategy> clone() const = 0;
    };
}
#pragma once

//STL
#include <vector>
#include <memory>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/IMoveGenerator.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"

//using declarations
using boardgame::core::Position;
using boardgame::board::chess::IChessBoard;
using boardgame::piece::chess::IChessPiece;

namespace boardgame::move::chess
{
    class IChessMoveGenerator : public boardgame::move::IMoveGenerator
    {
    public:
        /// @brief Virtual destructor for the chess move generator interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer
        virtual ~IChessMoveGenerator() = default;

        /// @brief Generates all legal moves for a given  board.
        /// @param board The chess board to generate moves for.
        /// @return A vector of unique pointers to the generated legal moves.
        virtual std::vector<std::unique_ptr<IChessMove>> generateMoves(const IChessBoard &board) const = 0;
    };
}
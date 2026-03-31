#pragma once

#include <vector>
#include <memory>

#include "interfaces/move/IMoveGenerator.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"

using namespace boardgame::core;
using namespace boardgame::board::chess;
using namespace boardgame::piece::chess;

namespace boardgame::move::chess
{
    class IChessMoveGenerator : public boardgame::move::IMoveGenerator
    {
    public:
        /// @brief Virtual destructor for the chess move generator interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer
        virtual ~IChessMoveGenerator() = default;

        /// @brief Generates all legal moves for a given chess piece on the board.
        /// @param board The chess board to generate moves for.
        /// @return A vector of unique pointers to the generated legal moves.
        virtual std::vector<std::unique_ptr<IChessMove>> generateMoves(const IChessBoard &board) const = 0;
    };
}
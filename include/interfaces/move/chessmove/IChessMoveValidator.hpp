#pragma once

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/move/IMoveValidator.hpp"

namespace boardgame::move::chess
{
    class IChessMoveValidator : public boardgame::move::IMoveValidator
    {
    public:
        /// @brief Virtual destructor for the chess move validator interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer
        virtual ~IChessMoveValidator() = default;

        /// @brief Validates whether a given chess move is legal on the provided chess board.
        /// @param board The chess board to validate the move against.
        /// @param move The chess move to validate.
        /// @return True if the move is valid, false otherwise.
        virtual bool isValidMove(const boardgame::board::chess::IChessBoard &board, const boardgame::move::chess::IChessMove &move) const = 0;
    };
}
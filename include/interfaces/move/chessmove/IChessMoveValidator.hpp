#pragma once

//Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/move/IMoveValidator.hpp"

//using declarations
using boardgame::board::chess::IChessBoard;
using boardgame::move::chess::IChessMove;

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
        virtual bool isValidMove(const IChessBoard &board, const IChessMove &move) const = 0;
    };
}
#pragma once

//STL
#include <vector>
#include <memory>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

//using declarations
using boardgame::board::chess::IChessBoard;
using boardgame::move::chess::IChessMove;
using boardgame::move::chess::IChessMoveValidator;

namespace boardgame::move::chess
{
    class ChessMoveValidator : public IChessMoveValidator
    {
    public:
        bool isValidMove(
            const IChessBoard& board,
            const IChessMove& move
        ) const override;

        /// @brief  Adds a move validator to the chess move validator.
        /// @param validator The move validator to add. It will be used to validate moves in the order they were added.
        void addValidator(std::unique_ptr<IChessMoveValidator> validator);

    private:
        std::vector<std::unique_ptr<IChessMoveValidator>> validators;
    };
}
#include "domain/move/chessmove/validator/chess_move_validator.hpp"

namespace boardgame::move::chess
{
    bool ChessMoveValidator::isValidMove(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::move::chess::IChessMove& move
    ) const
    {
        for (const auto& validator : validators)
        {
            if (!validator->isValidMove(board, move))
            {
                return false;
            }
        }

        return true;
    }

    void ChessMoveValidator::addValidator(std::unique_ptr<IChessMoveValidator> validator)
    {
        validators.push_back(std::move(validator));
    }
}
#include "domain/move/chessmove/validator/chess_move_validator.hpp"
#include "domain/move/chessmove/validator/chess_validation_utils.hpp"
#include "domain/move/chessmove/validator/basic_move_validator.hpp"
#include "domain/move/chessmove/validator/piece_move_validator.hpp"
#include "domain/move/chessmove/validator/king_safety_validator.hpp"


namespace boardgame::move::chess
{
    ChessMoveValidator::ChessMoveValidator()
    {
        validators.push_back(std::make_unique<BasicMoveValidator>());
        std::unique_ptr<IChessMoveValidator> specialMoveValidator = std::make_unique<SpecialMoveValidator>();
        validators.push_back(std::make_unique<PieceMoveValidator>(std::move(specialMoveValidator)));
        validators.push_back(std::make_unique<KingSafetyValidator>());
    }

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
}
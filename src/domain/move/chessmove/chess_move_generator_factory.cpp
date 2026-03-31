#include "domain/move/chessmove/chess_move_generator_factory.hpp"

#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"
#include "domain/move/chessmove/chess_move_generator.hpp"
#include "domain/move/chessmove/validator/chess_move_validator.hpp"
#include "domain/move/chessmove/validator/basic_move_validator.hpp"
#include "domain/move/chessmove/validator/piece_move_validator.hpp"
#include "domain/move/chessmove/validator/special_move_validator.hpp"

namespace boardgame::move::chess
{
    std::unique_ptr<IChessMoveGenerator> ChessMoveGeneratorFactory::create()
    {
        auto moveValidator = std::make_unique<ChessMoveValidator>();
        moveValidator->addValidator(std::make_unique<BasicMoveValidator>());
        moveValidator->addValidator(std::make_unique<PieceMoveValidator>(std::make_unique<SpecialMoveValidator>()));
        moveValidator->addValidator(std::make_unique<KingSafetyValidator>());
        return std::make_unique<ChessMoveGenerator>(std::move(moveValidator));
    }
}
#pragma once

#include <memory>
#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"
#include "domain/move/chessmove/validator/chess_move_validator.hpp"

namespace boardgame::move::chess
{
    class ChessMoveGeneratorFactory
    {
    public:
        static std::unique_ptr<IChessMoveGenerator> create();
    };
}
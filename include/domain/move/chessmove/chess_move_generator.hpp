#pragma once

#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

namespace boardgame::move::chess
{
    class ChessMoveGenerator : public IChessMoveGenerator
    {
    public:
        /// @brief Constructs a ChessMoveGenerator with the given move validator.
        /// @param moveValidator A unique pointer to an IChessMoveValidator used to validate generated moves.
        ChessMoveGenerator(std::unique_ptr<IChessMoveValidator> moveValidator);

        virtual std::vector<std::unique_ptr<IChessMove>> generateMoves(const IChessBoard &board) const override;

    private:
        std::unique_ptr<IChessMoveValidator> m_MoveValidator;
    };
}
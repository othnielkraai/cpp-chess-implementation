#pragma once

//STL
#include <vector>
#include <memory>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/IMoveGenerator.hpp"
#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"

//using declarations
using boardgame::core::Position;
using boardgame::board::chess::IChessBoard;
using boardgame::piece::chess::IChessPiece;
using boardgame::move::chess::IChessMove;
using boardgame::move::chess::IChessMoveValidator;

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
#pragma once

#include <memory>

#include "core/Position.hpp"

#include "interfaces/player/IPlayer.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/piece/chesspiece/ChessPieceColor.hpp"

namespace boardgame::player::chess
{
    class IChessPlayer : public IPlayer
    {
    public:
        virtual ~IChessPlayer() = default;

        /// @brief Gets the color of the player
        virtual ChessPieceColor getColor() const = 0;

        /// @brief Let the player choose a move
        virtual std::unique_ptr<IChessMove> chooseMove(
            const boardgame::board::chess::IChessBoard& board
        ) = 0;
    };
}

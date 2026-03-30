#pragma once

#include <vector>
#include <memory>
#include "core/common/position.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/game/IGame.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

using namespace boardgame::core;
using namespace boardgame::piece::chess;
using namespace boardgame::board::chess;

namespace boardgame::game::chess
{
    enum class GameState
    {
        Ongoing,
        Check,
        Checkmate,
        Stalemate,
        Draw
    };

    /// @brief class responsible controlling the game
    class IChessGame : public boardgame::game::IGame
    {
    public:
        /// @brief Virtual destructor for the chess game interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer
        virtual ~IChessGame() = default;

        /// @brief Gets the current state of the chess board.
        /// @return A reference to the current chess board.
        virtual const IChessBoard &getBoard() const = 0;

        /// @brief Attempts to make a move in the chess game.
        /// @param move The chess move to make.
        virtual bool makeMove(const IChessMove &move) = 0;

        /// @brief Gets all legal moves for a piece at the specified position.
        /// @param position The position of the piece to get legal moves for.
        virtual std::vector<std::shared_ptr<IChessMove>> getLegalMoves(const Position &position) const = 0;

        /// @brief Gets the current state of the game (e.g., ongoing, check, checkmate).
        /// @return The current state of the game.
        virtual GameState getGameState() const = 0;
    };
}
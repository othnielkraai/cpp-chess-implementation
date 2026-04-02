#pragma once

#include <vector>
#include <memory>
#include "core/common/position.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/game/IGame.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"
#include "interfaces/player/IPlayer.hpp"
#include "interfaces/history/chesshistory/IChessHistory.hpp"

using namespace boardgame::core;
using namespace boardgame::piece::chess;
using namespace boardgame::board::chess;
using boardgame::player::IPlayer;
using boardgame::history::chess::IChessHistory;

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

        /// @brief Gets the current player in the chess game.
        /// @return A reference to the current player.
        virtual const IPlayer &getCurrentPlayer() const = 0;

        /// @brief Gets the white player in the chess game.
        /// @return A reference to the white player.
        virtual const IPlayer &getwhitePlayer() const = 0;

        /// @brief Gets the black player in the chess game.
        /// @return A reference to the black player.
        virtual const IPlayer &getBlackPlayer() const = 0;

        /// @brief Switches the current player in the chess game.
        /// @details This function changes the turn to the other player.
        virtual void switchPlayer() = 0;

        /// @brief Gets the history of moves made in the chess game.
        /// @return A reference to the chess history.
        virtual const IChessHistory &getHistory() const = 0;

        /// @brief Undoes the last move made in the chess game.
        /// @return True if the move was successfully undone, false otherwise.
        virtual bool undoMove() = 0;

        /// @brief Redoes the last undone move in the chess game.
        /// @return True if the move was successfully redone, false otherwise.
        virtual bool redoMove() = 0;

        /// @brief Attempts to make a move in the chess game.
        /// @param move The chess move to make.
        virtual bool makeMove(const IChessMove &move) = 0;

        /// @brief Gets all legal moves for a piece at the specified position.
        /// @param position The position of the piece to get legal moves for.
        virtual std::vector<std::unique_ptr<IChessMove>> getLegalMoves(const Position &position) const = 0;

        /// @brief Gets the current state of the game (e.g., ongoing, check, checkmate).
        /// @return The current state of the game.
        virtual GameState getGameState() const = 0;

        /// @brief Checks if the game is over (e.g., checkmate, stalemate).
        /// @return True if the game is over, false otherwise.
        virtual bool isGameOver() const = 0;

        /// @brief Resets the chess game to its initial state.
        /// @details This function clears the board, resets the players, and clears the move history.
        virtual void resetGame() = 0;
    };
}
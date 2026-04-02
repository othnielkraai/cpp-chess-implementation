#pragma once

#include <vector>
#include <memory>
#include "core/common/position.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

#include "interfaces/history/chesshistory/IChessHistory.hpp"
#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"
#include "interfaces/player/chessplayer/IChessPlayer.hpp"

using boardgame::board::chess::IChessBoard;
using boardgame::core::Position;
using boardgame::history::chess::IChessHistory;
using boardgame::move::chess::IChessMove;
using boardgame::move::chess::IChessMoveGenerator;
using boardgame::player::chess::IChessPlayer;

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
    class IChessGame
    {
    public:
        /// @brief Virtual destructor for the chess game interface.
        /// @details This ensures that derived classes can clean up resources properly when deleted through a pointer
        virtual ~IChessGame() = default;

        virtual void addBoard(std::unique_ptr<IChessBoard> board) = 0;

        /// @brief Gets the current state of the chess board.
        /// @return A reference to the current chess board.
        virtual const IChessBoard &getBoard() const = 0;

        /// @brief Attempts to make a move in the chess game.
        /// @param move The chess move to make.
        virtual bool makeMove(const IChessMove &move) = 0;

        virtual void addWhitePlayer(std::unique_ptr<IChessPlayer> player) = 0;
        virtual void addBlackPlayer(std::unique_ptr<IChessPlayer> player) = 0;

        /// @brief Gets the current player in the chess game.
        /// @return A reference to the current player.
        virtual const IChessPlayer &getCurrentPlayer() const = 0;

        /// @brief Gets the white player in the chess game.
        /// @return A reference to the white player.
        virtual const IChessPlayer &getWhitePlayer() const = 0;

        /// @brief Gets the black player in the chess game.
        /// @return A reference to the black player.
        virtual const IChessPlayer &getBlackPlayer() const = 0;

        virtual void addMoveGenerator(std::unique_ptr<IChessMoveGenerator> moveGenerator) = 0;

        /// @brief Gets all legal moves for a piece at the specified position.
        /// @param position The position of the piece to get legal moves for.
        virtual std::vector<std::unique_ptr<IChessMove>> getLegalMoves(const Position &position) const = 0;

        virtual void addHistory(std::unique_ptr<IChessHistory> history) = 0;

        /// @brief Gets the history of moves made in the chess game.
        /// @return A reference to the chess history.
        virtual const IChessHistory &getHistory() const = 0;

        /// @brief Undoes the last move made in the chess game.
        /// @return True if the move was successfully undone, false otherwise.
        virtual bool undoMove() = 0;

        /// @brief Redoes the last undone move in the chess game.
        /// @return True if the move was successfully redone, false otherwise.
        virtual bool redoMove() = 0;

        /// @brief Gets the current state of the game (e.g., ongoing, check, checkmate).
        /// @return The current state of the game.
        virtual GameState getGameState() const = 0;

        /// @brief Checks if the game is over (e.g., checkmate, stalemate).
        /// @return True if the game is over, false otherwise.
        virtual bool isGameOver() const = 0;

        /// @brief Resets the chess game to its initial state.
        /// @details This function clears the board, resets the players, and clears the move history.
        virtual void resetGame() = 0;

    private:
        /// @brief Switches the current player in the chess game.
        /// @details This function changes the turn to the other player.
        virtual void switchPlayer() = 0;
    };
}
#pragma once

// STL
#include <memory>
#include <vector>

// Interfaces
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/game/chessgame/IChessGame.hpp"
#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"
#include "interfaces/history/chesshistory/IChessHistory.hpp"

namespace boardgame::game::chess
{
    class ChessGame : public IChessGame
    {
    public:
        ChessGame();
        ~ChessGame() override = default;

        void addBoard(std::unique_ptr<IChessBoard> board) override;
        const IChessBoard& getBoard() const override;

        bool makeMove(const IChessMove& move) override;

        void addWhitePlayer(std::unique_ptr<IChessPlayer> player) override;
        void addBlackPlayer(std::unique_ptr<IChessPlayer> player) override;

        const IChessPlayer& getCurrentPlayer() const override;
        const IChessPlayer& getWhitePlayer() const override;
        const IChessPlayer& getBlackPlayer() const override;

        void addMoveGenerator(std::unique_ptr<IChessMoveGenerator> moveGenerator) override;
        std::vector<std::unique_ptr<IChessMove>> getLegalMoves(const Position& position) const override;

        void addHistory(std::unique_ptr<IChessHistory> history) override;
        const IChessHistory& getHistory() const override;

        bool undoMove() override;
        bool redoMove() override;

        GameState getGameState() const override;
        bool isGameOver() const override;

        void resetGame() override;

    private:
        void switchPlayer();
        void updateGameState();

    private:
        std::unique_ptr<IChessBoard> m_Board;
        std::unique_ptr<IChessPlayer> m_WhitePlayer;
        std::unique_ptr<IChessPlayer> m_BlackPlayer;
        IChessPlayer* m_CurrentPlayer;
        std::unique_ptr<IChessMoveGenerator> m_MoveGenerator;
        std::unique_ptr<IChessHistory> m_History;
        GameState m_GameState;
    };
}
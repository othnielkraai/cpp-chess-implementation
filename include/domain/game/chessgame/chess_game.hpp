// #pragma once

// // STL
// #include <memory>
// #include <vector>

// // Interfaces
// #include "interfaces/board/chessboard/IChessBoard.hpp"
// #include "interfaces/game/chessgame/IChessGame.hpp"
// #include "interfaces/move/chessmove/IChessMoveGenerator.hpp"
// #include "interfaces/move/chessmove/IChessMoveValidator.hpp"

// namespace boardgame::game::chess
// {
//     class ChessGame : public IChessGame
//     {
//     public:
//         ChessGame(
//             std::unique_ptr<boardgame::board::chess::IChessBoard> board,
//             std::unique_ptr<boardgame::move::chess::IChessMoveGenerator> moveGenerator,
//             std::unique_ptr<boardgame::move::chess::IChessMoveValidator> moveValidator);

//         virtual const boardgame::board::chess::IChessBoard &getBoard() const override;
//         bool makeMove(const boardgame::move::chess::IChessMove &move) override;

//         std::vector<std::shared_ptr<boardgame::move::chess::IChessMove>> getLegalMoves(
//             const boardgame::core::Position &position) const override;

//         virtual GameState getGameState() const override;


//     private:
//         bool isPlayersPiece(const boardgame::core::Position &position) const;
//         void switchPlayer();

//         bool applyMove(const boardgame::move::chess::IChessMove &move);
//         bool applyNormalMove(const boardgame::move::chess::IChessMove &move);
//         bool applyCastlingMove(const boardgame::move::chess::IChessMove &move);
//         bool applyEnPassantMove(const boardgame::move::chess::IChessMove &move);
//         bool applyPromotionMove(const boardgame::move::chess::IChessMove &move);

//         bool hasAnyLegalMoves(boardgame::piece::chess::ChessPieceColor color) const;

//         bool isSquareAttacked(
//             const boardgame::board::chess::IChessBoard &board,
//             const boardgame::core::Position &square,
//             boardgame::piece::chess::ChessPieceColor attackingColor) const;

//         bool canPieceAttackSquare(
//             const boardgame::board::chess::IChessBoard &board,
//             const boardgame::core::Position &from,
//             const boardgame::piece::chess::IChessPiece &piece,
//             const boardgame::core::Position &target) const;

//         bool isPathClear(
//             const boardgame::board::chess::IChessBoard &board,
//             const boardgame::core::Position &from,
//             const boardgame::core::Position &to) const;

//         int getStep(int delta) const;

//         boardgame::piece::chess::ChessPieceColor oppositeColor(
//             boardgame::piece::chess::ChessPieceColor color) const;

//         int pawnForwardDirection(
//             boardgame::piece::chess::ChessPieceColor color) const;

//         std::unique_ptr<boardgame::board::chess::IChessBoard> m_Board;
//         std::unique_ptr<boardgame::move::chess::IChessMoveGenerator> m_MoveGenerator;
//         std::unique_ptr<boardgame::move::chess::IChessMoveValidator> m_MoveValidator;
//         boardgame::piece::chess::ChessPieceColor m_CurrentPlayer;
//     };
// }
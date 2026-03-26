#pragma once

#include <vector>
#include <memory>
#include "core/common/position.hpp"
#include "interfaces/piece/IChessPiece.hpp"
#include "interfaces/game/IGame.hpp"
#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

namespace boardgame::game::chess
{
    class IChessGame : public boardgame::game::IGame
    {
    public:
        virtual ~IChessGame() = default;
        virtual const boardgame::board::chess::IChessBoard &getBoard() const = 0;
        virtual void makeMove(const boardgame::move::chess::IChessMove &move) = 0;
        virtual std::vector<std::shared_ptr<boardgame::move::chess::IChessMove>> getLegalMoves(const boardgame::core::Position &position) const = 0;
        virtual boardgame::piece::chess::ChessPieceColor getCurrentPlayer() const = 0;
        virtual bool isCheck() const = 0;
        virtual bool isCheckmate() const = 0;
        virtual bool isStalemate() const = 0;
    };
}
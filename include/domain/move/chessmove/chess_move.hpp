#pragma once

//STL
#include <memory>

//core
#include "core/common/position.hpp"

//Interfaces
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

// using declarations
using boardgame::core::Position;
using boardgame::piece::chess::ChessPieceType;

namespace boardgame::move::chess
{
    class ChessMove : public IChessMove
    {
    public:
        // constructor
        ChessMove(
            const boardgame::core::Position &from,
            const boardgame::core::Position &to,
            ChessMoveType moveType = ChessMoveType::Normal,
            std::optional<boardgame::piece::chess::ChessPieceType> promotedPiece = std::nullopt
        );

        boardgame::core::Position getFrom() const override;

        boardgame::core::Position getTo() const override;

        ChessMoveType getMoveType() const override;

        std::unique_ptr<IChessMove> clone() const override;

        std::optional<ChessPieceType> getPromotedPieceType() const override;

    private:
        boardgame::core::Position m_from;
        boardgame::core::Position m_to;
        ChessMoveType m_moveType = ChessMoveType::Normal;
        std::optional<boardgame::piece::chess::ChessPieceType> m_promotedPieceType;
    };
}
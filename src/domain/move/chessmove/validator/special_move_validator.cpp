#include "domain/move/chessmove/validator/special_move_validator.hpp"
#include "domain/move/chessmove/validator/chess_validation_utils.hpp"

#include <cmath>

namespace boardgame::move::chess
{
    bool SpecialMoveValidator::isValidMove(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move) const
    {
        auto *piece = board.getPieceAt(move.getFrom());
        switch (move.getMoveType())
        {
        case boardgame::move::chess::ChessMoveType::Castling:
            return isCastlingMoveValid(board, move, *piece);
            break;
        case boardgame::move::chess::ChessMoveType::EnPassant:
            return isEnPassantMoveValid(board, move, *piece);
            break;
        case boardgame::move::chess::ChessMoveType::Promotion:
            return isPromotionMoveValid(board, move, *piece);
            break;
        case boardgame::move::chess::ChessMoveType::PawnDoubleMove:
            return isPawnDoubleMoveValid(board, move, *piece);
            break;

        default:
            return true;
            break;
        }
    }
    bool SpecialMoveValidator::isPawnDoubleMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &pawn) const
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        const int forward = utils::pawnForwardDirection(pawn.getColor());
        const int dRow = to.row - from.row;
        const int dCol = to.col - from.col;

        if (dCol != 0 || dRow != 2 * forward)
        {
            return false;
        }

        if (from.row != utils::pawnStartRow(pawn.getColor()))
        {
            return false;
        }

        if (pawn.hasMoved())
        {
            return false;
        }

        boardgame::core::Position middle{from.row + forward, from.col};

        if (!board.isEmpty(middle) && !board.isEmpty(to))
        {
            return false;
        }

        return true;
    }

    bool SpecialMoveValidator::isCastlingMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &king) const
    {
        using boardgame::piece::chess::ChessPieceType;

        if (king.getType() != ChessPieceType::King)
        {
            return false;
        }

        if (king.hasMoved())
        {
            return false;
        }

        const auto from = move.getFrom();
        const auto to = move.getTo();

        if (from.row != to.row)
        {
            return false;
        }

        if (std::abs(to.col - from.col) != 2)
        {
            return false;
        }

        const bool kingSide = to.col > from.col;
        const int rookCol = kingSide ? 7 : 0;

        boardgame::core::Position rookPos{from.row, rookCol};
        auto *rook = board.getPieceAt(rookPos);

        if (rook == nullptr)
        {
            return false;
        }

        if (rook->getType() != ChessPieceType::Rook)
        {
            return false;
        }

        if (rook->getColor() != king.getColor())
        {
            return false;
        }

        if (rook->hasMoved())
        {
            return false;
        }

        return utils::isPathClear(board, from, rookPos);
    }

    bool SpecialMoveValidator::isEnPassantMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &pawn) const
    {
        using boardgame::piece::chess::ChessPieceType;

        const auto from = move.getFrom();
        const auto to = move.getTo();

        const int forward = utils::pawnForwardDirection(pawn.getColor());

        if (to.row - from.row != forward || std::abs(to.col - from.col) != 1)
        {
            return false;
        }

        if (!board.isEmpty(to))
        {
            return false;
        }

        const auto *lastMove = board.getLastMove();
        if (lastMove == nullptr)
        {
            return false;
        }

        if (lastMove->getMoveType() != ChessMoveType::PawnDoubleMove)
        {
            return false;
        }

        auto *adjacentPiece = board.getPieceAt({from.row, to.col});
        if (adjacentPiece == nullptr)
        {
            return false;
        }

        if (adjacentPiece->getType() != ChessPieceType::Pawn)
        {
            return false;
        }

        if (adjacentPiece->getColor() == pawn.getColor())
        {
            return false;
        }

        if (lastMove->getTo() != boardgame::core::Position{from.row, to.col})
        {
            return false;
        }

        return true;
    }

    bool SpecialMoveValidator::isPromotionMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &pawn) const
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        const int forward = utils::pawnForwardDirection(pawn.getColor());
        const int dRow = to.row - from.row;
        const int dCol = to.col - from.col;

        const bool oneForward =
            (dCol == 0 && dRow == forward && board.isEmpty(to));

        const bool diagonalCapture =
            (std::abs(dCol) == 1 &&
             dRow == forward &&
             board.hasEnemyPiece(to, pawn.getColor()));

        if (!(oneForward || diagonalCapture))
        {
            return false;
        }

        return to.row == utils::promotionRow(pawn.getColor());
    }
}
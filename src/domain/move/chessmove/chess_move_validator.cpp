#include "domain/move/chessmove/chess_move_validator.hpp"

#include <cmath>

namespace boardgame::move::chess
{
    bool ChessMoveValidator::isValidMove(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move) const
    {
        auto *piece = board.getPieceAt(move.getFrom());

        return isBasicMoveValid(board, move) && piece != nullptr && isMoveShapeValid(board, move, *piece) && !leavesKingInCheck(board, move);
    }

    bool ChessMoveValidator::isBasicMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move) const
    {
        if (!board.isInside(move.getFrom()) || !board.isInside(move.getTo()))
            return false;
        if (move.getFrom() == move.getTo())
            return false;
        if (board.getPieceAt(move.getFrom()) == nullptr)
            return false;
        if (isDestinationOccupiedByOwnPiece(board, move) && move.getMoveType() != ChessMoveType::EnPassant)
            return false;

        return true;
    }

    bool ChessMoveValidator::isMoveShapeValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &piece) const
    {
        using boardgame::piece::chess::ChessPieceType;

        switch (piece.getType())
        {
        case ChessPieceType::Pawn:
            return isPawnMoveValid(board, move, piece);

        case ChessPieceType::Knight:
            return isKnightMoveValid(move);

        case ChessPieceType::Bishop:
            return isBishopMoveValid(board, move);

        case ChessPieceType::Rook:
            return isRookMoveValid(board, move);

        case ChessPieceType::Queen:
            return isQueenMoveValid(board, move);

        case ChessPieceType::King:
            return isKingMoveValid(board, move, piece);

        default:
            return false;
        }
    }

    bool ChessMoveValidator::isPawnMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &piece) const
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        const int dRow = to.row - from.row;
        const int dCol = to.col - from.col;
        const int forward = pawnForwardDirection(piece.getColor());

        switch (move.getMoveType())
        {
        case ChessMoveType::Normal:
        {
            const bool oneForward = (dCol == 0 && dRow == forward && !isOccupied(board, to));
            const bool diagonalCapture =
                (std::abs(dCol) == 1 &&
                 dRow == forward &&
                 isOccupiedByEnemy(board, to, piece.getColor()));

            if (!(oneForward || diagonalCapture))
            {
                return false;
            }

            if (to.row == promotionRow(piece.getColor()))
            {
                return false;
            }

            return true;
        }

        case ChessMoveType::PawnDoubleMove:
        {
            if (dCol != 0 || dRow != 2 * forward)
            {
                return false;
            }

            if (from.row != pawnStartRow(piece.getColor()))
            {
                return false;
            }

            if (piece.hasMoved())
            {
                return false;
            }

            boardgame::core::Position middle{from.row + forward, from.col};

            if (isOccupied(board, middle) || isOccupied(board, to))
            {
                return false;
            }

            return true;
        }

        case ChessMoveType::EnPassant:
            return isEnPassantMoveValid(board, move, piece);

        case ChessMoveType::Promotion:
            return isPromotionMoveValid(board, move, piece);

        default:
            return false;
        }
    }

    bool ChessMoveValidator::isKnightMoveValid(
        const boardgame::move::chess::IChessMove &move) const
    {
        const int dRow = std::abs(rowDelta(move));
        const int dCol = std::abs(colDelta(move));

        return (dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2);
    }

    bool ChessMoveValidator::isBishopMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move) const
    {
        const int dRow = std::abs(rowDelta(move));
        const int dCol = std::abs(colDelta(move));

        if (dRow != dCol)
        {
            return false;
        }

        return isPathClear(board, move.getFrom(), move.getTo());
    }

    bool ChessMoveValidator::isRookMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move) const
    {
        const int dRow = std::abs(rowDelta(move));
        const int dCol = std::abs(colDelta(move));

        if (!((dRow == 0 && dCol > 0) || (dCol == 0 && dRow > 0)))
        {
            return false;
        }

        return isPathClear(board, move.getFrom(), move.getTo());
    }

    bool ChessMoveValidator::isQueenMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move) const
    {
        const int dRow = std::abs(rowDelta(move));
        const int dCol = std::abs(colDelta(move));

        const bool diagonal = (dRow == dCol);
        const bool straight = (dRow == 0 && dCol > 0) || (dCol == 0 && dRow > 0);

        if (!(diagonal || straight))
        {
            return false;
        }

        return isPathClear(board, move.getFrom(), move.getTo());
    }

    bool ChessMoveValidator::isKingMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &piece) const
    {
        const int dRow = std::abs(rowDelta(move));
        const int dCol = std::abs(colDelta(move));

        if (move.getMoveType() == ChessMoveType::Castling)
        {
            return isCastlingMoveValid(board, move, piece);
        }

        if (move.getMoveType() != ChessMoveType::Normal)
        {
            return false;
        }

        return dRow <= 1 && dCol <= 1;
    }

    bool ChessMoveValidator::isCastlingMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &king) const
    {
        if (king.getType() != boardgame::piece::chess::ChessPieceType::King)
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

        if (rook->getType() != boardgame::piece::chess::ChessPieceType::Rook)
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

        if (!isPathClear(board, from, rookPos))
        {
            return false;
        }

        if (isKingInCheck(board, king.getColor()))
        {
            return false;
        }

        const int step = kingSide ? 1 : -1;
        boardgame::core::Position through{from.row, from.col + step};
        boardgame::core::Position destination{from.row, from.col + 2 * step};

        const auto enemyColor = oppositeColor(king.getColor());

        if (isSquareAttacked(board, through, enemyColor))
        {
            return false;
        }

        if (isSquareAttacked(board, destination, enemyColor))
        {
            return false;
        }

        return true;
    }

    bool ChessMoveValidator::isEnPassantMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &pawn) const
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        const int forward = pawnForwardDirection(pawn.getColor());

        if (to.row - from.row != forward || std::abs(to.col - from.col) != 1)
        {
            return false;
        }

        if (isOccupied(board, to))
        {
            return false;
        }

        const auto *lastMove = board.lastMove();
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

        if (adjacentPiece->getType() != boardgame::piece::chess::ChessPieceType::Pawn)
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

    bool ChessMoveValidator::isPromotionMoveValid(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move,
        const boardgame::piece::chess::IChessPiece &pawn) const
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        const int forward = pawnForwardDirection(pawn.getColor());
        const int dRow = to.row - from.row;
        const int dCol = to.col - from.col;

        const bool oneForward = (dCol == 0 && dRow == forward && !isOccupied(board, to));
        const bool diagonalCapture =
            (std::abs(dCol) == 1 &&
             dRow == forward &&
             isOccupiedByEnemy(board, to, pawn.getColor()));

        if (!(oneForward || diagonalCapture))
        {
            return false;
        }

        return to.row == promotionRow(pawn.getColor());
    }

    bool ChessMoveValidator::leavesKingInCheck(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move) const
    {
        auto *sourcePiece = board.getPieceAt(move.getFrom());
        if (sourcePiece == nullptr)
        {
            return true;
        }

        std::unique_ptr<boardgame::board::chess::IChessBoard> clonedBoard = board.clone();
        if (!clonedBoard)
        {
            return true;
        }

        if (!simulateMoveOnBoard(*clonedBoard, move))
        {
            return true;
        }

        return isKingInCheck(*clonedBoard, sourcePiece->getColor());
    }

    bool ChessMoveValidator::simulateMoveOnBoard(
        boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move) const
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        switch (move.getMoveType())
        {
        case ChessMoveType::Normal:
        case ChessMoveType::PawnDoubleMove:
        case ChessMoveType::Promotion:
            return board.movePiece(from, to);

        case ChessMoveType::EnPassant:
        {
            if (!board.movePiece(from, to))
            {
                return false;
            }

            boardgame::core::Position capturedPawnPos{from.row, to.col};
            return board.removePiece(capturedPawnPos);
        }

        case ChessMoveType::Castling:
        {
            if (!board.movePiece(from, to))
            {
                return false;
            }

            const bool kingSide = to.col > from.col;
            const int rookFromCol = kingSide ? 7 : 0;
            const int rookToCol = kingSide ? to.col - 1 : to.col + 1;

            boardgame::core::Position rookFrom{from.row, rookFromCol};
            boardgame::core::Position rookTo{from.row, rookToCol};

            return board.movePiece(rookFrom, rookTo);
        }

        default:
            return false;
        }
    }

    bool ChessMoveValidator::isKingInCheck(
        const boardgame::board::chess::IChessBoard &board,
        boardgame::piece::chess::ChessPieceColor color) const
    {
        const boardgame::core::Position kingPos = board.findKing(color);
        return isSquareAttacked(board, kingPos, oppositeColor(color));
    }

    bool ChessMoveValidator::isSquareAttacked(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::core::Position &square,
        boardgame::piece::chess::ChessPieceColor attackingColor) const
    {
        const auto pieces = board.getPieces(attackingColor);

        for (const auto &[pos, piece] : pieces)
        {
            if (piece == nullptr)
            {
                continue;
            }

            if (canPieceAttackSquare(board, pos, *piece, square))
            {
                return true;
            }
        }

        return false;
    }

    bool ChessMoveValidator::canPieceAttackSquare(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::core::Position &from,
        const boardgame::piece::chess::IChessPiece &piece,
        const boardgame::core::Position &target) const
    {
        using boardgame::piece::chess::ChessPieceType;

        const int dRow = target.row - from.row;
        const int dCol = target.col - from.col;

        switch (piece.getType())
        {
        case ChessPieceType::Pawn:
        {
            const int forward = pawnForwardDirection(piece.getColor());
            return dRow == forward && std::abs(dCol) == 1;
        }

        case ChessPieceType::Knight:
        {
            return (std::abs(dRow) == 2 && std::abs(dCol) == 1) ||
                   (std::abs(dRow) == 1 && std::abs(dCol) == 2);
        }

        case ChessPieceType::Bishop:
        {
            if (std::abs(dRow) != std::abs(dCol))
            {
                return false;
            }
            return isPathClear(board, from, target);
        }

        case ChessPieceType::Rook:
        {
            const bool straight =
                (dRow == 0 && dCol != 0) ||
                (dCol == 0 && dRow != 0);

            if (!straight)
            {
                return false;
            }

            return isPathClear(board, from, target);
        }

        case ChessPieceType::Queen:
        {
            const bool diagonal = std::abs(dRow) == std::abs(dCol);
            const bool straight =
                (dRow == 0 && dCol != 0) ||
                (dCol == 0 && dRow != 0);

            if (!(diagonal || straight))
            {
                return false;
            }

            return isPathClear(board, from, target);
        }

        case ChessPieceType::King:
        {
            return std::abs(dRow) <= 1 && std::abs(dCol) <= 1;
        }

        default:
            return false;
        }
    }

    bool ChessMoveValidator::isPathClear(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::core::Position &from,
        const boardgame::core::Position &to) const
    {
        const int dRow = to.row - from.row;
        const int dCol = to.col - from.col;

        const int rowStep = getStep(dRow);
        const int colStep = getStep(dCol);

        int currentRow = from.row + rowStep;
        int currentCol = from.col + colStep;

        while (currentRow != to.row || currentCol != to.col)
        {
            if (board.getPieceAt({currentRow, currentCol}) != nullptr)
            {
                return false;
            }

            currentRow += rowStep;
            currentCol += colStep;
        }

        return true;
    }

    bool ChessMoveValidator::isDestinationOccupiedByOwnPiece(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::move::chess::IChessMove &move) const
    {
        auto *sourcePiece = board.getPieceAt(move.getFrom());
        auto *destinationPiece = board.getPieceAt(move.getTo());

        if (sourcePiece == nullptr || destinationPiece == nullptr)
        {
            return false;
        }

        return sourcePiece->getColor() == destinationPiece->getColor();
    }

    bool ChessMoveValidator::isOccupied(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::core::Position &pos) const
    {
        return board.getPieceAt(pos) != nullptr;
    }

    bool ChessMoveValidator::isOccupiedByEnemy(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::core::Position &pos,
        boardgame::piece::chess::ChessPieceColor myColor) const
    {
        auto *piece = board.getPieceAt(pos);
        return piece != nullptr && piece->getColor() != myColor;
    }

    bool ChessMoveValidator::isOccupiedByOwnColor(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::core::Position &pos,
        boardgame::piece::chess::ChessPieceColor myColor) const
    {
        auto *piece = board.getPieceAt(pos);
        return piece != nullptr && piece->getColor() == myColor;
    }

    int ChessMoveValidator::rowDelta(
        const boardgame::move::chess::IChessMove &move) const
    {
        return move.getTo().row - move.getFrom().row;
    }

    int ChessMoveValidator::colDelta(
        const boardgame::move::chess::IChessMove &move) const
    {
        return move.getTo().col - move.getFrom().col;
    }

    int ChessMoveValidator::getStep(int delta) const
    {
        if (delta > 0)
        {
            return 1;
        }

        if (delta < 0)
        {
            return -1;
        }

        return 0;
    }

    int ChessMoveValidator::pawnForwardDirection(
        boardgame::piece::chess::ChessPieceColor color) const
    {
        return color == boardgame::piece::chess::ChessPieceColor::White ? -1 : 1;
    }

    int ChessMoveValidator::pawnStartRow(
        boardgame::piece::chess::ChessPieceColor color) const
    {
        return color == boardgame::piece::chess::ChessPieceColor::White ? 6 : 1;
    }

    int ChessMoveValidator::promotionRow(
        boardgame::piece::chess::ChessPieceColor color) const
    {
        return color == boardgame::piece::chess::ChessPieceColor::White ? 0 : 7;
    }

    boardgame::piece::chess::ChessPieceColor ChessMoveValidator::oppositeColor(
        boardgame::piece::chess::ChessPieceColor color) const
    {
        return color == boardgame::piece::chess::ChessPieceColor::White
                   ? boardgame::piece::chess::ChessPieceColor::Black
                   : boardgame::piece::chess::ChessPieceColor::White;
    }
}
#include "domain/game/chessgame/chess_game.hpp"

#include <cmath>
#include <utility>

namespace boardgame::game::chess
{
    ChessGame::ChessGame(
        std::unique_ptr<boardgame::board::chess::IChessBoard> board,
        std::unique_ptr<boardgame::move::chess::IChessMoveGenerator> moveGenerator,
        std::unique_ptr<boardgame::move::chess::IChessMoveValidator> moveValidator
    )
        : m_Board(std::move(board))
        , m_MoveGenerator(std::move(moveGenerator))
        , m_MoveValidator(std::move(moveValidator))
        , m_CurrentPlayer(boardgame::piece::chess::ChessPieceColor::White)
    {
    }


    const boardgame::board::chess::IChessBoard& ChessGame::getBoard() const
    {
        return *m_Board;
    }

    bool ChessGame::isGameOver() const
    {
        return isCheckmate() || isStalemate();
    }

    bool ChessGame::makeMove(const boardgame::move::chess::IChessMove& move)
    {
        if (!isPlayersPiece(move.getFrom()))
        {
            return false;
        }

        if (!m_MoveValidator->isValidMove(*m_Board, move))
        {
            return false;
        }

        if (!applyMove(move))
        {
            return false;
        }

        auto* movedPiece = m_Board->getPieceAt(move.getTo());
        if (movedPiece != nullptr)
        {
            movedPiece->setHasMoved(true);
        }

        m_Board->setLastMove(
            std::unique_ptr<boardgame::move::chess::IChessMove>(move.clone())
        );

        switchPlayer();
        return true;
    }

    std::vector<std::shared_ptr<boardgame::move::chess::IChessMove>> ChessGame::getLegalMoves(
        const boardgame::core::Position& position
    ) const
    {
        std::vector<std::shared_ptr<boardgame::move::chess::IChessMove>> legalMoves;

        auto* piece = m_Board->getPieceAt(position);
        if (piece == nullptr)
        {
            return legalMoves;
        }

        if (piece->getColor() != m_CurrentPlayer)
        {
            return legalMoves;
        }

        auto generatedMoves = m_MoveGenerator->generateMoves(*m_Board, *piece, position);

        for (const auto& move : generatedMoves)
        {
            if (move != nullptr && m_MoveValidator->isValidMove(*m_Board, *move))
            {
                legalMoves.push_back(move);
            }
        }

        return legalMoves;
    }

    boardgame::piece::chess::ChessPieceColor ChessGame::getCurrentPlayer() const
    {
        return m_CurrentPlayer;
    }

    bool ChessGame::isCheck() const
    {
        const boardgame::core::Position kingPosition = m_Board->findKing(m_CurrentPlayer);
        return isSquareAttacked(*m_Board, kingPosition, oppositeColor(m_CurrentPlayer));
    }

    bool ChessGame::isCheckmate() const
    {
        return isCheck() && !hasAnyLegalMoves(m_CurrentPlayer);
    }

    bool ChessGame::isStalemate() const
    {
        return !isCheck() && !hasAnyLegalMoves(m_CurrentPlayer);
    }

    bool ChessGame::isPlayersPiece(const boardgame::core::Position& position) const
    {
        auto* piece = m_Board->getPieceAt(position);
        return piece != nullptr && piece->getColor() == m_CurrentPlayer;
    }

    void ChessGame::switchPlayer()
    {
        m_CurrentPlayer = oppositeColor(m_CurrentPlayer);
    }

    bool ChessGame::applyMove(const boardgame::move::chess::IChessMove& move)
    {
        switch (move.getMoveType())
        {
            case boardgame::move::chess::ChessMoveType::Normal:
            case boardgame::move::chess::ChessMoveType::PawnDoubleMove:
                return applyNormalMove(move);

            case boardgame::move::chess::ChessMoveType::Castling:
                return applyCastlingMove(move);

            case boardgame::move::chess::ChessMoveType::EnPassant:
                return applyEnPassantMove(move);

            case boardgame::move::chess::ChessMoveType::Promotion:
                return applyPromotionMove(move);

            default:
                return false;
        }
    }

    bool ChessGame::applyNormalMove(const boardgame::move::chess::IChessMove& move)
    {
        return m_Board->movePiece(move.getFrom(), move.getTo());
    }

    bool ChessGame::applyCastlingMove(const boardgame::move::chess::IChessMove& move)
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        if (!m_Board->movePiece(from, to))
        {
            return false;
        }

        const bool kingSide = to.col > from.col;
        const int rookFromCol = kingSide ? 7 : 0;
        const int rookToCol = kingSide ? to.col - 1 : to.col + 1;

        const boardgame::core::Position rookFrom{from.row, rookFromCol};
        const boardgame::core::Position rookTo{from.row, rookToCol};

        if (!m_Board->movePiece(rookFrom, rookTo))
        {
            return false;
        }

        auto* rook = m_Board->getPieceAt(rookTo);
        if (rook != nullptr)
        {
            rook->setHasMoved(true);
        }

        return true;
    }

    bool ChessGame::applyEnPassantMove(const boardgame::move::chess::IChessMove& move)
    {
        const auto from = move.getFrom();
        const auto to = move.getTo();

        if (!m_Board->movePiece(from, to))
        {
            return false;
        }

        const boardgame::core::Position capturedPawnPosition{from.row, to.col};
        return m_Board->removePiece(capturedPawnPosition);
    }

    bool ChessGame::applyPromotionMove(const boardgame::move::chess::IChessMove& move)
    {
        // Voor nu alleen de pawn naar de laatste rij verplaatsen.
        // Echte piece replacement (queen/rook/bishop/knight) kan pas
        // netjes als je move ook bewaart waarnaartoe gepromoveerd wordt.
        return m_Board->movePiece(move.getFrom(), move.getTo());
    }

    bool ChessGame::hasAnyLegalMoves(
        boardgame::piece::chess::ChessPieceColor color
    ) const
    {
        const auto pieces = m_Board->getPieces(color);

        for (const auto& [position, piece] : pieces)
        {
            if (piece == nullptr)
            {
                continue;
            }

            auto generatedMoves = m_MoveGenerator->generateMoves(*m_Board, *piece, position);

            for (const auto& move : generatedMoves)
            {
                if (move != nullptr && m_MoveValidator->isValidMove(*m_Board, *move))
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool ChessGame::isSquareAttacked(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& square,
        boardgame::piece::chess::ChessPieceColor attackingColor
    ) const
    {
        const auto pieces = board.getPieces(attackingColor);

        for (const auto& [position, piece] : pieces)
        {
            if (piece == nullptr)
            {
                continue;
            }

            if (canPieceAttackSquare(board, position, *piece, square))
            {
                return true;
            }
        }

        return false;
    }

    bool ChessGame::canPieceAttackSquare(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& from,
        const boardgame::piece::chess::IChessPiece& piece,
        const boardgame::core::Position& target
    ) const
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

    bool ChessGame::isPathClear(
        const boardgame::board::chess::IChessBoard& board,
        const boardgame::core::Position& from,
        const boardgame::core::Position& to
    ) const
    {
        const int rowStep = getStep(to.row - from.row);
        const int colStep = getStep(to.col - from.col);

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

    int ChessGame::getStep(int delta) const
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

    boardgame::piece::chess::ChessPieceColor ChessGame::oppositeColor(
        boardgame::piece::chess::ChessPieceColor color
    ) const
    {
        return color == boardgame::piece::chess::ChessPieceColor::White
            ? boardgame::piece::chess::ChessPieceColor::Black
            : boardgame::piece::chess::ChessPieceColor::White;
    }

    int ChessGame::pawnForwardDirection(
        boardgame::piece::chess::ChessPieceColor color
    ) const
    {
        return color == boardgame::piece::chess::ChessPieceColor::White ? -1 : 1;
    }
}
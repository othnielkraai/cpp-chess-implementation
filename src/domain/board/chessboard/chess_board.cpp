#include "domain/board/chessboard/chess_board.hpp"

namespace boardgame::board::chess
{
    IChessPiece *ChessBoard::getPieceAt(const Position& pos) const
    {
        auto it = m_Board.find(pos);
        if (it == m_Board.end())
        {
            return nullptr;
        }

        return it->second.get();
    }

    void ChessBoard::placePiece(
        const Position& pos, std::unique_ptr<IChessPiece> piece)
    {
        if (!isInside(pos) || !piece)
        {
            return;
        }

        if (m_Board.find(pos) != m_Board.end())
        {
            return;
        }

        m_Board[pos] = std::move(piece);
    }

    std::unique_ptr<IChessPiece> ChessBoard::removePiece(const Position& pos)
    {
        auto it = m_Board.find(pos);
        if (it == m_Board.end())
        {
            return nullptr;
        }

        m_Board.erase(it);
        return std::move(it->second);
    }

    void ChessBoard::movePiece(const Position& from, const Position& to)
    {
        if (!isInside(from) || !isInside(to))
        {
            return;
        }

        auto fromIt = m_Board.find(from);
        if (fromIt == m_Board.end())
        {
            return;
        }

        if (m_Board.find(to) != m_Board.end())
        {
            return;
        }

        m_Board[to] = std::move(fromIt->second);
        m_Board.erase(fromIt);
        return;
    }

    const std::map<Position, std::unique_ptr<IChessPiece>>& ChessBoard::getPieces() const
    {
        return m_Board;
    }

    std::map<Position, std::unique_ptr<IChessPiece>> ChessBoard::getPieces(ChessPieceColor color) const
    {
        std::map<Position, std::unique_ptr<IChessPiece>> result;

        for (const auto &[pos, piece] : m_Board)
        {
            if (piece && piece->getColor() == color)
            {
                result[pos] = std::unique_ptr<IChessPiece>(piece->clone());
            }
        }

        return result;
    }

    bool ChessBoard::isInside(const Position& pos) const
    {
        return pos.row >= 0 && pos.row < 8 &&
               pos.col >= 0 && pos.col < 8;
    }

    bool ChessBoard::isEmpty(const Position& pos) const
    {
        return getPieceAt(pos) == nullptr;
    }

    bool ChessBoard::hasPiece(const Position& pos) const
    {
        return getPieceAt(pos) != nullptr;
    }

    bool ChessBoard::hasEnemyPiece(const Position& pos, ChessPieceColor color) const
    {
        auto piece = getPieceAt(pos);
        return piece && piece->getColor() != color;
    }

    bool ChessBoard::hasFriendlyPiece(const Position& pos, ChessPieceColor color) const
    {
        auto piece = getPieceAt(pos);
        return piece && piece->getColor() == color;
    }

    Position ChessBoard::findKing(ChessPieceColor color) const
    {
        for (const auto &[pos, piece] : m_Board)
        {
            if (piece &&
                piece->getType() == ChessPieceType::King &&
                piece->getColor() == color)
            {
                return pos;
            }
        }

        return boardgame::core::Position{-1, -1}; // TODO maybe throw error or something 
    }

    void ChessBoard::setLastMove(const IChessMove& move) 
    {
        m_LastMove = move;
    }

    std::optional<IChessMove> ChessBoard::getLastMove() const
    {
        return m_LastMove ? std::make_optional(*m_LastMove) : std::nullopt;
    }

    std::unique_ptr<IChessBoard> ChessBoard::clone() const
    {
        auto newBoard = std::make_unique<ChessBoard>();

        for (const auto &[pos, piece] : m_Board)
        {
            if (piece)
            {
                newBoard->placePiece(pos, std::unique_ptr<boardgame::piece::chess::IChessPiece>(piece->clone()));
            }
        }

        if (m_LastMove)
        {
            newBoard->setLastMove(std::unique_ptr<boardgame::move::chess::IChessMove>(m_LastMove->clone()));
        }

        return newBoard;
    }
}
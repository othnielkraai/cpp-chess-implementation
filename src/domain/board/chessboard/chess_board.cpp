#include "domain/board/chessboard/chess_board.hpp"

namespace boardgame::board::chess
{
    boardgame::piece::chess::IChessPiece *ChessBoard::getPieceAt(boardgame::core::Position pos) const
    {
        auto it = m_Board.find(pos);
        if (it == m_Board.end())
        {
            return nullptr;
        }

        return it->second.get();
    }

    bool ChessBoard::placePiece(
        boardgame::core::Position pos,
        std::unique_ptr<boardgame::piece::chess::IChessPiece> piece)
    {
        if (!isInside(pos) || !piece)
        {
            return false;
        }

        if (m_Board.find(pos) != m_Board.end())
        {
            return false;
        }

        m_Board[pos] = std::move(piece);
        return true;
    }

    bool ChessBoard::removePiece(boardgame::core::Position pos)
    {
        auto it = m_Board.find(pos);
        if (it == m_Board.end())
        {
            return false;
        }

        m_Board.erase(it);
        return true;
    }

    bool ChessBoard::movePiece(boardgame::core::Position from, boardgame::core::Position to)
    {
        if (!isInside(from) || !isInside(to))
        {
            return false;
        }

        auto fromIt = m_Board.find(from);
        if (fromIt == m_Board.end())
        {
            return false;
        }

        if (m_Board.find(to) != m_Board.end())
        {
            return false;
        }

        m_Board[to] = std::move(fromIt->second);
        m_Board.erase(fromIt);
        return true;
    }

    bool ChessBoard::isInside(boardgame::core::Position pos) const
    {
        return pos.row >= 0 && pos.row < 8 &&
               pos.col >= 0 && pos.col < 8;
    }

    boardgame::core::Position ChessBoard::findKing(boardgame::piece::chess::ChessPieceColor color) const
    {
        for (const auto &[pos, piece] : m_Board)
        {
            if (piece &&
                piece->getType() == boardgame::piece::chess::ChessPieceType::King &&
                piece->getColor() == color)
            {
                return pos;
            }
        }

        return boardgame::core::Position{-1, -1}; // TODO maybe throw error or something 
    }

    std::map<boardgame::core::Position, boardgame::piece::chess::IChessPiece *> ChessBoard::getAllPieces() const
    {
        std::map<boardgame::core::Position, boardgame::piece::chess::IChessPiece *> result;

        for (const auto &[pos, piece] : m_Board)
        {
            result[pos] = piece.get();
        }

        return result;
    }

    std::map<boardgame::core::Position, boardgame::piece::chess::IChessPiece *> ChessBoard::getPieces(
        boardgame::piece::chess::ChessPieceColor color) const
    {
        std::map<boardgame::core::Position, boardgame::piece::chess::IChessPiece *> result;

        for (const auto &[pos, piece] : m_Board)
        {
            if (piece && piece->getColor() == color)
            {
                result[pos] = piece.get();
            }
        }

        return result;
    }

    void ChessBoard::setLastMove(std::unique_ptr<boardgame::move::chess::IChessMove> move)
    {
        m_LastMove = std::move(move);
    }

    const std::unique_ptr<boardgame::move::chess::IChessMove>& ChessBoard::lastMove() const
    {
        return m_LastMove;
    }
}
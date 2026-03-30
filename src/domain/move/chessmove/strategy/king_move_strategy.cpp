#include "domain/move/chessmove/strategy/king_move_strategy.hpp"


namespace boardgame::move::chess
{
    std::vector<std::unique_ptr<IChessMove>> KingMoveStrategy::generateMoves(
        const boardgame::board::chess::IChessBoard &board,
        const boardgame::piece::chess::IChessPiece &piece,
        const boardgame::core::Position &from) const
    {
        static constexpr std::array<std::pair<int, int>, 8> offsets{{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};

        std::vector<std::unique_ptr<IChessMove>> moves;

        // normale king moves
        for (const auto &[rowOffset, colOffset] : offsets)
        {
            boardgame::core::Position to{
                from.row + rowOffset,
                from.col + colOffset};

            if (!board.isInside(to))
            {
                continue;
            }

            auto targetPiece = board.getPieceAt(to);

            if (!targetPiece)
            {
                moves.push_back(std::make_unique<ChessMove>(from, to));
                continue;
            }

            if (targetPiece->getColor() != piece.getColor())
            {
                moves.push_back(std::make_unique<ChessMove>(from, to));
            }
        }

        int startRow =
            (piece.getColor() == ChessPieceColor::White)
                ? 0
                : 7;

        if (!piece.hasMoved())
        {
            {
                Position f{startRow, 5};
                Position g{startRow, 6};
                Position rookPos{startRow, 7};

                auto rook = board.getPieceAt(rookPos);

                if (!board.getPieceAt(f) &&
                    !board.getPieceAt(g) &&
                    rook &&
                    !rook->hasMoved() &&
                    rook->getColor() == piece.getColor())
                {
                    moves.push_back(
                        std::make_unique<ChessMove>(
                            from,
                            g,
                            ChessMoveType::Castling));
                }
            }
            {
                Position b{startRow, 1};
                Position c{startRow, 2};
                Position d{startRow, 3};
                Position rookPos{startRow, 0};

                auto rook = board.getPieceAt(rookPos);

                if (!board.getPieceAt(b) &&
                    !board.getPieceAt(c) &&
                    !board.getPieceAt(d) &&
                    rook &&
                    !rook->hasMoved() &&
                    rook->getColor() == piece.getColor())
                {
                    moves.push_back(
                        std::make_unique<ChessMove>(
                            from,
                            c,
                            ChessMoveType::Castling));
                }
            }
        }

        return moves;
    }
}
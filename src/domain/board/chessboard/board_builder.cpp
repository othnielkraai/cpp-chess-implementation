#include "domain/board/chessboard/board_builder.hpp"

#include <stdexcept>
#include <utility>

#include "domain/board/chessboard/chess_board.hpp"
#include "domain/piece/chesspiece/chess_piece_factory.hpp"

namespace boardgame::board::chess
{
    using namespace boardgame::core;
    using namespace boardgame::piece::chess;

    BoardBuilder& BoardBuilder::buildEmptyBoard()
    {
        board_ = std::make_unique<ChessBoard>();
        return *this;
    }

    BoardBuilder& BoardBuilder::withPiece(
        const Position& position,
        std::unique_ptr<IChessPiece> piece
    )
    {
        if (!board_)
        {
            throw std::logic_error("Call buildEmptyBoard() or buildDefaultBoard() first");
        }

        board_->placePiece(position, std::move(piece));
        return *this;
    }

    BoardBuilder& BoardBuilder::buildDefaultBoard()
    {
        buildEmptyBoard();

        // black pieces
        board_->placePiece({0, 0}, ChessPieceFactory::create(ChessPieceType::Rook, ChessPieceColor::Black));
        board_->placePiece({0, 1}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::Black));
        board_->placePiece({0, 2}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::Black));
        board_->placePiece({0, 3}, ChessPieceFactory::create(ChessPieceType::Queen, ChessPieceColor::Black));
        board_->placePiece({0, 4}, ChessPieceFactory::create(ChessPieceType::King, ChessPieceColor::Black));
        board_->placePiece({0, 5}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::Black));
        board_->placePiece({0, 6}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::Black));
        board_->placePiece({0, 7}, ChessPieceFactory::create(ChessPieceType::Rook, ChessPieceColor::Black));

        for (int col = 0; col < 8; ++col)
        {
            board_->placePiece({1, col}, ChessPieceFactory::create(ChessPieceType::Pawn, ChessPieceColor::Black));
        }

        // white pieces
        board_->placePiece({7, 0}, ChessPieceFactory::create(ChessPieceType::Rook, ChessPieceColor::White));
        board_->placePiece({7, 1}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::White));
        board_->placePiece({7, 2}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::White));
        board_->placePiece({7, 3}, ChessPieceFactory::create(ChessPieceType::Queen, ChessPieceColor::White));
        board_->placePiece({7, 4}, ChessPieceFactory::create(ChessPieceType::King, ChessPieceColor::White));
        board_->placePiece({7, 5}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::White));
        board_->placePiece({7, 6}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::White));
        board_->placePiece({7, 7}, ChessPieceFactory::create(ChessPieceType::Rook, ChessPieceColor::White));

        for (int col = 0; col < 8; ++col)
        {
            board_->placePiece({6, col}, ChessPieceFactory::create(ChessPieceType::Pawn, ChessPieceColor::White));
        }

        return *this;
    }

    std::unique_ptr<IChessBoard> BoardBuilder::build()
    {
        if (!board_)
        {
            throw std::logic_error("No board has been created");
        }

        return std::move(board_);
    }
}
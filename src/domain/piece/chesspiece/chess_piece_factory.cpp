#include "domain/piece/chesspiece/chess_piece_factory.hpp"

//piece includes
#include "domain/piece/chesspiece/bishop_piece.hpp"
#include "domain/piece/chesspiece/rook_piece.hpp"
#include "domain/piece/chesspiece/queen_piece.hpp"
#include "domain/piece/chesspiece/king_piece.hpp"
#include "domain/piece/chesspiece/knight_piece.hpp"
#include "domain/piece/chesspiece/pawn_piece.hpp"

//move strategy includes
#include "domain/move/chessmove/strategy/bishop_move_strategy.hpp"
#include "domain/move/chessmove/strategy/rook_move_strategy.hpp"
#include "domain/move/chessmove/strategy/queen_move_strategy.hpp"
#include "domain/move/chessmove/strategy/king_move_strategy.hpp"
#include "domain/move/chessmove/strategy/knight_move_strategy.hpp"
#include "domain/move/chessmove/strategy/pawn_move_strategy.hpp"

namespace boardgame::piece::chess
{
    std::unique_ptr<IChessPiece> ChessPieceFactory::create(
        ChessPieceType type,
        ChessPieceColor color
    )
    {
        switch (type)
        {
            case ChessPieceType::Bishop:
                return std::make_unique<BishopPiece>(
                    std::make_unique<boardgame::move::chess::BishopMoveStrategy>(),
                    color
                );

            case ChessPieceType::Rook:
                return std::make_unique<RookPiece>(
                    std::make_unique<boardgame::move::chess::RookMoveStrategy>(),
                    color
                );

            case ChessPieceType::Queen:
                return std::make_unique<QueenPiece>(
                    std::make_unique<boardgame::move::chess::QueenMoveStrategy>(),
                    color
                );

            case ChessPieceType::King:
                return std::make_unique<KingPiece>(
                    std::make_unique<boardgame::move::chess::KingMoveStrategy>(),
                    color
                );

            case ChessPieceType::Knight:
                return std::make_unique<KnightPiece>(
                    std::make_unique<boardgame::move::chess::KnightMoveStrategy>(),
                    color
                );

            case ChessPieceType::Pawn:
                return std::make_unique<PawnPiece>(
                    std::make_unique<boardgame::move::chess::PawnMoveStrategy>(),
                    color
                );

            default:
                return nullptr;
        }
    }
}
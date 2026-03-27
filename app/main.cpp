#include <iostream>

#include <memory>

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "domain/board/chessboard/chess_board.hpp"
#include "domain/piece/chesspiece/pawn_piece.hpp"
#include "domain/piece/chesspiece/rook_piece.hpp"
#include "domain/piece/chesspiece/knight_piece.hpp"
#include "domain/piece/chesspiece/bishop_piece.hpp"
#include "domain/piece/chesspiece/queen_piece.hpp"
#include "domain/piece/chesspiece/king_piece.hpp"



using namespace boardgame::board::chess;
using namespace boardgame::piece::chess;


int main(){
    std::unique_ptr<IChessBoard> board = std::make_unique<ChessBoard>();

        // ===== pawns =====
        for (int col = 0; col < 8; ++col)
        {
            board->placePiece({6, col}, std::make_unique<PawnPiece>(ChessPieceColor::White));
            board->placePiece({1, col}, std::make_unique<PawnPiece>(ChessPieceColor::Black));
        }

        // ===== rooks =====
        board->placePiece({7, 0}, std::make_unique<RookPiece>(ChessPieceColor::White));
        board->placePiece({7, 7}, std::make_unique<RookPiece>(ChessPieceColor::White));
        board->placePiece({0, 0}, std::make_unique<RookPiece>(ChessPieceColor::Black));
        board->placePiece({0, 7}, std::make_unique<RookPiece>(ChessPieceColor::Black));

        // ===== knights =====
        board->placePiece({7, 1}, std::make_unique<KnightPiece>(ChessPieceColor::White));
        board->placePiece({7, 6}, std::make_unique<KnightPiece>(ChessPieceColor::White));
        board->placePiece({0, 1}, std::make_unique<KnightPiece>(ChessPieceColor::Black));
        board->placePiece({0, 6}, std::make_unique<KnightPiece>(ChessPieceColor::Black));

        // ===== bishops =====
        board->placePiece({7, 2}, std::make_unique<BishopPiece>(ChessPieceColor::White));
        board->placePiece({7, 5}, std::make_unique<BishopPiece>(ChessPieceColor::White));
        board->placePiece({0, 2}, std::make_unique<BishopPiece>(ChessPieceColor::Black));
        board->placePiece({0, 5}, std::make_unique<BishopPiece>(ChessPieceColor::Black));

        // ===== queens =====
        board->placePiece({7, 3}, std::make_unique<QueenPiece>(ChessPieceColor::White));
        board->placePiece({0, 3}, std::make_unique<QueenPiece>(ChessPieceColor::Black));

        // ===== kings =====
        board->placePiece({7, 4}, std::make_unique<KingPiece>(ChessPieceColor::White));
        board->placePiece({0, 4}, std::make_unique<KingPiece>(ChessPieceColor::Black));
    return 0;
}

#include <iostream>

#include <memory>

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"


#include "domain/board/chessboard/chess_board.hpp"
#include "domain/piece/chesspiece/chess_piece_factory.hpp"
#include "domain/move/chessmove/chess_move_generator_factory.hpp"
#include "domain/move/chessmove/chess_move_generator.hpp"

using namespace boardgame::board::chess;
using namespace boardgame::piece::chess;

#include <iostream>
#include <iomanip>

void printBoard(const IChessBoard &board)
{
    std::cout << "\n";

    for (int row = 0; row < 8; ++row)
    {
        std::cout << 8 - row << "  ";

        for (int col = 0; col < 8; ++col)
        {
            auto piece = board.getPieceAt({row, col});

            if (!piece)
            {
                std::cout << ". ";
                continue;
            }

            char symbol = '?';

            switch (piece->getType())
            {
            case ChessPieceType::Pawn:
                symbol = 'p';
                break;
            case ChessPieceType::Rook:
                symbol = 'r';
                break;
            case ChessPieceType::Knight:
                symbol = 'n';
                break;
            case ChessPieceType::Bishop:
                symbol = 'b';
                break;
            case ChessPieceType::Queen:
                symbol = 'q';
                break;
            case ChessPieceType::King:
                symbol = 'k';
                break;
            }

            // wit = hoofdletter
            if (piece->getColor() == ChessPieceColor::White)
                symbol = std::toupper(symbol);

            std::cout << symbol << " ";
        }

        std::cout << "\n";
    }

    std::cout << "\n   a b c d e f g h\n\n";
}

std::unique_ptr<IChessBoard> createInitialBoard()
{
    auto board = std::make_unique<ChessBoard>();

    // Place black pieces
    board->placePiece({0, 0}, ChessPieceFactory::create(ChessPieceType::Rook, ChessPieceColor::Black));
    board->placePiece({0, 1}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::Black));
    board->placePiece({0, 2}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::Black));
    board->placePiece({0, 3}, ChessPieceFactory::create(ChessPieceType::Queen, ChessPieceColor::Black));
    board->placePiece({0, 4}, ChessPieceFactory::create(ChessPieceType::King, ChessPieceColor::Black));
    board->placePiece({0, 5}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::Black));
    board->placePiece({0, 6}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::Black));
    board->placePiece({0, 7}, ChessPieceFactory::create(ChessPieceType::Rook, ChessPieceColor::Black));

    for (int col = 0; col < 8; ++col)
        board->placePiece({1, col}, ChessPieceFactory::create(ChessPieceType::Pawn, ChessPieceColor::Black));

    // Place white pieces
    board->placePiece({7, 0}, ChessPieceFactory::create(ChessPieceType::Rook, ChessPieceColor::White));
    board->placePiece({7, 1}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::White));
    board->placePiece({7, 2}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::White));
    board->placePiece({7, 3}, ChessPieceFactory::create(ChessPieceType::Queen, ChessPieceColor::White));
    board->placePiece({7, 4}, ChessPieceFactory::create(ChessPieceType::King, ChessPieceColor::White));
    board->placePiece({7, 5}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::White));
    board->placePiece({7, 6}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::White));
    board->placePiece({7, 7}, ChessPieceFactory::create(ChessPieceType::Rook, ChessPieceColor::White));

    for (int col = 0; col < 8; ++col)
        board->placePiece({6, col}, ChessPieceFactory::create(ChessPieceType::Pawn, ChessPieceColor::White));

    return board;
}

int main()
{
    auto board = createInitialBoard();
    auto moveGenerator = ChessMoveGeneratorFactory::create();
    printBoard(*board);

    auto moves = moveGenerator->generateMoves(*board);
    for (const auto &move : moves)
    {
        std::cout
            << move->getFrom().row << "," << move->getFrom().col
            << " -> "
            << move->getTo().row << "," << move->getTo().col
            << "\n";
    }

    board->movePiece({6, 4}, {4, 4}); // e2 to e4
    printBoard(*board);
    
    auto movesAfter = moveGenerator->generateMoves(*board);
    for (const auto &move : movesAfter)
    {        std::cout
            << move->getFrom().row << "," << move->getFrom().col
            << " -> "
            << move->getTo().row << "," << move->getTo().col
            << "\n";
    }
    return 0;
}

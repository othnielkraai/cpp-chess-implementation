#include <iostream>

#include <memory>

#include "interfaces/board/chessboard/IChessBoard.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMoveGenerator.hpp"
#include "interfaces/move/chessmove/IChessMoveValidator.hpp"


#include "domain/board/chessboard/chess_board.hpp"
#include "domain/move/chessmove/chess_move_generator_factory.hpp"
#include "domain/move/chessmove/chess_move_generator.hpp"
#include "domain/board/chessboard/board_builder.hpp"

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



int main()
{
    auto board = BoardBuilder{}.buildDefaultBoard().build();
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

#include <gtest/gtest.h>
#include <memory>
#include <optional>

#include "interfaces/piece/chesspiece/IChessPiece.hpp"

#include "domain/move/chessmove/chess_move.hpp"
#include "core/common/position.hpp"

using boardgame::core::Position;
using boardgame::move::chess::ChessMove;
using boardgame::move::chess::ChessMoveType;
using boardgame::move::chess::IChessMove;
using boardgame::piece::chess::ChessPieceType;

TEST(ChessMoveTest, ConstructorSetsFromPositionCorrectly)
{
    Position from{1, 2};
    Position to{3, 4};

    ChessMove move(from, to, ChessMoveType::Normal, std::nullopt);

    EXPECT_EQ(move.getFrom(), from);
}

TEST(ChessMoveTest, ConstructorSetsToPositionCorrectly)
{
    Position from{1, 2};
    Position to{3, 4};

    ChessMove move(from, to, ChessMoveType::Normal, std::nullopt);

    EXPECT_EQ(move.getTo(), to);
}

TEST(ChessMoveTest, ConstructorSetsMoveTypeCorrectly)
{
    Position from{1, 2};
    Position to{3, 4};

    ChessMove move(from, to, ChessMoveType::Castling, std::nullopt);

    EXPECT_EQ(move.getMoveType(), ChessMoveType::Castling);
}

TEST(ChessMoveTest, GetPromotedPieceTypeReturnsNulloptForNonPromotionMove)
{
    Position from{6, 0};
    Position to{7, 0};

    ChessMove move(from, to, ChessMoveType::Normal, std::nullopt);

    EXPECT_FALSE(move.getPromotedPieceType().has_value());
}

TEST(ChessMoveTest, GetPromotedPieceTypeReturnsPromotedPieceForPromotionMove)
{
    Position from{6, 0};
    Position to{7, 0};

    ChessMove move(from, to, ChessMoveType::Promotion, ChessPieceType::Queen);

    ASSERT_TRUE(move.getPromotedPieceType().has_value());
    EXPECT_EQ(move.getPromotedPieceType().value(), ChessPieceType::Queen);
}

TEST(ChessMoveTest, CloneReturnsDifferentObject)
{
    Position from{1, 2};
    Position to{3, 4};

    ChessMove move(from, to, ChessMoveType::Normal, std::nullopt);

    std::unique_ptr<IChessMove> clonedMove = move.clone();

    ASSERT_NE(clonedMove, nullptr);
    EXPECT_NE(clonedMove.get(), &move);
}

TEST(ChessMoveTest, CloneCopiesFromAndToCorrectly)
{
    Position from{1, 2};
    Position to{3, 4};

    ChessMove move(from, to, ChessMoveType::Normal, std::nullopt);

    std::unique_ptr<IChessMove> clonedMove = move.clone();

    ASSERT_NE(clonedMove, nullptr);
    EXPECT_EQ(clonedMove->getFrom(), from);
    EXPECT_EQ(clonedMove->getTo(), to);
}

TEST(ChessMoveTest, CloneCopiesMoveTypeCorrectly)
{
    Position from{4, 4};
    Position to{6, 4};

    ChessMove move(from, to, ChessMoveType::Castling, std::nullopt);

    std::unique_ptr<IChessMove> clonedMove = move.clone();

    ASSERT_NE(clonedMove, nullptr);
    EXPECT_EQ(clonedMove->getMoveType(), ChessMoveType::Castling);
}

TEST(ChessMoveTest, CloneCopiesPromotedPieceTypeCorrectly)
{
    Position from{6, 0};
    Position to{7, 0};

    ChessMove move(from, to, ChessMoveType::Promotion, ChessPieceType::Queen);

    std::unique_ptr<IChessMove> clonedMove = move.clone();

    ASSERT_NE(clonedMove, nullptr);
    ASSERT_TRUE(clonedMove->getPromotedPieceType().has_value());
    EXPECT_EQ(clonedMove->getPromotedPieceType().value(), ChessPieceType::Queen);
}
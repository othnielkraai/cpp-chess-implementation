#include "domain/game/chessgame/chess_game.hpp"

#include <stdexcept>

#include "interfaces/history/chesshistory/IChessHistory.hpp"
#include "interfaces/piece/chesspiece/IChessPiece.hpp"
#include "interfaces/move/chessmove/IChessMove.hpp"

using boardgame::history::chess::ChessRecord;
using boardgame::piece::chess::ChessPieceFactory;
using boardgame::piece::chess::ChessPieceType;
using boardgame::piece::chess::ChessPieceColor;
using boardgame::move::chess::ChessMoveType;

namespace boardgame::game::chess
{
    ChessGame::ChessGame()
        : m_Board(nullptr),
          m_WhitePlayer(nullptr),
          m_BlackPlayer(nullptr),
          m_CurrentPlayer(nullptr),
          m_MoveGenerator(nullptr),
          m_History(nullptr),
          m_GameState(GameState::Ongoing)
    {
    }

    void ChessGame::ensureReady() const
    {
        if (!m_Board)
            throw std::logic_error("ChessGame::ensureReady - board not set");

        if (!m_WhitePlayer)
            throw std::logic_error("ChessGame::ensureReady - white player not set");

        if (!m_BlackPlayer)
            throw std::logic_error("ChessGame::ensureReady - black player not set");

        if (!m_CurrentPlayer)
            throw std::logic_error("ChessGame::ensureReady - current player not set");

        if (!m_MoveGenerator)
            throw std::logic_error("ChessGame::ensureReady - move generator not set");

        if (!m_History)
            throw std::logic_error("ChessGame::ensureReady - history not set");
    }

    void ChessGame::addBoard(std::unique_ptr<IChessBoard> board)
    {
        if (!board)
        {
            throw std::invalid_argument("ChessGame::addBoard - board is null");
        }

        m_Board = std::move(board);
    }

    const IChessBoard &ChessGame::getBoard() const
    {
        if (!m_Board)
        {
            throw std::logic_error("ChessGame::getBoard - board not set");
        }

        return *m_Board;
    }

    void ChessGame::addWhitePlayer(std::unique_ptr<IChessPlayer> player)
    {
        if (!player)
        {
            throw std::invalid_argument("ChessGame::addWhitePlayer - player is null");
        }

        m_WhitePlayer = std::move(player);

        if (!m_CurrentPlayer)
        {
            m_CurrentPlayer = m_WhitePlayer.get();
        }
    }

    void ChessGame::addBlackPlayer(std::unique_ptr<IChessPlayer> player)
    {
        if (!player)
        {
            throw std::invalid_argument("ChessGame::addBlackPlayer - player is null");
        }

        m_BlackPlayer = std::move(player);
    }

    const IChessPlayer &ChessGame::getCurrentPlayer() const
    {
        if (!m_CurrentPlayer)
        {
            throw std::logic_error("ChessGame::getCurrentPlayer - current player not set");
        }

        return *m_CurrentPlayer;
    }

    const IChessPlayer &ChessGame::getWhitePlayer() const
    {
        if (!m_WhitePlayer)
        {
            throw std::logic_error("ChessGame::getWhitePlayer - white player not set");
        }

        return *m_WhitePlayer;
    }

    const IChessPlayer &ChessGame::getBlackPlayer() const
    {
        if (!m_BlackPlayer)
        {
            throw std::logic_error("ChessGame::getBlackPlayer - black player not set");
        }

        return *m_BlackPlayer;
    }

    void ChessGame::addMoveGenerator(std::unique_ptr<IChessMoveGenerator> moveGenerator)
    {
        if (!moveGenerator)
        {
            throw std::invalid_argument("ChessGame::addMoveGenerator - move generator is null");
        }

        m_MoveGenerator = std::move(moveGenerator);
    }

    std::vector<std::unique_ptr<IChessMove>> ChessGame::getLegalMoves(const Position &position) const
    {
        ensureReady();

        auto piece = m_Board->getPieceAt(position);
        if (!piece)
        {
            return {};
        }

        if (piece->getColor() != (m_CurrentPlayer->isWhite() ? boardgame::piece::chess::ChessPieceColor::White : boardgame::piece::chess::ChessPieceColor::Black))
        {
            return {};
        }

        return m_MoveGenerator->generateMoves(*m_Board, position);
    }

    void ChessGame::addHistory(std::unique_ptr<IChessHistory> history)
    {
        if (!history)
        {
            throw std::invalid_argument("ChessGame::addHistory - history is null");
        }

        m_History = std::move(history);
    }

    const IChessHistory &ChessGame::getHistory() const
    {
        if (!m_History)
        {
            throw std::logic_error("ChessGame::getHistory - history not set");
        }

        return *m_History;
    }

    bool ChessGame::isMoveForCurrentPlayer(const IChessMove &move) const
    {
        auto piece = m_Board->getPieceAt(move.getFrom());
        if (!piece)
        {
            return false;
        }

        auto temp = m_CurrentPlayer->isWhite() ? boardgame::piece::chess::ChessPieceColor::White : boardgame::piece::chess::ChessPieceColor::Black;

        return piece->getColor() == temp;
    }

    bool ChessGame::isLegalMove(const IChessMove &move) const
    {
        auto legalMoves = getLegalMoves(move.getFrom());

        for (const auto &legalMove : legalMoves)
        {
            if (legalMove->getFrom() == move.getFrom() &&
                legalMove->getTo() == move.getTo() &&
                legalMove->getMoveType() == move.getMoveType())
            {
                return true;
            }
        }

        return false;
    }

    std::unique_ptr<ChessRecord> ChessGame::buildRecord(const IChessMove &move) const
    {
        auto movedPiece = m_Board->getPieceAt(move.getFrom());
        if (!movedPiece)
        {
            return nullptr;
        }

        auto record = std::make_unique<ChessRecord>();
        record->move = move.clone();
        record->movedPieceType = movedPiece->getType();
        record->movedPieceColor = movedPiece->getColor();

        switch (move.getMoveType())
        {
            case ChessMoveType::Normal:
            case ChessMoveType::PawnDoubleMove:
            case ChessMoveType::Promotion:
            {
                auto capturedPiece = m_Board->getPieceAt(move.getTo());
                if (capturedPiece)
                {
                    record->capturedPieceType = capturedPiece->getType();
                    record->capturedPieceColor = capturedPiece->getColor();
                    record->capturedPiecePosition = move.getTo();
                }

                if (move.getMoveType() == ChessMoveType::Promotion)
                {
                    record->promotionPieceType = move.getPromotedPieceType();
                }

                break;
            }

            case ChessMoveType::EnPassant:
            {
                Position capturedPos{move.getFrom().row, move.getTo().col};
                auto capturedPiece = m_Board->getPieceAt(capturedPos);

                if (capturedPiece)
                {
                    record->capturedPieceType = capturedPiece->getType();
                    record->capturedPieceColor = capturedPiece->getColor();
                    record->capturedPiecePosition = capturedPos;
                }

                break;
            }

            case ChessMoveType::Castling:
            {
                if (move.getTo().col == 6)
                {
                    record->rookFrom = Position{move.getFrom().row, 7};
                    record->rookTo = Position{move.getFrom().row, 5};
                }
                else if (move.getTo().col == 2)
                {
                    record->rookFrom = Position{move.getFrom().row, 0};
                    record->rookTo = Position{move.getFrom().row, 3};
                }

                break;
            }

            default:
                break;
        }

        return record;
    }

    bool ChessGame::applyNormalMove(const IChessMove &move)
    {
        auto movingPiece = m_Board->removePiece(move.getFrom());
        if (!movingPiece)
        {
            return false;
        }

        m_Board->removePiece(move.getTo());

        if (!m_Board->placePiece(move.getTo(), std::move(movingPiece)))
        {
            return false;
        }

        m_Board->setLastMove(move.clone());
        return true;
    }

    bool ChessGame::applyPromotionMove(const IChessMove &move)
    {
        auto movingPiece = m_Board->removePiece(move.getFrom());
        if (!movingPiece)
        {
            return false;
        }

        m_Board->removePiece(move.getTo());

        auto promotedType = move.getPromotedPieceType();
        if (!promotedType.has_value())
        {
            return false;
        }

        auto promotedPiece = ChessPieceFactory::create(
            promotedType.value(),
            movingPiece->getColor());

        if (!promotedPiece)
        {
            return false;
        }

        if (!m_Board->placePiece(move.getTo(), std::move(promotedPiece)))
        {
            return false;
        }

        m_Board->setLastMove(move.clone());
        return true;
    }

    bool ChessGame::applyCastlingMove(const IChessMove &move)
    {
        auto king = m_Board->removePiece(move.getFrom());
        if (!king)
        {
            return false;
        }

        Position rookFrom{};
        Position rookTo{};

        if (move.getTo().col == 6)
        {
            rookFrom = Position{move.getFrom().row, 7};
            rookTo = Position{move.getFrom().row, 5};
        }
        else if (move.getTo().col == 2)
        {
            rookFrom = Position{move.getFrom().row, 0};
            rookTo = Position{move.getFrom().row, 3};
        }
        else
        {
            m_Board->placePiece(move.getFrom(), std::move(king));
            return false;
        }

        auto rook = m_Board->removePiece(rookFrom);
        if (!rook)
        {
            m_Board->placePiece(move.getFrom(), std::move(king));
            return false;
        }

        if (!m_Board->placePiece(move.getTo(), std::move(king)))
        {
            m_Board->placePiece(move.getFrom(), std::move(king));
            m_Board->placePiece(rookFrom, std::move(rook));
            return false;
        }

        if (!m_Board->placePiece(rookTo, std::move(rook)))
        {
            auto kingBack = m_Board->removePiece(move.getTo());
            if (kingBack)
            {
                m_Board->placePiece(move.getFrom(), std::move(kingBack));
            }
            m_Board->placePiece(rookFrom, std::move(rook));
            return false;
        }

        m_Board->setLastMove(move.clone());
        return true;
    }

    bool ChessGame::applyEnPassantMove(const IChessMove &move)
    {
        auto movingPiece = m_Board->removePiece(move.getFrom());
        if (!movingPiece)
        {
            return false;
        }

        Position capturedPawnPos{move.getFrom().row, move.getTo().col};

        auto capturedPawn = m_Board->removePiece(capturedPawnPos);
        if (!capturedPawn)
        {
            m_Board->placePiece(move.getFrom(), std::move(movingPiece));
            return false;
        }

        if (!m_Board->placePiece(move.getTo(), std::move(movingPiece)))
        {
            m_Board->placePiece(move.getFrom(), std::move(movingPiece));
            m_Board->placePiece(capturedPawnPos, std::move(capturedPawn));
            return false;
        }

        m_Board->setLastMove(move.clone());
        return true;
    }

    bool ChessGame::applyPawnDoubleMove(const IChessMove &move)
    {
        return applyNormalMove(move);
    }

    bool ChessGame::applyMove(const IChessMove &move)
    {
        switch (move.getMoveType())
        {
            case ChessMoveType::Normal:
                return applyNormalMove(move);

            case ChessMoveType::Promotion:
                return applyPromotionMove(move);

            case ChessMoveType::Castling:
                return applyCastlingMove(move);

            case ChessMoveType::EnPassant:
                return applyEnPassantMove(move);

            case ChessMoveType::PawnDoubleMove:
                return applyPawnDoubleMove(move);

            default:
                return false;
        }
    }

    bool ChessGame::makeMove(const IChessMove &move)
    {
        ensureReady();

        if (isGameOver())
        {
            return false;
        }

        if (!isMoveForCurrentPlayer(move))
        {
            return false;
        }

        if (!isLegalMove(move))
        {
            return false;
        }

        auto record = buildRecord(move);
        if (!record)
        {
            return false;
        }

        if (!applyMove(move))
        {
            return false;
        }

        m_History->addRecord(std::move(record));

        switchPlayer();
        updateGameState();

        return true;
    }

    bool ChessGame::restoreFromRecord(const ChessRecord &record)
    {
        const Position from = record.move->getFrom();
        const Position to = record.move->getTo();

        switch (record.move->getMoveType())
        {
            case ChessMoveType::Normal:
            case ChessMoveType::PawnDoubleMove:
            {
                auto movedPiece = m_Board->removePiece(to);
                if (!movedPiece)
                {
                    return false;
                }

                if (!m_Board->placePiece(from, std::move(movedPiece)))
                {
                    return false;
                }

                if (record.capturedPieceType.has_value() &&
                    record.capturedPieceColor.has_value() &&
                    record.capturedPiecePosition.has_value())
                {
                    auto capturedPiece = ChessPieceFactory::create(
                        record.capturedPieceType.value(),
                        record.capturedPieceColor.value());

                    if (!capturedPiece)
                    {
                        return false;
                    }

                    if (!m_Board->placePiece(record.capturedPiecePosition.value(), std::move(capturedPiece)))
                    {
                        return false;
                    }
                }

                return true;
            }

            case ChessMoveType::Promotion:
            {
                auto promotedPiece = m_Board->removePiece(to);
                if (!promotedPiece)
                {
                    return false;
                }

                auto pawn = ChessPieceFactory::create(
                    ChessPieceType::Pawn,
                    record.movedPieceColor);

                if (!pawn)
                {
                    return false;
                }

                if (!m_Board->placePiece(from, std::move(pawn)))
                {
                    return false;
                }

                if (record.capturedPieceType.has_value() &&
                    record.capturedPieceColor.has_value() &&
                    record.capturedPiecePosition.has_value())
                {
                    auto capturedPiece = ChessPieceFactory::create(
                        record.capturedPieceType.value(),
                        record.capturedPieceColor.value());

                    if (!capturedPiece)
                    {
                        return false;
                    }

                    if (!m_Board->placePiece(record.capturedPiecePosition.value(), std::move(capturedPiece)))
                    {
                        return false;
                    }
                }

                return true;
            }

            case ChessMoveType::EnPassant:
            {
                auto movedPiece = m_Board->removePiece(to);
                if (!movedPiece)
                {
                    return false;
                }

                if (!m_Board->placePiece(from, std::move(movedPiece)))
                {
                    return false;
                }

                if (record.capturedPieceType.has_value() &&
                    record.capturedPieceColor.has_value() &&
                    record.capturedPiecePosition.has_value())
                {
                    auto capturedPiece = ChessPieceFactory::create(
                        record.capturedPieceType.value(),
                        record.capturedPieceColor.value());

                    if (!capturedPiece)
                    {
                        return false;
                    }

                    if (!m_Board->placePiece(record.capturedPiecePosition.value(), std::move(capturedPiece)))
                    {
                        return false;
                    }
                }

                return true;
            }

            case ChessMoveType::Castling:
            {
                auto king = m_Board->removePiece(to);
                if (!king)
                {
                    return false;
                }

                if (!m_Board->placePiece(from, std::move(king)))
                {
                    return false;
                }

                if (!record.rookFrom.has_value() || !record.rookTo.has_value())
                {
                    return false;
                }

                auto rook = m_Board->removePiece(record.rookTo.value());
                if (!rook)
                {
                    return false;
                }

                if (!m_Board->placePiece(record.rookFrom.value(), std::move(rook)))
                {
                    return false;
                }

                return true;
            }

            default:
                return false;
        }
    }

    bool ChessGame::undoMove()
    {
        ensureReady();

        auto recordOpt = m_History->undo();
        if (!recordOpt.has_value() || !recordOpt.value())
        {
            return false;
        }

        if (!restoreFromRecord(*recordOpt.value()))
        {
            return false;
        }

        switchPlayer();
        updateGameState();

        return true;
    }

    bool ChessGame::redoMove()
    {
        ensureReady();

        auto recordOpt = m_History->redo();
        if (!recordOpt.has_value() || !recordOpt.value())
        {
            return false;
        }

        const ChessRecord &record = *recordOpt.value();

        if (!applyMove(*record.move))
        {
            return false;
        }

        switchPlayer();
        updateGameState();

        return true;
    }

    GameState ChessGame::getGameState() const
    {
        return m_GameState;
    }

    bool ChessGame::isGameOver() const
    {
        return m_GameState == GameState::Checkmate ||
               m_GameState == GameState::Stalemate ||
               m_GameState == GameState::Draw;
    }

    void ChessGame::switchPlayer()
    {
        if (m_CurrentPlayer == m_WhitePlayer.get())
        {
            m_CurrentPlayer = m_BlackPlayer.get();
        }
        else
        {
            m_CurrentPlayer = m_WhitePlayer.get();
        }
    }

    void ChessGame::updateGameState()
    {
        m_GameState = GameState::Ongoing;
    }

    void ChessGame::initializeStandardGame()
    {
        ensureReady();

        m_GameState = GameState::Ongoing;
        m_CurrentPlayer = m_WhitePlayer.get();

        for (int col = 0; col < 8; ++col)
        {
            m_Board->placePiece(
                Position{1, col},
                ChessPieceFactory::create(ChessPieceType::Pawn, ChessPieceColor::Black));

            m_Board->placePiece(
                Position{6, col},
                ChessPieceFactory::create(ChessPieceType::Pawn, ChessPieceColor::White));
        }

        m_Board->placePiece(Position{0, 0}, ChessPieceFactory::create(ChessPieceType::Rook,   ChessPieceColor::Black));
        m_Board->placePiece(Position{0, 1}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::Black));
        m_Board->placePiece(Position{0, 2}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::Black));
        m_Board->placePiece(Position{0, 3}, ChessPieceFactory::create(ChessPieceType::Queen,  ChessPieceColor::Black));
        m_Board->placePiece(Position{0, 4}, ChessPieceFactory::create(ChessPieceType::King,   ChessPieceColor::Black));
        m_Board->placePiece(Position{0, 5}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::Black));
        m_Board->placePiece(Position{0, 6}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::Black));
        m_Board->placePiece(Position{0, 7}, ChessPieceFactory::create(ChessPieceType::Rook,   ChessPieceColor::Black));

        m_Board->placePiece(Position{7, 0}, ChessPieceFactory::create(ChessPieceType::Rook,   ChessPieceColor::White));
        m_Board->placePiece(Position{7, 1}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::White));
        m_Board->placePiece(Position{7, 2}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::White));
        m_Board->placePiece(Position{7, 3}, ChessPieceFactory::create(ChessPieceType::Queen,  ChessPieceColor::White));
        m_Board->placePiece(Position{7, 4}, ChessPieceFactory::create(ChessPieceType::King,   ChessPieceColor::White));
        m_Board->placePiece(Position{7, 5}, ChessPieceFactory::create(ChessPieceType::Bishop, ChessPieceColor::White));
        m_Board->placePiece(Position{7, 6}, ChessPieceFactory::create(ChessPieceType::Knight, ChessPieceColor::White));
        m_Board->placePiece(Position{7, 7}, ChessPieceFactory::create(ChessPieceType::Rook,   ChessPieceColor::White));
    }
}
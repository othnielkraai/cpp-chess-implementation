#include "domain/game/chessgame/chess_game.hpp"

#include <stdexcept>

using boardgame::history::chess::ChessRecord;

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

        if (m_CurrentPlayer == nullptr)
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
        if (!m_Board)
        {
            throw std::logic_error("ChessGame::getLegalMoves - board not set");
        }

        if (!m_MoveGenerator)
        {
            throw std::logic_error("ChessGame::getLegalMoves - move generator not set");
        }

        auto legalMoves = m_MoveGenerator->generateMoves(*m_Board);

        for (auto it = legalMoves.begin(); it != legalMoves.end();)
        {
            if ((*it)->getFrom() == position)
            {
                ++it;
            }
            else
            {
                it = legalMoves.erase(it);
            }
        }

        return legalMoves;
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

    bool ChessGame::makeMove(const IChessMove &move)
    {
        if (!m_Board)
        {
            throw std::logic_error("ChessGame::makeMove - board not set");
        }

        if (!m_History)
        {
            throw std::logic_error("ChessGame::makeMove - history not set");
        }

        if (!m_CurrentPlayer)
        {
            throw std::logic_error("ChessGame::makeMove - current player not set");
        }

        if (!m_Board->movePiece(move.getFrom(), move.getTo()))
        {
            return false;
        }

        auto record = std::make_unique<boardgame::history::chess::ChessRecord>(
            boardgame::history::chess::ChessRecord{
                move.clone(),
                m_Board->getPieceAt(move.getTo())->getType(),
                m_Board->getPieceAt(move.getTo())->getColor(),
                move.getMoveType() == ChessMoveType::Normal ? std::optional<ChessPieceType>{m_Board->getPieceAt(move.getTo())->getType()} : std::nullopt,
                move.getMoveType() == ChessMoveType::Promotion ? std::optional<ChessPieceType>{m_Board->getPieceAt(move.getTo())->getType()} : std::nullopt});

        m_History->addRecord(std::move(record));
        switchPlayer();
        updateGameState();
        return true;

        return false;
    }

    bool ChessGame::undoMove()
    {
        if (!m_History)
        {
            throw std::logic_error("ChessGame::undoMove - history not set");
        }

        if (!m_Board)
        {
            throw std::logic_error("ChessGame::undoMove - board not set");
        }

        // PAS DIT AAN NAAR JOUW EIGEN HISTORY / BOARD API
        //
        // Voorbeeld:
        // auto move = m_History->undo();
        // if (!move)
        // {
        //     return false;
        // }
        //
        // m_Board->undoMove(*move);
        // switchPlayer();
        // updateGameState();
        // return true;

        return false;
    }

    bool ChessGame::redoMove()
    {
        if (!m_History)
        {
            throw std::logic_error("ChessGame::redoMove - history not set");
        }

        if (!m_Board)
        {
            throw std::logic_error("ChessGame::redoMove - board not set");
        }

        // PAS DIT AAN NAAR JOUW EIGEN HISTORY / BOARD API
        //
        // Voorbeeld:
        // auto move = m_History->redo();
        // if (!move)
        // {
        //     return false;
        // }
        //
        // m_Board->applyMove(*move);
        // switchPlayer();
        // updateGameState();
        // return true;

        return false;
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

    void ChessGame::resetGame()
    {
        m_Board.reset();
        m_WhitePlayer.reset();
        m_BlackPlayer.reset();
        m_CurrentPlayer = nullptr;
        m_MoveGenerator.reset();
        m_History.reset();
        m_GameState = GameState::Ongoing;
    }

    void ChessGame::switchPlayer()
    {
        if (!m_WhitePlayer || !m_BlackPlayer)
        {
            throw std::logic_error("ChessGame::switchPlayer - players not set");
        }

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
        // PAS DIT LATER AAN MET JOUW EIGEN LOGICA
        //
        // Bijvoorbeeld:
        // - check of current player in check staat
        // - check of er legal moves zijn
        // - dan Check / Checkmate / Stalemate / Ongoing zetten

        m_GameState = GameState::Ongoing;
    }
}
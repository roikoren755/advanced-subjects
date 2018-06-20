//
// Created by Roi Koren on 16/06/2018.
//

#ifndef ADVANCED_SUBJECTS_GAMEBOARD_H
#define ADVANCED_SUBJECTS_GAMEBOARD_H

#include <memory>
#include <array>
#include <iostream>

template<typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template <int ROWS, int COLS, class GAME_PIECE, int NUMBER_OF_PLAYERS = 2>
class GameBoard {
	PieceInfo<GAME_PIECE> board[ROWS][COLS];
	std::shared_ptr<GAME_PIECE> piece;
	int player;
public:
	GameBoard(): piece(nullptr), player(-1) {
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				this->board[i][j] = nullptr;
			}
		}
	}

	PieceInfo<GAME_PIECE> getPiece(int row, int col) const {
		int player = (*(this->board[row][col])).first;
		GAME_PIECE piece = (*this->board[row][col]).second;
		return std::make_unique<const std::pair<int, GAME_PIECE>>(std::make_pair(player, piece));
	}

	PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player) {
		PieceInfo<GAME_PIECE> pieceInfo = std::move(this->board[row][col]);
		this->board[row][col] = std::make_unique<const std::pair<int, GAME_PIECE>>(std::make_pair(player, piece));
		return std::move(pieceInfo);
	}

	void setPlayerSought(int player) {
		this->player = player;
	}

	void setPieceSought(std::shared_ptr<GAME_PIECE> piece) {
		if (piece == nullptr) {
			this->piece = nullptr;
		} else {
			this->piece = std::make_shared<GAME_PIECE>(*piece);
		}
	}

	class iterator {
		int row;
		int column;
		std::shared_ptr<GAME_PIECE> piece;
		int player;
		GameBoard& board;
	public:
		iterator(int row, int column, std::shared_ptr<GAME_PIECE> piece, int player, GameBoard& board):
				row(row), column(column), piece(piece), player(player), board(board) {}
		iterator operator++() {
			this->column++;
			if (this->column == COLS) {
				this->row++;
				this->column = 0;
			}

			if (this->row == ROWS) {
				this->column = 0;
				this->board.setPlayerSought(-1);
				this->board.setPieceSought(nullptr);
				return *this;
			}

			if (this->board.board[row][column] == nullptr) {
				return ++(*this);
			}

			if (this->player != -1 && (*(this->board.board[row][column])).first != this->player) {
				return ++(*this);
			}

			if (this->piece != nullptr && (*(this->board.board[row][column])).second != *(this->piece)) {
				return ++(*this);
			}

			return *this;
		}

		bool operator!=(iterator other) {
			return this->row != other.row || this->column != other.column || this->piece != other.piece ||
				   this->player != other.player;
		}

		const std::tuple<int, int, GAME_PIECE, int> operator*() {
			if (this->board.board[this->row][this->column] == nullptr) {
				return *(++(*this));
			}

			int currentPlayer = (*(this->board.board[row][column])).first;
			GAME_PIECE currentPiece = (*(this->board.board[row][column])).second;
			if (this->player != -1 && currentPlayer != this->player) {
				return *(++(*this));
			}

			if (this->piece != nullptr && currentPiece != *(this->piece)) {
				return *(++(*this));
			}

			return std::make_tuple(this->row, this->column, currentPiece, currentPlayer);
		}
	};

	iterator begin() {
		return iterator(0, 0, this->piece, this->player, *this);
	}

	iterator end() {
		return iterator(ROWS, 0, this->piece, this->player, *this);
	}

	GameBoard& allPiecesOfPlayer(int playerNum) {
		this->setPlayerSought(playerNum);
		return *this;
	}

	GameBoard& allOccureneceOfPiece(GAME_PIECE piece) {
		this->setPieceSought(std::make_shared<GAME_PIECE>(piece));
		return *this;
	}

	GameBoard& allOccureneceOfPieceForPlayer(GAME_PIECE piece, int playerNum) {
		this->setPlayerSought(playerNum);
		this->setPieceSought(std::make_shared<GAME_PIECE>(piece));
		return *this;
	}
};

#endif //ADVANCED_SUBJECTS_GAMEBOARD_H

/*
 * Board.hpp
 *
 *  Created on: Dec 8, 2013
 *      Author: orle
 *
 *  A set of 64 Squares, represents the chess Board
 */

#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <utility>
#include <list>
#include "Piece.hpp"

#define NUM_OF_SQUARES 64
#define WHITE_KING_START_RANK 1
#define BLACK_KING_START_RANK 8
#define WHITE_PAWN_RANK 2
#define BLACK_PAWN_RANK 7
#define KING_START_FILE 5
#define TYPE_POSITION 0

#define QS_WHITE_ROOK 0
#define QS_WHITE_KNIGHT 1
#define QS_WHITE_BISHOP 2
#define WHITE_QUEEN 3
#define WHITE_KING 4
#define KS_WHITE_BISHOP 5
#define KS_WHITE_KNIGHT 6
#define KS_WHITE_ROOK 7

#define FIRST_WHITE_PAWN 8
#define LAST_WHITE_PAWN 15

#define FIRST_EMPTY_SQUARE 16
#define LAST_EMPTY_SQUARE 47

#define FIRST_BLACK_PAWN 48
#define LAST_BLACK_PAWN 55

#define QS_BLACK_ROOK 56
#define QS_BLACK_KNIGHT 57
#define QS_BLACK_BISHOP 58
#define BLACK_QUEEN 59
#define BLACK_KING 60
#define KS_BLACK_BISHOP 61
#define KS_BLACK_KNIGHT 62
#define KS_BLACK_ROOK 63

#define QS_ROOK_FILE 1
#define QS_KNIGHT_FILE 2
#define QS_BISHOP_FILE 3
#define QUEEN_START_FILE 4
#define KS_BISHOP_FILE 6
#define KS_KNIGHT_FILE 7
#define KS_ROOK_FILE 8
#define RANK_WIDTH 8

enum castleType
{
	kingside_castle,
	queenside_castle
};

enum moveType
{
	regular_move,
	castle_kingside,
	castle_queenside,
	promotion,
	en_passant
};

class Piece;

class Board
{
public:
	/**
	 * board constructor
	 */
	Board();

	/**
	 * board destructor
	 */
	~Board();

	/**
	 * make a move on the board
	 */
	void makeMove(Position& origin, Position& destination);

	/**
	 * checks if a move is legal
	 */
	bool isLegal(const int originFile, const int originRank, const int destinationFile,
			const int destinationRank, pieceColor color) const;

	/**
	 * returns the color of a piece in the place represented by the position
	 */
	pieceColor pieceInPosition(const int file, const int rank) const;

	/**
	 * print the board to the screen, should be used for developement only
	 */
	void displayBoard() const;

	/**
	 * return the position of a king
	 */
	Position& getKingPos(pieceColor color);

	/**
	 * returns a char representing the type of the piece in position
	 */
	char getPieceType(const int file, const int rank) const;

	/**
	 * updates the checking list of the selected king
	 */
	bool updateCheckingList(pieceColor color);

	/**
	 * return a list with the positions of the pieces checking the specified king
	 */
	const std::list<Position>& getCheckingList(pieceColor color);

	/**
	 * updates the legal moves of all the pieces on the board, return the number of legal moves.
	 */
	int updateMoves(pieceColor color);

	/**
	 * prints the list of legal moves for each piece of the requested color, used for debugging
	 */
	void showLegalMoves(pieceColor color) const;

	/**
	 * returns true if a the pieces (king and rook) involved in a certain castle (defiend by color and
	 * castleType) has not yet made a move in the game.
	 */
	bool canCastle(pieceColor color, castleType type) const;

	/**
	 * checks if the piece in the position has made a double jump in the last move, if so returns true. assumes
	 * that the piece in this location is a Pawn and it must be verified before calling this method.
	 */
	bool isEnPassantLegal(const int file, const int rank, pieceColor color);

	/**
	 * returns the current turn number.
	 */
	int getCurrentTurn() const;

	/**
	 * updated the current turn number
	 */
	void updateTurnNumber();

	/**
	 * returns the string if the move for the PGN file in the right notation.
	 */
	std::string getMoveString(Position& origin, Position& destination);

private:
	/**
	 * returns the position of the square in the array according to the file and rank
	 */
	int squarePosition(const int file, const int rank) const;

	/**
	 * sets a pointer to the wanted piece in the wanted square, sets the pointer of the current position to NULL
	 */
	void setPieceInPosition(Position& origin, Position& destination);

	/**
	 * returns the type of a move. can be a regular move or a special move (castling, promotion, en-passant)
	 */
	moveType getMoveType(Position& origin, Position& destination);

	/**
	 * finding the appropriate multiple possibilities string. if another piece of the same type can move to
	 * the destination, should return the file letter of the origin. if the these pieces are on the same file
	 * should return the rank number. if there are such pieces both on the piece file and rank should return the
	 * exact position.
	 */
	std::string getMultPosString(Position& origin, Position& destination) const;

	/**
	 * returns the letter corresponding to the piece or an empty string in case of pawn
	 */
	std::string getTypeString(Position& origin) const;

	/**
	 * returns 'x' in case there is a take operation and empty string otherwise
	 */
	std::string getTakeString(Position& origin, Position& destination) const;

	/**
	 * returns the destination square algebric notation
	 */
	std::string getDestinationString(Position& destination) const;

	/**
	 * returns the file letter that responds to the given number
	 */
	char getFileLetter(const int file) const;

	Piece* _board[NUM_OF_SQUARES];
	Position _whiteKingPos;
	Position _blackKingPos;
	int _turnNumber;
	bool _whiteKingMoved;
	bool _blackKingMoved;
	bool _whiteKingRookMoved;
	bool _blackKingRookMoved;
	bool _whiteQueenRookMoved;
	bool _blackQueenRookMoved;
};


#endif /* BOARD_HPP_ */

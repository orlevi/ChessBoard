/*
 * King.hpp
 *
 *  Created on: 23 במרץ 2014
 *      Author: Or
 */

#ifndef KING_HPP_
#define KING_HPP_

#include "Piece.hpp"

#define SHORT_KNIGHT_JUMP 1
#define LONG_KNIGHT_JUMP 2

#define KINGSIDE_CASTLE_FILE 7
#define QUEENSIDE_CASTLE_FILE 3

#define BISHOP 'B'
#define ROOK 'R'

class King : public Piece
{
public:
	/**
	 * King's constructor
	 */
	King(const pieceColor color, const int file, const int rank, Board& board);

	/**
	 * King's destructor
	 */
	~King();

	/**
	 * update the current legal moves list for this piece.
	 */
	int updateLegalMoves();

	/**
	 * updates the list of pieces currently checking the king returns true if the king is in check and false
	 * otherwise
	 */
	bool updateCheckingList();

	/**
	 * return the list of pieces currently checking the king
	 */
	const std::list<Position>& getCheckingList() const;

	/**
	 * checks if a certain square is threatened (if so, the king cannot move there). returns true if it is
	 * threatened and false other wise.
	 */
	bool isThreatened(Position& position);

protected:
	/**
	 * check for checks on diagonals;
	 */
	int checkDiagonals(Position& position, const bool updateList);

	/**
	 * check for checks on straight lines
	 */
	int checkFilesAndRanks(Position& position, const bool updateList);

	/**
	 * check for knight checks
	 */
	int checkForKnights(Position& position, const bool updateList);

	/**
	 * check for pawns
	 */
	int checkForPawns(Position& position, const bool updateList);

	/**
	 * checks for opposing pieces along a line, if such piece found and it is either a queen or a "dangerousType"
	 * it is added to the check list
	 */
	int checkLine(Position& position, const int fileIncrement, const int rankIncrement, const char dangerousType,
			const bool updateList);

	/**
	 * returns true if it is legal to castle to the kingside
	 */
	bool canCastleKingside();

	/**
	 * returns true if it is legal to castle to the queenside
	 */
	bool canCastleQueenside();

	std::list<Position> _checkingPieces;
};


#endif /* KING_HPP_ */

/*
 * NonKingPiece.hpp
 *
 *  Created on: 18 במרץ 2014
 *      Author: Or
 */

#ifndef NONKINGPIECE_HPP_
#define NONKINGPIECE_HPP_

#include "Piece.hpp"

enum pinStatus
{
	no_pin,
	rank_positive,
	rank_negative,
	file_positive,
	file_negative,
	diagonal_positive_positive,
	diagonal_positive_negative,
	diagonal_negative_negative,
	diagonal_negative_positive
};

enum listCode
{
	pin_list,
	check_list,
	move_list
};

/**
 * represents any piece which is not a king.
 */
class NonKingPiece : public Piece
{
public:
	/**
	 * constructor for a piece which is not a king.
	 */
	NonKingPiece(const pieceColor color, const int file, const int rank, Board &board, const std::string& ID);

	/**
	 * destructor for a piece which is not a king.
	 */
	virtual ~NonKingPiece();

	/**
	 * update the current legal moves list for this piece.
	 */
	int updateLegalMoves();

protected:
	/**
	 * returns the pin status for that piece.
	 */
	pinStatus isPinned() const;

	/**
	 * a helping method for isPinned, checks for pins on a file.
	 */
	pinStatus checkFilePin(Position& kingPos) const;

	/**
	 * a helping method for isPinned, checks for pins on a rank.
	 */
	pinStatus checkRankPin(Position& kingPos) const;

	/**
	 * a helping method for isPinned, checks for pins on a diagonal.
	 */
	pinStatus checkDiagonalPin(Position& kingPos) const;

	/**
	 * updates the list of positions that are legal for that piece under the opposing pinning pieces (if that
	 * piece is not pinned, all the positions are legal).
	 */
	void pinMoves();

	/**
	 * updates the list of positions that are legal for that piece under the state of check we are in (if the
	 * king is not in check all moves are legal, if the king is in double check no move is legal).
	 */
	void checkMoves();

	/**
	 * updates the list of the positions that piece can go to according to its movement style, this method should
	 * be implemented for each piece separately.
	 */
	virtual void pieceMoves() = 0;

	/**
	 * adds all the squares to the designated list
	 */
	void addAllSquars(listCode list);

	/**
	 * adds a line to the designated list, the line can be either a straight line along a rank or file, or a
	 * diagonal, according to the given increments.
	 * the line starts on the position of the piece and ends when we encounter another piece along that line or
	 * we reach the end of the board. if we stop because of a piece the square the piece is on is added if the
	 * color of the piece is not the same color as our piece, if they are of the same color, the last square
	 * that is added is the square before that piece.
	 */
	void addLine(listCode list, const int fileIncrement, const int rankIncrement, const Position& pos);

	std::list<Position>* _pieceMoves;
	std::list<Position>* _pinMoves;
	std::list<Position>* _checkMoves;
};



#endif /* NONKINGPIECE_HPP_ */

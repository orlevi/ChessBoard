/*
 * Knight.hpp
 *
 *  Created on: 28 במרץ 2014
 *      Author: Or
 */

#ifndef KNIGHT_HPP_
#define KNIGHT_HPP_


#include "NonKingPiece.hpp"

#define SHORT_KNIGHT_JUMP 1
#define LONG_KNIGHT_JUMP 2

/**
 * this class represents a Knight, inherited from piece.
 */
class Knight : public NonKingPiece
{
public:
	/**
	 * constructor of a Knight
	 */
	Knight(const pieceColor color, const int file, const int rank, Board& board);

	/**
	 * destructor of Knight
	 */
	~Knight();

	/**
	 * updates the list of the positions that piece can go to according to the knight movement style.
	 */
	void pieceMoves();

protected:
	/**
	 * checks a single move and adds it to the piece moves list if it is legal.
	 */
	void checkMove(const int fileJump, const int rankJump);
};



#endif /* KNIGHT_HPP_ */

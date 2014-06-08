/*
 * Pawn.hpp
 *
 *  Created on: 30 במרץ 2014
 *      Author: Or
 */

#ifndef PAWN_HPP_
#define PAWN_HPP_

#include "NonKingPiece.hpp"

/**
 * this class represents a Pawn, inherited from piece.
 */
class Pawn : public NonKingPiece
{
public:
	/**
	 * constructor of a Pawn
	 */
	Pawn(const pieceColor color, const int file, const int rank, Board& board);

	/**
	 * destructor of Pawn
	 */
	~Pawn();

	/**
	 * updates the list of the positions that piece can go to according to the Pawn movement style.
	 */
	void pieceMoves();

	/**
	 * returns the number of the last turn this pawn has moved.
	 */
	int getDoubleJumpTurn() const;

	/**
	 * sets the last move field to the current turn number
	 */
	void updateDoubleJumpTurn(const int turnNumber);

protected:
	int _doubleJumpTurn;
};




#endif /* PAWN_HPP_ */

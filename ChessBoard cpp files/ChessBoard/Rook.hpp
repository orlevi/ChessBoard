/*
 * Rook.hpp
 *
 *  Created on: 16 במרץ 2014
 *      Author: Or
 */

#ifndef ROOK_HPP_
#define ROOK_HPP_

#include "NonKingPiece.hpp"

/**
 * this class represents a Rook, inherited from piece.
 */
class Rook : public NonKingPiece
{
public:
	/**
	 * constructor of a Rook
	 */
	Rook(const pieceColor color, const int file, const int rank, Board& board);

	/**
	 * destructor of Rook
	 */
	~Rook();

	/**
	 * updates the list of the positions that piece can go to according to the rook movement style.
	 */
	void pieceMoves();
};



#endif /* ROOK_HPP_ */

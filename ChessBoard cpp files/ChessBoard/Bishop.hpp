/*
 * Bishop.hpp
 *
 *  Created on: 25 במרץ 2014
 *      Author: Or
 */

#ifndef BISHOP_HPP_
#define BISHOP_HPP_

#include "NonKingPiece.hpp"

/**
 * this class represents a Bishop, inherited from piece.
 */
class Bishop : public NonKingPiece
{
public:
	/**
	 * constructor of a Bishop
	 */
	Bishop(const pieceColor color, const int file, const int rank, Board& board);

	/**
	 * destructor of Bishop
	 */
	~Bishop();

	/**
	 * updates the list of the positions that piece can go to according to the rook movement style.
	 */
	void pieceMoves();
};



#endif /* BISHOP_HPP_ */

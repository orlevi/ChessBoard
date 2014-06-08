/*
 * Queen.hpp
 *
 *  Created on: 25 במרץ 2014
 *      Author: Or
 */

#ifndef QUEEN_HPP_
#define QUEEN_HPP_



#include "NonKingPiece.hpp"

/**
 * this class represents a Bishop, inherited from piece.
 */
class Queen : public NonKingPiece
{
public:
	/**
	 * constructor of a Queen
	 */
	Queen(const pieceColor color, const int file, const int rank, Board& board);

	/**
	 * destructor of Queen
	 */
	~Queen();

	/**
	 * updates the list of the positions that piece can go to according to the queen movement style.
	 */
	void pieceMoves();
};



#endif /* QUEEN_HPP_ */

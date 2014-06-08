/*
 * Rook.cpp
 *
 *  Created on: 16 במרץ 2014
 *      Author: Or
 */

#include "Rook.hpp"

/**
 * constructor of a Rook
 */
Rook::Rook(const pieceColor color, const int file, const int rank, Board& board):
NonKingPiece(color, file, rank, board, (color == white) ? "Rw" : "Rb")
{
}

/**
 * destructor of Rook
 */
Rook::~Rook()
{

}

/**
 * updates the list of the positions that piece can go to according to the rook movement style.
 */
void Rook::pieceMoves()
{
	int fileIncrement;
	int rankIncrement;

	/* moving along a file, positive direction */
	fileIncrement = 0;
	rankIncrement = 1;
	addLine(move_list, fileIncrement, rankIncrement, _position);

	/* moving along a file, negative direction */
	fileIncrement = 0;
	rankIncrement = -1;
	addLine(move_list, fileIncrement, rankIncrement, _position);

	/* moving along a rank, positive direction */
	fileIncrement = 1;
	rankIncrement = 0;
	addLine(move_list, fileIncrement, rankIncrement, _position);

	/* moving along a rank, negative direction */
	fileIncrement = -1;
	rankIncrement = 0;
	addLine(move_list, fileIncrement, rankIncrement, _position);
}

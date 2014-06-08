/*
 * Queen.cpp
 *
 *  Created on: 25 במרץ 2014
 *      Author: Or
 */

#include "Queen.hpp"

/**
 * constructor of a Queen
 */
Queen::Queen(const pieceColor color, const int file, const int rank, Board& board):
NonKingPiece(color, file, rank, board, (color == white) ? "Qw" : "Qb")
{
}

/**
 * destructor of Queen
 */
Queen::~Queen()
{

}


/**
 * updates the list of the positions that piece can go to according to the queen movement style.
 */
void Queen::pieceMoves()
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

	/* moving along the upper right diagonal */
	fileIncrement = 1;
	rankIncrement = 1;
	addLine(move_list, fileIncrement, rankIncrement, _position);

	/* moving along the lower right diagonal */
	fileIncrement = 1;
	rankIncrement = -1;
	addLine(move_list, fileIncrement, rankIncrement, _position);

	/* moving along the upper left diagonal */
	fileIncrement = -1;
	rankIncrement = 1;
	addLine(move_list, fileIncrement, rankIncrement, _position);

	/* moving along the lower left diagonal */
	fileIncrement = -1;
	rankIncrement = -1;
	addLine(move_list, fileIncrement, rankIncrement, _position);
}


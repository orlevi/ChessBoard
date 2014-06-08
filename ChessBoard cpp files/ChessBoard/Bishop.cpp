/*
 * Bishop.cpp
 *
 *  Created on: 25 במרץ 2014
 *      Author: Or
 */

#include "Bishop.hpp"

/**
 * constructor of a Bishop
 */
Bishop::Bishop(const pieceColor color, const int file, const int rank, Board& board):
NonKingPiece(color, file, rank, board, (color == white) ? "Bw" : "Bb")
{
}

/**
 * destructor of Bishop
 */
Bishop::~Bishop()
{

}

/**
 * updates the list of the positions that piece can go to according to the bishop movement style.
 */
void Bishop::pieceMoves()
{
	int fileIncrement;
	int rankIncrement;

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


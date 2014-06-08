/*
 * Knight.cpp
 *
 *  Created on: 28 במרץ 2014
 *      Author: Or
 */

#include "Knight.hpp"

/**
 * constructor of a Knight
 */
Knight::Knight(const pieceColor color, const int file, const int rank, Board& board) :
NonKingPiece(color, file, rank, board, (color == white) ? "Nw" : "Nb")
{

}

/**
 * destructor of Knight
 */
Knight::~Knight()
{

}

/**
 * updates the list of the positions that piece can go to according to the knight movement style.
 * checks explicitly for the 8 possible moves.
 */
void Knight::pieceMoves()
{
	checkMove(SHORT_KNIGHT_JUMP, LONG_KNIGHT_JUMP);
	checkMove(SHORT_KNIGHT_JUMP, -LONG_KNIGHT_JUMP);
	checkMove(-SHORT_KNIGHT_JUMP, LONG_KNIGHT_JUMP);
	checkMove(-SHORT_KNIGHT_JUMP, -LONG_KNIGHT_JUMP);
	checkMove(LONG_KNIGHT_JUMP, SHORT_KNIGHT_JUMP);
	checkMove(LONG_KNIGHT_JUMP, -SHORT_KNIGHT_JUMP);
	checkMove(-LONG_KNIGHT_JUMP, SHORT_KNIGHT_JUMP);
	checkMove(-LONG_KNIGHT_JUMP, -SHORT_KNIGHT_JUMP);
}

void Knight::checkMove(const int fileJump, const int rankJump)
{
	int file = _position.getFile() + fileJump;
	int rank = _position.getRank() + rankJump;
	if ((file >= MIN_FILE) && (file <= MAX_FILE) && (rank >= MIN_RANK) && (rank <= MAX_RANK) &&
			(_board.pieceInPosition(file, rank) != getColor()))
	{
		_pieceMoves->push_front(Position(file, rank));
	}
}



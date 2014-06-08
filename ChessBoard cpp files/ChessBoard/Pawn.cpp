/*
 * Pawn.cpp
 *
 *  Created on: 30 במרץ 2014
 *      Author: Or
 */

#include "Pawn.hpp"

/**
 * constructor of a Pawn
 */
Pawn::Pawn(const pieceColor color, const int file, const int rank, Board& board):
NonKingPiece(color, file, rank, board, (color == white) ? "pw" : "pb"), _doubleJumpTurn(0)
{

}

/**
 * destructor of Pawn
 */
Pawn::~Pawn()
{

}

/**
 * updates the list of the positions that piece can go to according to the Pawn movement style.
 */
void Pawn::pieceMoves()
{
	/* defines the direction of move of the pawn according to its color */
	int file;
	int rank;
	int rank2;
	int initialRank =  (getColor() == white) ? 2 : 7;
	int rankIncrement = (getColor() == white) ? 1 : -1;
	pieceColor oppositeColor = (getColor() == white) ? black : white;

	/* regular pawn advance */
	file = _position.getFile();
	rank = _position.getRank() + rankIncrement;
	if ((rank <= MAX_RANK) && (rank >= MIN_RANK) && (_board.pieceInPosition(file, rank) == no_piece))
	{
		_pieceMoves->push_front(Position(file, rank));
	}

	/* pawn large first move */
	file = _position.getFile();
	rank = _position.getRank() + 2 * rankIncrement;
	rank2 = _position.getRank() + rankIncrement;
	if ((_position.getRank() == initialRank) && (_board.pieceInPosition(file, rank2) == no_piece) &&
			(_board.pieceInPosition(file, rank) == no_piece))
	{
		_pieceMoves->push_front(Position(file, rank));
	}

	/* pawn takes to the right */
	file = _position.getFile() + 1;
	rank = _position.getRank() + rankIncrement;
	if ((rank <= MAX_RANK) && (rank >= MIN_RANK) && (file <= MAX_FILE) &&
			(_board.pieceInPosition(file, rank) == oppositeColor))
	{
		_pieceMoves->push_front(Position(file, rank));
	}

	/* pawn takes to the left */
	file = _position.getFile() - 1;
	rank = _position.getRank() + rankIncrement;
	if ((rank <= MAX_RANK) && (rank >= MIN_RANK) && (file>= MIN_FILE) &&
			(_board.pieceInPosition(file, rank) == oppositeColor))
	{
		_pieceMoves->push_front(Position(file, rank));
	}

	/* en passant to the right*/
	file = _position.getFile() + 1;
	rank = _position.getRank() + rankIncrement;
	rank2 = _position.getRank();
	/* there is an opposing pawn next to us on the right rank and file */
	if ((file <= MAX_FILE) && (rank2 == initialRank + 3 * rankIncrement) && (_board.pieceInPosition(file, rank2) == oppositeColor) &&
			(_board.getPieceType(file, rank2) == 'p'))
	{
		/* the pawn has made a double jump in the previous move */
		if (_board.isEnPassantLegal(file, rank2, getColor()))
		{
			_pieceMoves->push_front(Position(file, rank));
		}
	}

	/* en passant to the left*/
	file = _position.getFile() - 1;
	rank = _position.getRank() + rankIncrement;
	rank2 = _position.getRank();
	/* there is an opposing pawn next to us on the right rank and file */
	if ((file >= MIN_FILE) && (rank2 == initialRank + 3 * rankIncrement) && (_board.pieceInPosition(file, rank2) == oppositeColor) &&
			(_board.getPieceType(file, rank2) == 'p'))
	{
		/* the pawn has made a double jump in the previous move */
		if (_board.isEnPassantLegal(file, rank2, getColor()))
		{
			_pieceMoves->push_front(Position(file, rank));
		}
	}
}

/**
 * returns the number of the last turn this pawn has moved.
 */
int Pawn::getDoubleJumpTurn() const
{
	return _doubleJumpTurn;
}

/**
 * sets the last move field to the current turn number
 */
void Pawn::updateDoubleJumpTurn(const int turnNumber)
{
	_doubleJumpTurn = turnNumber;
}




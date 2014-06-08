/*
 * Piece.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: orle
 */

#include "Piece.hpp"

/**
 * constructor of a piece
 */
Piece::Piece(const pieceColor color, const int file, const int rank, Board& board, const std::string& ID):_color(color),
_position(file, rank), _board(board), _ID(ID)
{
	_moveList = new std::list<Position>();
}

/**
 * destructor of a piece, since this class serve as an interface and should be inherited the
 * dtor is virtual
 */
Piece::~Piece()
{
	delete _moveList;
}

/**
 * returns the ID of the piece, [one char for the type (p = pawn, R == rook, B = bishop,
 * N = knight, Q = queen, K = king) followed by one char representing the color (L = light,
 * D = dark)].
 */
std::string Piece::getID() const
{
	return _ID;
}

/**
 * updates the file and rank the piece is on
 */
void Piece::updatePosition(const int file, const int rank)
{
	_position.setFile(file);
	_position.setRank(rank);
}

/**
 * check if a certain move, indicated by the destination square file and rank is in the legal
 * moves list
 */
bool Piece::isLegalMove(const int file, const int rank) const
{
	for (std::list<Position>::iterator it = _moveList->begin(); it != _moveList->end(); it++)
	{
		if (it->getFile() == file && it->getRank() == rank) return true;
	}
	return false;
}

/**
 * clears the move list (the move list needs to be constructed from scratch before every turn)
 */
void Piece::clearMoveList()
{
	_moveList->erase(_moveList->begin(), _moveList->end());
}

/**
 * a getter function to the piece color
 */
pieceColor Piece::getColor() const
{
	return _color;
}

/**
 * a getter function for the list of legal moves
 */
std::list<Position>* Piece::getMoveList()
{
	return _moveList;
}

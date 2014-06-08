/*
 * Piece.hpp
 *
 *  Created on: Dec 8, 2013
 *      Author: orle
 *
 *  an all virtual father to every type of the pieces (and pawns...)
 */

#ifndef PIECE_HPP_
#define PIECE_HPP_

enum pieceColor
{
	white,
	black,
	no_piece
};

#define MIN_RANK 1
#define MAX_RANK 8
#define MIN_FILE 1
#define MAX_FILE 8

#include "Position.hpp"
#include "Board.hpp"
#include <list>
#include <utility>
#include <iostream>

class Board;

class Piece
{
public:
	/**
	 * constructor of a piece
	 */
	Piece(const pieceColor color, const int file, const int rank, Board& board, const std::string& ID);
	
	/**
	 * destructor of a piece, since this class serve as an interface and should be inherited the
	 * dtor is virtual
	 */
	virtual ~Piece();

	friend std::ostream& operator<< (std::ostream& stream, Piece& piece)
	{
		stream << piece.getID();
		return stream;
	}

	/**
	 * update the current legal moves list for this piece, should be implemented for each piece
	 * according to its move characteristics.
	 */
	virtual int updateLegalMoves() = 0;
	
	/**
	 * clears the move list (the move list needs to be constructed from scratch before every turn)
	 */
	void clearMoveList();

	/**
	 * returns the ID of the piece, [one char for the type (p = pawn, R == rook, B = bishop,
	 * N = knight, Q = queen, K = king) followed by one char representing the color (L = light,
	 * D = dark)].
	 */
	std::string getID() const;


	/**
	 * updates the file and rank the piece is on
	 */
	void updatePosition(const int file, const int rank);
	
	/**
	 * check if a certain move, indicated by the destination square file and rank is in the legal
	 * moves list
	 */
	bool isLegalMove(const int file, const int rank) const;

	/**
	 * a getter function to the piece color
	 */
	pieceColor getColor() const;

	/**
	 * a getter function for the list of legal moves
	 */
	std::list<Position>* getMoveList();
protected:
	pieceColor _color;
	Position _position;
	Board& _board;
	std::string _ID;
	std::list<Position>* _moveList;
};
//functions - color getter

#endif /* PIECE_HPP_ */

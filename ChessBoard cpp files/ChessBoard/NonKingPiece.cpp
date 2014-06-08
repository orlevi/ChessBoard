/*
 * NonKingPiece.cpp
 *
 *  Created on: 18 במרץ 2014
 *      Author: Or
 */

#include "NonKingPiece.hpp"
#include <cmath>
#include <algorithm>

/**
 * constructor for a piece which is not a kong
 */
NonKingPiece::NonKingPiece(const pieceColor color, const int file, const int rank, Board& board,
		const std::string& ID):Piece(color, file, rank, board, ID)
{
	_pieceMoves = new std::list<Position>;
	_pinMoves = new std::list<Position>;
	_checkMoves = new std::list<Position>;
}

/**
 * destructor for a piece which is not a king.
 */
NonKingPiece::~NonKingPiece()
{
	delete _pieceMoves;
	delete _pinMoves;
	delete _checkMoves;
}

/**
 * update the current legal moves list for this rook.
 */
int NonKingPiece::updateLegalMoves()
{
	_moveList->clear();

	pinMoves();
	checkMoves();
	pieceMoves();

	bool inCheckMoves;
	bool inPinMoves;

	for (std::list<Position>::iterator it = _pieceMoves->begin() ; it != _pieceMoves->end(); it++)
	{
		inCheckMoves = false;
		inPinMoves = false;
		/* checking if a position from the move list is also on the check list */
		if (std::find(_checkMoves->begin(), _checkMoves->end(), *it) != _checkMoves->end())
		{
			inCheckMoves= true;
		}
		/* checking if a position from the move list is also on the check list */
		if (std::find(_pinMoves->begin(), _pinMoves->end(), *it) != _pinMoves->end())
		{
			inPinMoves= true;
		}
		if (inCheckMoves && inPinMoves)
		{
			_moveList->push_front(*it);
		}
	}
	/* after the updating of the move list we clear all the other lists as preperation for the next move */
	_pinMoves->clear();
	_checkMoves->clear();
	_pieceMoves->clear();

	return _moveList->size();
}

/**
 * returns true if a piece is pinned for its king and false otherwise
 */
pinStatus NonKingPiece::isPinned() const
{
	Position& kingPos = _board.getKingPos(getColor());
	int fileDiff = kingPos.getFile() - _position.getFile();
	int rankDiff = kingPos.getRank() - _position.getRank();
	/* fileDiff == 0 means the piece is on the same file as the king and we should check if it is pinned
	 * rankDiff == 0 means the piece is on the same rank as the king and we should check if it is pinned
	 * |fileDiff| == |rankDiff| means the king and piece are on the same diagonal and we should check for pin
	 */
	if (fileDiff == 0)
	{
		return checkFilePin(kingPos);
	}
	else if (rankDiff == 0)
	{
		return checkRankPin(kingPos);
	}
	else if (std::abs(fileDiff) == std::abs(rankDiff))
	{
		return checkDiagonalPin(kingPos);
	}
	return no_pin;
}

/**
 * a helping method for isPinned, checks for pins on a file
 */
pinStatus NonKingPiece::checkFilePin(Position& kingPos) const
{
	int sameColorPieces = 0;
	int	increment = (kingPos.getRank() < _position.getRank()) ? 1 : -1;
	int file = kingPos.getFile();
	pieceColor oppositeColor = (getColor() == white) ? black : white;

	for (int rank = kingPos.getRank() + increment; (rank <= MAX_RANK) && (rank >= MIN_RANK); rank = rank + increment)
	{
		/* piece on that position is of the same color */
		if (((file != _position.getFile()) || (rank != _position.getRank())) &&
				(_board.pieceInPosition(file, rank) == getColor()))
		{
			sameColorPieces++;
		}
		/* piece on that position is of the opposite color */
		else if (_board.pieceInPosition(file, rank) == oppositeColor)
		{
			char opposingPieceType = _board.getPieceType(file, rank);
			if ((sameColorPieces == 0) && ((opposingPieceType == 'R')||(opposingPieceType == 'Q')))
			{
				return (increment == 1) ? file_positive : file_negative;
			}
			else
			{
				return no_pin;
			}

		}
	}
	return no_pin;
}

/**
 * a helping method for isPinned, checks for pins on a rank
 */
pinStatus NonKingPiece::checkRankPin(Position& kingPos) const
{
	int sameColorPieces = 0;
	int	increment = (kingPos.getFile() < _position.getFile()) ? 1 : -1;
	int rank = kingPos.getRank();
	pieceColor oppositeColor = (getColor() == white) ? black : white;

	for (int file = kingPos.getFile() + increment; (file <= MAX_FILE) && (file >= MIN_FILE);
			file = file + increment)
	{
		/* piece on that position is of the same color */
		if (((file != _position.getFile()) || (rank != _position.getRank())) &&
				(_board.pieceInPosition(file, rank) == getColor()))
		{
			sameColorPieces++;
		}
		/* piece on that position is of the opposite color */
		else if (_board.pieceInPosition(file, rank) == oppositeColor)
		{
			char opposingPieceType = _board.getPieceType(file, rank);
			if ((sameColorPieces == 0) && ((opposingPieceType == 'R')||(opposingPieceType == 'Q')))
			{
				return (increment == 1) ? rank_positive : rank_negative;
			}
			else
			{
				return no_pin;
			}
		}
	}
	return no_pin;
}

/**
 * a helping method for isPinned, checks for pins on a diagonal
 */
pinStatus NonKingPiece::checkDiagonalPin(Position& kingPos) const
{
	int sameColorPieces = 0;
	int	fileIncrement = (kingPos.getFile() < _position.getFile()) ? 1 : -1;
	int	rankIncrement = (kingPos.getRank() < _position.getRank()) ? 1 : -1;
	pieceColor oppositeColor = (getColor() == white) ? black : white;

	for (int rank = kingPos.getRank() + rankIncrement, file = kingPos.getFile() + fileIncrement;
			(rank <= MAX_RANK) && (rank >= MIN_RANK) && (file <= MAX_FILE) && (file >= MIN_FILE);
			file = file + fileIncrement, rank = rank + rankIncrement)
	{
		/* piece on that position is of the same color and is not the same piece  */
		if ( ((file != _position.getFile()) || (rank != _position.getRank())) &&
				(_board.pieceInPosition(file, rank) == getColor()))
		{
			sameColorPieces++;
		}
		/* piece on that position is of the opposite color */
		else if (_board.pieceInPosition(file, rank) == oppositeColor)
		{
			char opposingPieceType = _board.getPieceType(file, rank);
			if ((sameColorPieces == 0) && ((opposingPieceType == 'B')||(opposingPieceType == 'Q')))
			{
				if (fileIncrement == 1)
				{
					return (rankIncrement == 1) ? diagonal_positive_positive : diagonal_positive_negative;
				}
				else
				{
					return (rankIncrement == 1) ? diagonal_negative_positive : diagonal_negative_negative;
				}
			}
			else
			{
				return no_pin;
			}
		}
	}
	return no_pin;
}

/**
 * adds all the squares to the designated list
 */
void NonKingPiece::addAllSquars(listCode code)
{
	for (int rank = MIN_RANK; rank <= MAX_RANK; rank++)
	{
		for (int file = MIN_FILE; file <= MAX_FILE; file++)
		{
			Position pos(file, rank);
			switch (code)
			{
			case pin_list:
				_pinMoves->push_front(pos);
				break;
			case check_list:
				_checkMoves->push_front(pos);
				break;
			case move_list:
				_pieceMoves->push_front(pos);
				break;
			}
		}
	}
}

/**
 * adds a line to the designated list, the line can be either a straight line along a rank or file, or a
 * diagonal, according to the given increments.
 * the line starts on the position of the piece and ends when we encounter another piece along that line or
 * we reach the end of the board. if we stop because of a piece the square the piece is on is added if the
 * color of the piece is not the same color as our piece, if they are of the same color, the last square
 * that is added is the square before that piece.
 */
void NonKingPiece::addLine(listCode code, const int fileIncrement, const int rankIncrement, const Position& pos)
{
	/* choosing the right list to fill */
	std::list<Position>* list;
	switch (code)
	{
	case pin_list:
		list = _pinMoves;
		break;
	case check_list:
		list = _checkMoves;
		break;
	case move_list:
		list = _pieceMoves;
		break;
	}
	/* adding the line to that list */
	pieceColor color;

	/* moving along a file, positive direction */
	for(int rank = pos.getRank() + rankIncrement, file = pos.getFile() + fileIncrement;
			(rank <= MAX_RANK) && (rank >= MIN_RANK) && (file <= MAX_FILE) && (file >= MIN_FILE);
			rank = rank + rankIncrement, file = file + fileIncrement)
	{
		color = _board.pieceInPosition(file, rank);
		if (color == no_piece) //no piece on position
		{
			list->push_front(Position(file, rank));
		}
		/* same color piece on position (and it is not the same piece!) */
		else if (color == getColor() && ((file != _position.getFile()) || (rank != _position.getRank())))
		{
			break;
		}
		else if ((file != _position.getFile()) || (rank != _position.getRank()))//opposite color piece on position
		{
			list->push_front(Position(file, rank));
			break;
		}
	}
}

/**
 * updates the list of positions that are legal for that piece under the opposing pinning pieces (if that
 * piece is not pinned, all the positions are legal).
 */
void NonKingPiece::pinMoves()
{
	int fileIncrement = 0;
	int rankIncrement = 0;
	pinStatus status = isPinned();
	switch (status)
	{
	case rank_positive:
		fileIncrement = 1;
		break;
	case rank_negative:
		fileIncrement = -1;
		break;
	case file_positive:
		rankIncrement = 1;
		break;
	case file_negative:
		rankIncrement = -1;
		break;
	case diagonal_positive_positive:
		fileIncrement = 1;
		rankIncrement = 1;
		break;
	case diagonal_positive_negative:
		fileIncrement = 1;
		rankIncrement = -1;
		break;
	case diagonal_negative_positive:
		fileIncrement = -1;
		rankIncrement = 1;
		break;
	case diagonal_negative_negative:
		fileIncrement = -1;
		rankIncrement = -1;
		break;
	default:
		break;
	}
	if ((fileIncrement == 0) && (rankIncrement == 0)) //no pin, all moves are legal (pinwise)
	{
		addAllSquars(pin_list);
	}
	else //piece is pinned, moves are legal only along the pin line
	{
		addLine(pin_list, fileIncrement, rankIncrement, _board.getKingPos(getColor()));
	}
}

/**
 * updates the list of positions that are legal for that piece under the state of check we are in (if the
 * king is not in check all moves are legal, if the king is in double check no move is legal).
 */
void NonKingPiece::checkMoves()
{
	const std::list<Position>& checkingPieces = _board.getCheckingList(getColor());
	Position& king = _board.getKingPos(getColor());
	const Position& checkingPiece = *(checkingPieces.begin());
	int fileDiff;
	int rankDiff;

	switch (checkingPieces.size())
	{
	case 0 : //no check, all moves are legal
		addAllSquars(check_list);
		break;
	case 1 : //checked once, should take the piece or block if possible
		fileDiff = checkingPiece.getFile() - king.getFile();
		rankDiff = checkingPiece.getRank() - king.getRank();
		/* the checking piece is a knight and it must be taken */
		if ((fileDiff != 0) && (rankDiff != 0) && (fileDiff != rankDiff ))
		{
			_checkMoves->push_front(Position(checkingPiece.getFile(), checkingPiece.getRank()));
		}
		/* the checking piece is a Queen, Rook, Bishop (or pawn), which can be either taken or blocked */
		else
		{
			/* setting increment to zero or unity in the right directions */
			int fileIncrement = (fileDiff == 0) ? fileDiff : fileDiff/abs(fileDiff);
			int rankIncrement = (rankDiff == 0) ? rankDiff : rankDiff/abs(rankDiff);
			/* adding the relevant line to the checking list */
			addLine(check_list, fileIncrement, rankIncrement, king);
		}
		break;
	case 2 : //checked twice, no legal moves, king must move
		break;
	}
}

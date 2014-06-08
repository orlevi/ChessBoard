/*
 * King.cpp
 *
 *  Created on: 23 במרץ 2014
 *      Author: Or
 */

#include "King.hpp"



/**
 * King's constructor
 */
King::King(const pieceColor color, const int file, const int rank, Board& board) :
Piece(color, file, rank, board, (color == white) ? "Kw" : "Kb")
{

}

/**
 * King's destructor
 */
King::~King()
{

}

/**
 * update the current legal moves list for this piece. checks explicitly for all 8 possible squares. also checks
 * for castling moves
 */
int King::updateLegalMoves()
{
	_moveList->clear();

	/* regular moves */
	for (int rank = _position.getRank() - 1; rank <= _position.getRank() + 1; rank++)
	{
		for (int file = _position.getFile() - 1; file <= _position.getFile() + 1; file++)
		{
			/* excluding the square we are currently on and illegal squares */
			if ((file <= MAX_FILE) && (file >= MIN_FILE) && (rank <= MAX_RANK) && (rank >= MIN_RANK) &&
					(_board.pieceInPosition(file, rank) != getColor()))
			{
				Position position(file, rank);
				if (!isThreatened(position))
				{
					_moveList->push_front(position);
				}
			}
		}
	}
	/* castling moves */
	if (canCastleKingside())
	{
		Position position(KINGSIDE_CASTLE_FILE, _position.getRank());
		_moveList->push_front(position);
	}
	if (canCastleQueenside())
	{
		Position position(QUEENSIDE_CASTLE_FILE, _position.getRank());
		_moveList->push_front(position);
	}

	return _moveList->size();
}

/**
 * updates the list of pieces currently checking the king, returns true if the king is in check and false
 * otherwise
 */
bool King::updateCheckingList()
{
	_checkingPieces.clear();

	checkDiagonals(_position, true);
	checkFilesAndRanks(_position, true);
	checkForKnights(_position, true);
	checkForPawns(_position, true);

	return (_checkingPieces.size() != 0);
}

/**
 * return the list of pieces currently checking the king
 */
const std::list<Position>& King::getCheckingList() const
{
	return _checkingPieces;
}

/**
 * checks if a certain square is threatened (if so, the king cannot move there). returns true if it is
 * threatened and false other wise.
 */
bool King::isThreatened(Position& position)
{
	if ((checkDiagonals(position, false) != 0) || (checkFilesAndRanks(position, false) != 0) ||
			(checkForKnights(position, false) != 0) || (checkForPawns(position, false) != 0))
	{
		return true;
	}
	return false;
}

/**
 * check for checks on diagonals;
 */
int King::checkDiagonals(Position& position, const bool updateList)
{
	int threatCounter = 0;
	int fileIncrement;
	int rankIncrement;

	fileIncrement = 1;
	rankIncrement = 1;
	threatCounter += checkLine(position, fileIncrement, rankIncrement, BISHOP, updateList);

	fileIncrement = 1;
	rankIncrement = -1;
	threatCounter += checkLine(position, fileIncrement, rankIncrement, BISHOP, updateList);

	fileIncrement = -1;
	rankIncrement = 1;
	threatCounter += checkLine(position, fileIncrement, rankIncrement, BISHOP, updateList);

	fileIncrement = -1;
	rankIncrement = -1;
	threatCounter += checkLine(position, fileIncrement, rankIncrement, BISHOP, updateList);

	return threatCounter;
}


/**
 * check for checks on straight lines
 */
int King::checkFilesAndRanks(Position& position, const bool updateList)
{
	int threatCounter = 0;
	int fileIncrement;
	int rankIncrement;

	fileIncrement = 0;
	rankIncrement = 1;
	threatCounter += checkLine(position, fileIncrement, rankIncrement, ROOK, updateList);

	fileIncrement = 0;
	rankIncrement = -1;
	threatCounter += checkLine(position, fileIncrement, rankIncrement, ROOK, updateList);

	fileIncrement = 1;
	rankIncrement = 0;
	threatCounter += checkLine(position, fileIncrement, rankIncrement, ROOK, updateList);

	fileIncrement = -1;
	rankIncrement = 0;
	threatCounter += checkLine(position, fileIncrement, rankIncrement, ROOK, updateList);

	return threatCounter;
}

/**
 * check for knight checks, checks in all 8 possible position explicitly
 */
int King::checkForKnights(Position& position, const bool updateList)
{
	int threatCounter = 0;
	int file;
	int rank;
	pieceColor opposingColor = (getColor() == white) ? black : white;

	file = position.getFile() + SHORT_KNIGHT_JUMP;
	rank = position.getRank() + LONG_KNIGHT_JUMP;
	if ((file <= MAX_FILE) && (rank <= MAX_RANK) && (_board.pieceInPosition(file, rank) ==opposingColor) &&
			(_board.getPieceType(file, rank) == 'N'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	file = position.getFile() + LONG_KNIGHT_JUMP;
	rank = position.getRank() + SHORT_KNIGHT_JUMP;
	if ((file <= MAX_FILE) && (rank <= MAX_RANK) && (_board.pieceInPosition(file, rank) ==opposingColor) &&
			(_board.getPieceType(file, rank) == 'N'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	file = position.getFile() - SHORT_KNIGHT_JUMP;
	rank = position.getRank() + LONG_KNIGHT_JUMP;
	if ((file >= MIN_FILE) && (rank <= MAX_RANK) && (_board.pieceInPosition(file, rank) ==opposingColor) &&
			(_board.getPieceType(file, rank) == 'N'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	file = position.getFile() - LONG_KNIGHT_JUMP;
	rank = position.getRank() + SHORT_KNIGHT_JUMP;
	if ((file >= MIN_FILE) && (rank <= MAX_RANK) && (_board.pieceInPosition(file, rank) ==opposingColor) &&
			(_board.getPieceType(file, rank) == 'N'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	file = position.getFile() + SHORT_KNIGHT_JUMP;
	rank = position.getRank() - LONG_KNIGHT_JUMP;
	if ((file <= MAX_FILE) && (rank >= MIN_RANK) && (_board.pieceInPosition(file, rank) ==opposingColor) &&
			(_board.getPieceType(file, rank) == 'N'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	file = position.getFile() + LONG_KNIGHT_JUMP;
	rank = position.getRank() - SHORT_KNIGHT_JUMP;
	if ((file <= MAX_FILE) && (rank >= MIN_RANK) && (_board.pieceInPosition(file, rank) ==opposingColor) &&
			(_board.getPieceType(file, rank) == 'N'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	file = position.getFile() - SHORT_KNIGHT_JUMP;
	rank = position.getRank() - LONG_KNIGHT_JUMP;
	if ((file >= MIN_FILE) && (rank >= MIN_RANK) && (_board.pieceInPosition(file, rank) ==opposingColor) &&
			(_board.getPieceType(file, rank) == 'N'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	file = position.getFile() - LONG_KNIGHT_JUMP;
	rank = position.getRank() - SHORT_KNIGHT_JUMP;
	if ((file >= MIN_FILE) && (rank >= MIN_RANK) && (_board.pieceInPosition(file, rank) ==opposingColor) &&
			(_board.getPieceType(file, rank) == 'N'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	return threatCounter;
}

/**
 * check for pawns, checks in the two possible places explicitly
 */
int King::checkForPawns(Position& position, const bool updateList)
{
	int threatCounter = 0;
	int file;
	int rank = (getColor() == white) ?position.getRank() + 1 : position.getRank() - 1;
	pieceColor opposingColor = (getColor() == white) ? black : white;

	file = position.getFile() + 1;
	if ((file <= MAX_FILE) && (rank >= MIN_RANK) && (rank <= MAX_RANK) &&
			(_board.pieceInPosition(file, rank) == opposingColor) && (_board.getPieceType(file, rank) == 'p'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	file = position.getFile() - 1;
	if ((file >= MIN_FILE) && (rank >= MIN_RANK) &&(rank <= MAX_RANK) &&
			(_board.pieceInPosition(file, rank) == opposingColor) && (_board.getPieceType(file, rank) == 'p'))
	{
		if (updateList)
		{
			_checkingPieces.push_front(Position(file, rank));
		}
		threatCounter++;
	}

	return threatCounter;
}

/**
 * checks for opposing pieces along a line, if such piece found and it is either a queen or a "dangerousType"
 * it is added to the check list
 */
int King::checkLine(Position& position, const int fileIncrement, const int rankIncrement, char dangerousType,
		const bool updateList)
{
	int threatCounter = 0;
	pieceColor color;

	for(int rank = position.getRank() + rankIncrement, file = position.getFile() + fileIncrement;
			(rank <= MAX_RANK) && (rank >= MIN_RANK) && (file <= MAX_FILE) && (file >= MIN_FILE);
			rank = rank + rankIncrement, file = file + fileIncrement)
	{
		color = _board.pieceInPosition(file, rank);
		/* no piece on position, or the king in position, continue search in line */
		if (color != no_piece && ((file != _position.getFile()) || (rank != _position.getRank())))
		{

			if (color != getColor()) // opposite color piece on position
			{
				char pieceType = _board.getPieceType(file, rank);
				if ((pieceType == 'Q') || (pieceType == dangerousType)) //if the piece is dangerous, add it
				{
					if (updateList)
					{
						_checkingPieces.push_front(Position(file, rank));
					}
					threatCounter++;
				}
			}
			/* only pieces directly in line with the king (with no other pieces in the middle) can be
			   threatening */
			break;
		}
	}

	return threatCounter;
}

/**
 * returns true if it is legal to castle to the kingside
 */
bool King::canCastleKingside()
{
	int kingFile = _position.getFile();
	int kingRank = _position.getRank();

	/* checking if we are on the start file (if we are not we can't assume that (kingFile + 2) is a legal square
	   and we can't castle anyway so we return false) */
	if (kingFile != KING_START_FILE)
	{
		return false;
	}

	Position pathSquare1(kingFile + 1, kingRank);
	Position pathSquare2(kingFile + 2, kingRank);

	std::string rookID = (getColor() == white) ? "Rw" : "Rb";

	bool notInCheck = (_checkingPieces.size() == 0);
	bool pathClear = (_board.pieceInPosition(kingFile + 1, kingRank) == no_piece) &&
			(_board.pieceInPosition(kingFile + 2, kingRank) == no_piece);
	bool pathNotThreatend = (! isThreatened(pathSquare1)) && (! isThreatened(pathSquare2));
	bool castlingRight = _board.canCastle(getColor(), kingside_castle);

	return (notInCheck && pathClear && pathNotThreatend && castlingRight);
}

/**
 * returns true if it is legal to castle to the queenside
 */
bool King::canCastleQueenside()
{
	int kingFile = _position.getFile();
	int kingRank = _position.getRank();

	/* checking if we are on the start file (if we are not we can't assume that (kingFile - 3) is a legal square
	   and we can't castle anyway so we return false) */
	if (kingFile != KING_START_FILE)
	{
		return false;
	}

	Position pathSquare1(kingFile - 1, kingRank);
	Position pathSquare2(kingFile - 2, kingRank);
	Position pathSquare3(kingFile - 3, kingRank);

	std::string rookID = (getColor() == white) ? "Rw" : "Rb";

	bool notInCheck = (_checkingPieces.size() == 0);
	bool pathClear = (_board.pieceInPosition(kingFile - 1, kingRank) == no_piece) &&
			(_board.pieceInPosition(kingFile - 2, kingRank) == no_piece) &&
			(_board.pieceInPosition(kingFile - 3, kingRank) == no_piece);
	bool pathNotThreatend = (! isThreatened(pathSquare1)) && (! isThreatened(pathSquare2));
	bool castlingRight = _board.canCastle(getColor(), queenside_castle);

	return (notInCheck && pathClear && pathNotThreatend && castlingRight);
}


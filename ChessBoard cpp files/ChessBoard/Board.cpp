/*
 * Board.cpp
 *
 *  Created on: Dec 8, 2013
 *      Author: orle
 */

#include <iostream>
#include <sstream>
#include "Board.hpp"

#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Pawn.hpp"


/**
 * board constructor
 */
Board::Board():_whiteKingPos(KING_START_FILE, WHITE_KING_START_RANK),
_blackKingPos(KING_START_FILE, BLACK_KING_START_RANK), _turnNumber(1), _whiteKingMoved(false), _blackKingMoved(false),
_whiteKingRookMoved(false), _blackKingRookMoved(false), _whiteQueenRookMoved(false), _blackQueenRookMoved(false)
{
	for (int i = 0; i < NUM_OF_SQUARES; i++)
	{
		_board[i] = NULL;
	}
	_board[QS_WHITE_ROOK] = new Rook(white, QS_ROOK_FILE, MIN_RANK, *this);
	_board[QS_WHITE_KNIGHT] = new Knight(white, QS_KNIGHT_FILE, MIN_RANK, *this);
	_board[QS_WHITE_BISHOP] = new Bishop(white, QS_BISHOP_FILE, MIN_RANK, *this);
	_board[WHITE_QUEEN] = new Queen(white, QUEEN_START_FILE, MIN_RANK, *this);
	_board[WHITE_KING] = new King(white, KING_START_FILE, MIN_RANK, *this);
	_board[KS_WHITE_BISHOP] = new Bishop(white, KS_BISHOP_FILE, MIN_RANK, *this);
	_board[KS_WHITE_KNIGHT] = new Knight(white, KS_KNIGHT_FILE, MIN_RANK, *this);
	_board[KS_WHITE_ROOK] = new Rook(white, KS_ROOK_FILE, MIN_RANK, *this);
	for (int boardPosition = FIRST_WHITE_PAWN, file = 1; boardPosition <= LAST_WHITE_PAWN;
			boardPosition++, file++)
	{
		_board[boardPosition] = new Pawn(white, file, WHITE_PAWN_RANK, *this);
	}

	for (int boardPosition = FIRST_BLACK_PAWN, file = 1; boardPosition <= LAST_BLACK_PAWN;
			boardPosition++, file++)
	{
		_board[boardPosition] = new Pawn(black, file, BLACK_PAWN_RANK, *this);
	}
	_board[QS_BLACK_ROOK] = new Rook(black, QS_ROOK_FILE, MAX_RANK, *this);
	_board[QS_BLACK_KNIGHT] = new Knight(black, QS_KNIGHT_FILE, MAX_RANK, *this);
	_board[QS_BLACK_BISHOP] = new Bishop(black, QS_BISHOP_FILE, MAX_RANK, *this);
	_board[BLACK_QUEEN] = new Queen(black, QUEEN_START_FILE, MAX_RANK, *this);
	_board[BLACK_KING] = new King(black, KING_START_FILE, MAX_RANK, *this);
	_board[KS_BLACK_BISHOP] = new Bishop(black, KS_BISHOP_FILE, MAX_RANK, *this);
	_board[KS_BLACK_KNIGHT] = new Knight(black, KS_KNIGHT_FILE, MAX_RANK, *this);
	_board[KS_BLACK_ROOK] = new Rook(black, KS_ROOK_FILE, MAX_RANK, *this);
}

/**
 * board destructor
 */
Board::~Board()
{
	for(int square = 0; square < NUM_OF_SQUARES; square++)
	{
		if (_board[square] != NULL)
		{
			delete _board[square];
		}
	}
}

/**
 * make a move on the board
 */
void Board::makeMove(Position& origin, Position& destination)
{
	moveType type = getMoveType(origin, destination);
	Position KSRookOrigin(KS_ROOK_FILE, origin.getRank());
	Position KSRookDestination(KS_BISHOP_FILE, origin.getRank());
	Position QSRookOrigin(QS_ROOK_FILE, origin.getRank());
	Position QSRookDestination(QUEEN_START_FILE, origin.getRank());
	Position enPassantTaken(destination.getFile(), origin.getRank());
	pieceColor color = _board[squarePosition(origin.getFile(), origin.getRank())]->getColor();
	switch (type)
	{
	case regular_move:
		setPieceInPosition(origin, destination);
		break;
	case castle_kingside:
		setPieceInPosition(origin, destination);
		setPieceInPosition(KSRookOrigin, KSRookDestination);
		break;
	case castle_queenside:
		setPieceInPosition(origin, destination);
		setPieceInPosition(QSRookOrigin, QSRookDestination);
		break;
	case en_passant:
		setPieceInPosition(origin, destination);
		delete _board[squarePosition(enPassantTaken.getFile(), enPassantTaken.getRank())];
		_board[squarePosition(enPassantTaken.getFile(), enPassantTaken.getRank())] = NULL;
		break;
	case promotion:
		setPieceInPosition(origin, destination);
		delete _board[squarePosition(destination.getFile(), destination.getRank())];
		_board[squarePosition(destination.getFile(), destination.getRank())] =
				new Queen(color, destination.getFile(), destination.getRank(), *this);
	}
}

/**
 * checks if a move is legal
 */
bool Board::isLegal(const int originFile, const int originRank, const int destinationFile,
		const int destinationRank, pieceColor color) const
{
	if (pieceInPosition(originFile, originRank) == color)
	{
		return _board[squarePosition(originFile, originRank)]->isLegalMove(destinationFile, destinationRank);
	}
	return false;
}

/**
 * returns the color of a piece in the place represented by the position
 */
pieceColor Board::pieceInPosition(const int file, const int rank) const
{
	if (_board[squarePosition(file, rank)] == NULL)
	{
		return no_piece;
	}
	return (_board[squarePosition(file, rank)]->getColor());
}

/**
 * print the board to the screen, should be used for debugging purposes only
 */
void Board::displayBoard() const
{
	for (int rank = MAX_RANK; rank >= MIN_RANK; rank--)
	{
		std::cout << "  _______________________ " << std::endl ;
		std::cout << rank << "|" ;
		for(int file = MIN_FILE; file <= MAX_FILE; file++)
		{
			if (_board[squarePosition(file, rank)] == NULL)
			{
				std::cout << "  " << "|";
			}
			else
			{
				std::cout << *(_board[squarePosition(file, rank)]) << "|";
			}
		}
		std::cout << std::endl ;
	}
	std::cout << "  _______________________ " << std::endl ;
	std::cout << "   A  B  C  D  E  F  G  H  " << std::endl ;
}

/**
 * return the position of a king
 */
Position& Board::getKingPos(pieceColor color)
{
	return (color == white) ? _whiteKingPos : _blackKingPos;
}

/**
 * returns a char representing the type of the piece in position
 */
char Board::getPieceType(const int file, const int rank) const
{
	return (_board[squarePosition(file, rank)]->getID())[TYPE_POSITION];
}

/**
 * updates the checking list of the selected king
 */
bool Board::updateCheckingList(pieceColor color)
{
	Position& kingPos = getKingPos(color);
	King* king = (King*) _board[squarePosition(kingPos.getFile(), kingPos.getRank())];
	return king->updateCheckingList();
}

/**
 * return a list with the positions of the pieces checking the specified king
 */
const std::list<Position>& Board::getCheckingList(pieceColor color)
{
	Position& kingPos = getKingPos(color);
	King* king = (King*) _board[squarePosition(kingPos.getFile(), kingPos.getRank())];
	return king->getCheckingList();
}

/**
 * updates the legal moves of all the pieces on the board, returns the number of legal moves.
 */
int Board::updateMoves(pieceColor color)
{
	pieceColor otherColor;
	int legalMoves = 0;
	for (int square = 0; square < NUM_OF_SQUARES; square++)
	{
		if (_board[square] != NULL)
		{
			otherColor = _board[square]->getColor();
			if (otherColor == color)
			{
				legalMoves += _board[square]->updateLegalMoves();
			}
		}
	}
	return legalMoves;
}

/**
 * prints the list of legal moves for each piece of the requested color
 */
void Board::showLegalMoves(pieceColor color) const
{
	for (int rank = MIN_RANK; rank <= MAX_RANK; rank++)
	{
		for (int file = MIN_FILE; file <= MAX_FILE; file++)
		{
			if (pieceInPosition(file, rank) == color)
			{
				Position pos(file, rank);
				std::list<Position>* list = _board[squarePosition(file, rank)]->getMoveList();
				std::cout << pos << ": ";
				for (std::list<Position>::iterator it = list->begin(); it != list->end(); it++)
				{
					std::cout << *it << ", ";
				}
				std::cout << std:: endl;
			}
		}
	}
}

/**
 * returns true if a the pieces (king and rook) involved in a certain castle (defiend by color and
 * castleType) has not yet made a move in the game.
 */
bool Board::canCastle(pieceColor color, castleType type) const
{
	bool hasKingMoved = (color == white) ? _whiteKingMoved : _blackKingMoved;
	bool hasKingRookMoved = (color == white) ? _whiteKingMoved : _blackKingMoved;
	bool hasQueenRookMoved = (color == white) ? _whiteQueenRookMoved : _blackQueenRookMoved;
	return (type == kingside_castle) ? (!hasKingMoved && !hasKingRookMoved) :
			(!hasKingMoved && !hasQueenRookMoved);
}

/**
 * checks if the piece in the position has made a double jump in the last move, if so returns true. assumes
 * that the piece in this location is a Pawn and it must be verified before calling this method.
 */
bool Board::isEnPassantLegal(const int file, const int rank, pieceColor color)
{
	int lastMoveNumber = (color == white) ? (getCurrentTurn() - 1) : (getCurrentTurn());
	if (((Pawn*) _board[squarePosition(file, rank)])->getDoubleJumpTurn() == lastMoveNumber)
	{
		return true;
	}
	return false;
}

/**
 * returns the current turn number.
 */
int Board::getCurrentTurn() const
{
	return _turnNumber;
}

/**
 * updated the current turn number
 */
void Board::updateTurnNumber()
{
	_turnNumber++;
}

/**
 * returns the string if the move for the PGN file in the right notation.
 */
std::string Board::getMoveString(Position& origin, Position& destination)
{
	moveType move = getMoveType(origin, destination);
	if (move == castle_kingside)
	{
		return "0-0";
	}
	else if (move == castle_queenside)
	{
		return "0-0-0";
	}
	std::string moveString =  getTypeString(origin) + getMultPosString(origin, destination) +
			getTakeString(origin, destination) + getDestinationString(destination);
	if (move == promotion)
	{
		moveString = moveString + "=Q";
	}
	return moveString;
}

/**
 * returns the position of the square in the array according to the file and rank
 */
int Board::squarePosition(const int file, const int rank) const
{
	return (MAX_RANK * (rank - 1) + (file - 1));
}

/**
 * sets a pointer to the wanted piece in the wanted square, sets the pointer of the current position to NULL
 */
void Board::setPieceInPosition(Position& origin, Position& destination)
{
	std::string pieceID = _board[squarePosition(origin.getFile(), origin.getRank())]->getID();
	/* if it is the white king update the suitable field */
	if (pieceID.compare("Kw") == 0)
	{
		_whiteKingPos = destination;
		if (!_whiteKingMoved)
		{
			_whiteKingMoved = true;
		}
	}
	/* if it is the black king update the suitable field, if it hasn't moved yet, mark it as moved */
	if (pieceID.compare("Kb") == 0)
	{
		_blackKingPos = destination;
		if (!_blackKingMoved)
		{
			_blackKingMoved = true;
		}
	}
	/* if it is a rook that hasn't yet moved, mark it as moved */
	if (pieceID.compare("Rw") == 0)
	{
		if ((origin.getFile() == KS_ROOK_FILE) && (origin.getRank() == MIN_RANK) && !_whiteKingRookMoved)
		{
			_whiteKingRookMoved = true;
		}
		if ((origin.getFile() == QS_ROOK_FILE) && (origin.getRank() == MIN_RANK) && !_whiteQueenRookMoved)
		{
			_whiteQueenRookMoved = true;
		}
	}
	if (pieceID.compare("Rb") == 0)
	{
		if ((origin.getFile() == KS_ROOK_FILE) && (origin.getRank() == MAX_RANK) && !_blackKingRookMoved)
		{
			_blackKingRookMoved = true;
		}
		if ((origin.getFile() == QS_ROOK_FILE) && (origin.getRank() == MAX_RANK) && !_blackQueenRookMoved)
		{
			_blackQueenRookMoved = true;
		}
	}
	/* if it is a pawn, update the turn it moved on */
	if (pieceID[0] == 'p')
	{
		((Pawn*) _board[squarePosition(origin.getFile(), origin.getRank())])->updateDoubleJumpTurn(_turnNumber);
	}
	/* if there is a piece in the destination square, destruct it to prevent memory leak */
	if (_board[squarePosition(destination.getFile(), destination.getRank())] != NULL)
	{
		delete _board[squarePosition(destination.getFile(), destination.getRank())];
	}
	/* set the piece on the destination square and the origin square as NULL */
	_board[squarePosition(destination.getFile(), destination.getRank())] = _board[squarePosition(origin.getFile(), origin.getRank())];
	_board[squarePosition(origin.getFile(), origin.getRank())] = NULL;
	/* set the piece position field to the new position */
	_board[squarePosition(destination.getFile(), destination.getRank())]->
	updatePosition(destination.getFile(), destination.getRank());
}

/**
 * returns the type of a move. can be a regular move or a special move (castling, promotion, en-passant)
 */
moveType Board::getMoveType(Position& origin, Position& destination)
{
	char type = getPieceType(origin.getFile(), origin.getRank());
	switch (type)
	{
	case 'K':
		if (destination.getFile() - origin.getFile() == 2)
		{
			return castle_kingside;
		}
		else if (destination.getFile() - origin.getFile() == -2)
		{
			return castle_queenside;
		}
		break;
	case 'p':
		if ((origin.getFile() != destination.getFile()) &&
				pieceInPosition(destination.getFile(), destination.getRank()) == no_piece)
		{
			return en_passant;
		}
		else if ((destination.getRank() == MIN_RANK) || (destination.getRank() == MAX_RANK))
		{
			return promotion;
		}
	}
	return regular_move;
}

/**
 * finding the appropriate multiple possibilities string. if another piece of the same type can move to
 * the destination, should return the file letter of the origin. if the these pieces are on the same file
 * should return the rank number. if there are such pieces both on the piece file and rank should return the
 * exact position.
 */
std::string Board::getMultPosString(Position& origin, Position& destination) const
{
	std::list<int> indices;
	int originIndex = squarePosition(origin.getFile(), origin.getRank());
	bool fileLetter = false, rankLetter = false;
	std::string pieceID = _board[originIndex]->getID();
	if (getPieceType(origin.getFile(), origin.getRank()) != 'p') //check that it is not a pawn as it may create problems
	{
		for (int i = 0; i < NUM_OF_SQUARES; i++)
		{
			/* if a piece (not a pawn) has the same ID and it can move to destination, add its index to the list */
			if ((i != originIndex) && (_board[i] != NULL) && (_board[i]->getID() == pieceID) &&
					(_board[i]->isLegalMove(destination.getFile(), destination.getRank())))
			{
				indices.push_front(i);
			}
		}
	}
	for (std::list<int>::iterator it = indices.begin(); it != indices.end(); it++)
	{
		if (((*it) / RANK_WIDTH) + 1 == origin.getRank())
		{
			fileLetter = true;
		}
		if (((*it) % RANK_WIDTH) + 1 == origin.getFile())
		{
			rankLetter = true;
		}
	}

	std::stringstream multPosStream;
	if (fileLetter)
	{
		multPosStream << getFileLetter(origin.getFile());
	}
	if (rankLetter)
	{
		multPosStream << origin.getRank();
	}

	return multPosStream.str();
}

/**
 * returns the letter corresponding to the piece or an empty string in case of pawn
 */
std::string Board::getTypeString(Position& origin) const
{
	std::stringstream typeStream;
	char type = getPieceType(origin.getFile(), origin.getRank());
	if (type != 'p')
	{
		typeStream << type;
	}
	return typeStream.str();
}

/**
 * returns 'x' in case there is a take operation and empty string otherwise
 */
std::string Board::getTakeString(Position& origin, Position& destination) const
{
	std::stringstream takeStream;
	if (_board[squarePosition(destination.getFile(), destination.getRank())] != NULL)
	{
		char type = getPieceType(origin.getFile(), origin.getRank());
		if (type == 'p')
		{
			takeStream << getFileLetter(origin.getFile());
		}
		takeStream << "x";
	}
	return takeStream.str();
}

/**
 * returns the destination square algebric notation
 */
std::string Board::getDestinationString(Position& destination) const
{
	std::stringstream destinationStream;
	destinationStream << getFileLetter(destination.getFile()) << destination.getRank();
	return destinationStream.str();
}

/**
 * returns the file letter that responds to the given number
 */
char Board::getFileLetter(const int file) const
{
	switch (file)
	{
	case 1:
		return 'a';
	case 2:
		return 'b';
	case 3:
		return 'c';
	case 4:
		return 'd';
	case 5:
		return 'e';
	case 6:
		return 'f';
	case 7:
		return 'g';
	default:
		return 'h';
	}
}


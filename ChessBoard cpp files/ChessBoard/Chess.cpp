/*
 * Chess.cpp
 *
 *  Created on: 21 במרץ 2014
 *      Author: Or
 */

#include "Board.hpp"
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>

std::string makeAMove(Board* board, pieceColor color)
{
	int originFile;
	int originRank;
	int destinationFile;
	int destinationRank;
	bool legalMove = false;
	std::stringstream moveString;

	while (!legalMove)
	{
		//std::cout << "enter origin file and rank" << std::endl;
		std::cin >> originFile >> originRank;
		//std::cout << "enter destination file and rank" << std::endl;
		std::cin >> destinationFile >> destinationRank;

		if ((legalMove = board->isLegal(originFile, originRank, destinationFile, destinationRank, color)))
		{
			Position origin(originFile, originRank);
			Position destination(destinationFile, destinationRank);
			if (color == white)
			{
				int turnNumber = board->getCurrentTurn();
				if (turnNumber != 1) // add a space before the number, but not before the first one.
				{
					moveString << " ";
				}
				moveString << turnNumber << ".";
			}
			moveString << " " << board->getMoveString(origin, destination) ;
			board->makeMove(origin, destination);
			std::cout << "Legal" << std::endl;
		}
		else
		{
			std::cout << "Illegal" << std::endl;
		}
	}
	return moveString.str();
}


/**
 * main function that starts the chess game
 */
int main()
{
	Board* board = new Board();
	pieceColor color = white;

	/* naming the PGN file with the game date and time.  */
	time_t t = time(0);   // get time now
	struct tm * now = localtime( & t );

	std::stringstream date, time, dateTag;
	date << now->tm_mday << '-'
		 << (now->tm_mon + 1) << '-'
		 << (now->tm_year + 1900);
	dateTag << (now->tm_year + 1900) << '.'
			<< (now->tm_mon + 1) << '.'
			<< now->tm_mday;
	time << now->tm_hour <<':'
		 << now->tm_min <<':'
		 << now->tm_sec;
	std::string fileName = date.str() + ' ' + time.str() + ".pgn";

	/* creating the PGN file and adding the headers to the file. */

	std::ofstream PGNFileStream;
	PGNFileStream.open(fileName.c_str(), std::ofstream::out | std::ofstream::app);

	//PGNFileStream << "[Event \"testing the program\"]" << std::endl;
	PGNFileStream << "[Site  \"Jerusalem\"]" << std::endl;
	PGNFileStream << "[Date \"" << dateTag.str() << "\"]" << std::endl;
	//PGNFileStream << "[Round \"3\"]" << std::endl;
	PGNFileStream << "[White \"Or Levi\"]" << std::endl;
	PGNFileStream << "[Black \"Or Levi\"]" << std::endl;
	PGNFileStream << "[Result \"*\"]" << std::endl;

	/* saving the result position to update it when the game ends, the -4 is to "take back" the
	   '*"]' in the end of the line as well as the end-line character.
	 */
	long resultPos = PGNFileStream.tellp() - 4;

	/* handling the new game */

	int legalMoves = board->updateMoves(color);
	bool inCheck;
	//board->displayBoard();

	while (legalMoves != 0)
	{
		std::string moveString = makeAMove(board, color);
		PGNFileStream << moveString;

		//board->displayBoard(); //print the board to the screen (for debug)

		if (color == black)
		{
			board->updateTurnNumber();
		}
		color = (color == white) ? black : white; // change the turn color
		inCheck = board->updateCheckingList(color); // update the check status
		legalMoves = board->updateMoves(color); // update legal moves list

		if (inCheck && legalMoves != 0)
		{
			PGNFileStream << "+";
		}

		//board->showLegalMoves(color); //printing each piece options to the screen (for debug)
	}

	/* at this point there are no more legal moves, so the player whose turn it is is either losing or in a
	   stalemate */

	/* if there is a check, it is mate, if not - stalemate. */
	std::string result = inCheck ? "# " : "";
	PGNFileStream << result;

	/* updating the Result tag in the beginning of the PGN file and the result in its end */
	std::string potentialWin = (color == white) ? "0-1" : "1-0";
	result = (inCheck ? potentialWin : "1/2-1/2");
	PGNFileStream << result << std::endl; //result in the end of the PGN file
	result += "\"]";
	PGNFileStream.seekp(resultPos); //setting the file position back to the result tag
	PGNFileStream << result << std::endl; //updating the result in the result tab

	/* writing to the PGN file is finished - closing the PGN file */
	PGNFileStream.close();

	delete board;

	return 0;
}


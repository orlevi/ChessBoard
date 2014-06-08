/*
 * try.cpp
 *
 *  Created on: 21 במרץ 2014
 *      Author: Or
 */

#include "Board.hpp"
#include <sstream>
#include <fstream>

void makeAMove(Board* board, pieceColor color, std::ofstream& PGNFileStream)
{
	int originFile;
	int originRank;
	int destinationFile;
	int destinationRank;
	bool legalMove = false;

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
					PGNFileStream << " ";
				}
				PGNFileStream << turnNumber << ".";
			}
			PGNFileStream << " " << board->getMoveString(origin, destination) ;
			board->makeMove(origin, destination);
			std::cout << "Legal" << std::endl;
		}
		else
		{
			std::cout << "Illegal" << std::endl;
		}
	}
}


/**
 * main function that starts the chess game
 */
int main()
{
	Board* board = new Board();
	pieceColor color = white;

	std::ofstream PGNFileStream; // creating the pgn file
	PGNFileStream.open("try.pgn", std::ofstream::out | std::ofstream::app);
	PGNFileStream << "[Event \"testing the program\"]" << std::endl;
	PGNFileStream << "[Site  \"Jerusalem\"]" << std::endl;
	PGNFileStream << "[Date \"2014.24.04\"]" << std::endl;
	PGNFileStream << "[Round \"3\"]" << std::endl;
	PGNFileStream << "[White \"Or Levi\"]" << std::endl;
	PGNFileStream << "[Black \"Or Levi\"]" << std::endl;

	int legalMoves = board->updateMoves(color);
	bool inCheck;
	//board->displayBoard();

	while (legalMoves != 0)
	{
		makeAMove(board, color, PGNFileStream);

		//board->displayBoard();

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

		//board->showLegalMoves(color); //printing each piece options to the screen
	}

	/* at this point there are no more legal moves, so the player whose turn it is is either losing or in a
	   stalemate */
	std::string potentialWin = (color == white) ? "# 0-1" : "# 1-0";
	/* if there is a check, it is mate, if not - stalemate. */
	std::string result = inCheck ? potentialWin : " 1/2-1/2";

	PGNFileStream << result << std::endl;

	PGNFileStream.close();

	delete board;

	return 0;
}


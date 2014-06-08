/*
 * Position.hpp
 *
 *  Created on: 21 במרץ 2014
 *      Author: Or
 */

#ifndef POSITION_HPP_
#define POSITION_HPP_

#include <ostream>

class Position
{
public:
	/**
	 * Position constructor
	 */
	Position(const int file, const int rank);

	/**
	 * Position copy constructor
	 */
	Position(const Position& other);


	/**
	 * returns the file
	 */
	int getFile() const;

	/**
	 * returns the rank
	 */
	int getRank() const;

	/**
	 * sets the file field
	 */
	void setFile(const int file);

	/**
	 * sets the rank field
	 */
	void setRank(const int rank);

	/**
	 * comparing operator, positions are equal if their file and rank fields are equal
	 */
	bool operator==(const Position& other) const;

	/**
	 * insertion to stream operator
	 */
	friend std::ostream& operator<< (std::ostream& stream, Position& position)
	{
		char file;
		switch (position.getFile())
		{
		case 1:
			file = 'a';
			break;
		case 2:
			file = 'b';
			break;
		case 3:
			file = 'c';
			break;
		case 4:
			file = 'd';
			break;
		case 5:
			file = 'e';
			break;
		case 6:
			file = 'f';
			break;
		case 7:
			file = 'g';
			break;
		case 8:
			file = 'h';
			break;
		}
		return (stream << file << position.getRank());
	}
private:
	int _file;
	int _rank;
};



#endif /* POSITION_HPP_ */

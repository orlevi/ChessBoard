/*
 * Position.cpp
 *
 *  Created on: 21 במרץ 2014
 *      Author: Or
 */
#include "Position.hpp"

/**
 * Position constructor from two ints
 */
Position::Position(const int file, const int rank) : _file(file), _rank(rank)
{

}

/**
 * Position copy constructor
 */
Position::Position(const Position& other)
{
	_file = other.getFile();
	_rank = other.getRank();
}

/**
 * returns the file
 */
int Position::getFile() const
{
	return _file;
}

/**
 * returns the rank
 */
int Position::getRank() const
{
	return _rank;
}

/**
 * sets the file field
 */
void Position::setFile(const int file)
{
	_file = file;
}

/**
 * sets the rank field
 */
void Position::setRank(const int rank)
{
	_rank = rank;
}

/**
 * comparing operator, positions are equal if their file and rank fields are equal
 */
bool Position::operator==(const Position& other) const
{
	return ((_file == other.getFile()) && (_rank == other.getRank()));
}



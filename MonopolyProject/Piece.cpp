#include "Piece.h"


Piece::Piece(int which)
{
	//put piece on board
	position = 0;

	//TODO: range check
	piece = static_cast<pieces>(which);
}


int Piece::getPosition()
{
	return this->_position;
}

void Piece::advancePosition(int numSpaces)
{//must be able to advance backwards too
}

void Piece::movePosition(int new_position)
{
	//todo: range check
	this->_position = new_position;
}

std::string Piece::str()
{
	return std::string();
}

void Piece::presentPieceOptions()
{
}

bool Piece::operator==(const Piece& p)
{
	if (p.name == name)
	{
		return true;
	}
	else return false;
}

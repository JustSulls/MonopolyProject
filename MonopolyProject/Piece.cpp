#include "Piece.h"
#include <iostream>

Piece::Piece(int which)
{
	_position = 0;
	piece = pieces(which);
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
	return piece_map[piece];
}

void Piece::presentPieceOptions()
{
	for (uint16_t i = 0; i < npiece::NUMBER_PIECES; i++)
	{
		std::cout << "[" << i << "] " << npiece::enum_str[i] << std::endl;
	}
}

bool Piece::operator==(const Piece& p)
{
	if (p.name == name)
	{
		return true;
	}
	else return false;
}

#include "Piece.h"
#include <stdlib.h>
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
	int newPosition = this->_position += numSpaces;
	int oldPosition = this->_position;
	if (newPosition < 0)
	{
		newPosition += 40;
	}
	else if( newPosition > 39)
	{
		newPosition -= 40;
	}
	//move piece
	movePosition(newPosition);
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
		CLogger::GetLogger()->Log("[" + std::to_string(i) + "] " + npiece::enum_str[i]);
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

#include "Piece.h"
#include <iostream>

Piece::Piece(int which)
{
	_position = 0;
	piece = pieces(which);
}

int Piece::position()
{
	return _position;
}

void Piece::movePosition(int new_position)
{
	//todo: perform some check on position value validity
	_position = new_position;
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

#include "Piece.h"

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
